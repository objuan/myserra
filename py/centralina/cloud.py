#!/usr/bin/env python3
from sys import stdout
import serial
import time
from threading import Thread
import sys
import blynklib
from enum import Enum
import logging
import threading
from .ws_service import GetConn
from pymitter import EventEmitter
import traceback

logger = logging.getLogger(__name__)

def Time_Event(time):
    if (GetConn()):
            GetConn().fire( ' {"type" : "time", "msg":'+time+'}')
            
def char_range(c1, c2):
    """Generates the characters from `c1` to `c2`, inclusive."""
    for c in range(ord(c1), ord(c2)+1):
        yield chr(c)

class VirtualPinMode(Enum):
     NULL = 0
     DIGITAL = 1
     ANALOGIC = 2
     #VIRTUAL = 3

#class Protocol(object):
#    
#    def _pack_msg(self, msg_type, *args, **kwargs):
#        data = ('\0'.join([str(curr_arg) for curr_arg in args])).encode('utf-8')
#        return struct.pack('!BHH', msg_type, self._get_msg_id(**kwargs), len(data)) + data
        
class VirtualPin:
    name="s"
    pin=0
    value=None # out value
    mode = VirtualPinMode.ANALOGIC

    def __init__(self,pin):
        self.pin=pin

    def get(self):
        return self.value

    #
    def read(self,con):
        c = "_vr "+ str(self.pin) +"\n"
        con.write(c.encode())

    def write(self,con,val):
             
        self.value=val
        print ("[CLOUD] " + str(self.pin) +"="+self.value)
        self.send(con)

    def send(self,com):
        #print("_wm")
        c = "_vw "+ str(self.pin) +" "+self.value+"\n"
        com.write(c.encode())

    #def onConnect(self,con):
    #    if (self.mode == VirtualPinMode.READ_WRITE ):
    #        self.send(con)

#############
### NOTE: 0 is system message
class SharedMemory:  

    data = {}
  
    def __init__(self):
        for c in range(0, 128):
            self.data[c]=VirtualPin(c)

    def get(self,name):
        return self.data[name].get()

    def read(self,arduino,pin_list):
        for c in pin_list:
           self.data[c].read(arduino.con())  

    def write(self,arduino,pin,val):
       self.data[pin].write(arduino.con(),val)

'''
'''
class SharedClient:  

    isOpen=False
    
    def __init__(self,memory,arduino):
        self.memory=memory
        self.arduino=arduino
        self.onMemory = EventEmitter()
        self.arduino.onMemory.on("onWrite", self.onWrite)

    def fireWrite(self,name,value):
            #print("fire write" , name,value)
            pin = self.memory.data[name]
            if (pin.mode == VirtualPinMode.DIGITAL):
                #print("handler1 called with", name,"'"+str(value)+"'",pin.mode )
                self.onMemory.emit("onWrite",name,str(value) =="1")
            else:
                self.onMemory.emit("onWrite",name,value)

    def onWrite(self,name,value):
            self.fireWrite(name,value)

    def isConnChanged(self):
        if (self.isOpen!= self.arduino.isOpen):
            self.isOpen= self.arduino.isOpen
            return True
        else:
            return False

    def get(self,name):

        pin = self.memory.data[name]
        if (pin.mode == VirtualPinMode.DIGITAL):
             return str(pin.value)=="1"
        else:
            return pin.value

    def setPinMode(self, name,mode): #VirtualPinMode.DIGITAL
         pin = self.memory.data[name]
         pin.mode = mode

    def read(self,pin):
        print("READ " , pin)
        self.memory.data[pin].read(self.arduino.con())  

    def reads(self,pin_list):
        for c in pin_list:
           self.memory.data[c].read(self.arduino.con())  

    def write(self,name,val):
        print("WRITE " , name,val)
        pin = self.memory.data[name]
        if (pin.mode == VirtualPinMode.DIGITAL):
            if (val):
                self.memory.data[name].write(self.arduino.con(),"1")
            else:
                self.memory.data[name].write(self.arduino.con(),"0")
        else:
            self.memory.data[name].write(self.arduino.con(),str(val))

        self.fireWrite(name,self.memory.data[name].get())

class ArduinoClient:  

    port = "COM7"
    baud_rate = 9600
    end_param='\x00'
    isOpen=False
    _isOpen=None
    connection=None
    ancora=True
 
    def __init__(self,port,baud_rate,memory):
        self.port=port
        self.baud_rate=baud_rate
        self.memory=memory
        self.onMemory = EventEmitter()

    def popConnChanged(self):
        if (self.isOpen!= self._isOpen):
            self._isOpen= self.isOpen
            return True
        else:
            return False

    def start(self):
        logger.info("ArduinoClient Started")
        #self.memory = SharedMemory()
        self.ancora=True
        t = threading.Thread(target=self.tick,args=[],daemon=True)
        t.start() 
        #self.run();

    def stop(self):
        logger.info("ArduinoClient Stopped")
        self.ancora=False
        self.connection.close()

    def con(self):
        return self.connection

    def ping(self):
        #if ( self.isOpen):
        #    self.connection.write("CMD PING_REQ\n".encode())
        pass
        #if ( self.isOpen):
        #    self.connection.

    def tick(self):

        while self.ancora:
            try:
                if (not self.isOpen):
                    self.connection = serial.Serial(self.port, self.baud_rate, timeout=1)
                    #ser.setDTR(True)
                    self.connection.flush()
                    self.isOpen=True
                    logger.info("Connected  at "+str(self.port) )
                else:
                    #while True:
                    while self.connection.in_waiting > 0:
                        line = self.connection.readline().decode('utf-8').rstrip()
                        #print("<=",line)
                        if (line.startswith("vw")):
                            #print(repr(line[2]))
                            args = line.split(sep=self.end_param)

                            #i = line.index(self.end_param,3)
                            #pin = int(line[3:i])
                            pin = int(args[1])
                            #print ("pin = " + str(pin))

                            self.memory.write(self,pin,args[2].rstrip())

                            self.onMemory.emit("onWrite",pin,self.memory.get(pin))
                        else:
                            if (line.startswith("CMD")):
                                #logger.info(line)
                                command = line[4:]
                                args = command.split(sep=self.end_param)

                                #print(command,args)
                                if (args[0].rstrip() =="TIME"):
                                      #print (args[1] )
                                      Time_Event(str(int(args[1])/1000))
                            else:
                                logger.info(line)
            
            except serial.SerialException as e:
                self.isOpen=False
                #e = sys.exc_info()[0]
                print (e)
                logger.error("Connecting .."+str(e) )

            except Exception as e:
                traceback.print_exc()
                #print ("...",e.__traceback__)
                logger.error(str(e) )

            time.sleep(1)





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
from datetime import datetime

logger = logging.getLogger(__name__)

def Time_Event(time_type,time):
    if (GetConn()):
            GetConn().fire( ' {"type" : "time", "time_type": "'+time_type+'" ,"msg":"'+time+'"}')
            
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


    def set(self,val):
        self.value=val
        print ("[SET] " + str(self.pin) +"="+self.value)

    #
    def read(self,client):
        c = str(self.pin)
        client.write("vr",c)

    def write(self,client,val):
      
        self.value=val
        print ("[CLOUD] " + str(self.pin) +"="+self.value)
        self.send(client)

    def send(self,client):
        c = str(self.pin) +" "+self.value
        client.write("vw",c)

    #def onConnect(self,con):
    #    if (self.mode == VirtualPinMode.READ_WRITE ):
    #        self.send(con)

#############
### NOTE: 0 is system message
class SharedMemory:  

    data = {}
  
    def __init__(self):
        for c in range(0, 256):
            self.data[c]=VirtualPin(c)

    def get(self,name):
        return self.data[name].get()

    def set(self,arduino,pin,val):
       self.data[pin].set(val)

    def read(self,arduino,pin_list):
        for c in pin_list:
           self.data[c].read(arduino)  

    def write(self,arduino,pin,val):
       self.data[pin].write(arduino,val)

  

'''
'''
class SharedClient:  

    isReady=False
    
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
        if (self.isReady!= self.arduino.isReady):
            self.isReady= self.arduino.isReady
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
        self.memory.data[pin].read(self.arduino)

    def reads(self,pin_list):
        for c in pin_list:
           self.memory.data[c].read(self.arduino)

    def write(self,name,val):
        print("WRITE " , name,val)
        pin = self.memory.data[name]
        if (pin.mode == VirtualPinMode.DIGITAL):
            if (str(val) == "True" or  str(val) == "1"):
                self.memory.data[name].write(self.arduino,"1")
            else:
                self.memory.data[name].write(self.arduino,"0")
        else:
            self.memory.data[name].write(self.arduino,str(val))

        self.fireWrite(name,self.memory.data[name].get())

class ArduinoClient:  

    port = "COM7"
    baud_rate = 9600
    end_param='\x00'
    end_block='\x01'
    isOpen=False
    isReady=False
    _isReady=None
    connection=None
    ancora=True
    messageQueue = []
    messageTime= None
    currentMessage = None
   
    def __init__(self,port,baud_rate,memory):
        self.port=port
        self.baud_rate=baud_rate
        self.memory=memory
        self.onMemory = EventEmitter()
        self._lock = threading.Lock() 
 

    def popConnChanged(self):
        if (self.isReady!= self._isReady):
            self._isReady= self.isReady
            return True
        else:
            return False

    def start(self):
        logger.info("ArduinoClient Started")
        #self.memory = SharedMemory()
        self.ancora=True
        t = threading.Thread(target=self.tick,args=[],daemon=True)
        t.start() 

        t1 = threading.Thread(target=self.tick_ping,args=[],daemon=True)
        t1.start() 
        #self.run();

    def stop(self):
        logger.info("ArduinoClient Stopped")
        self.ancora=False
        self.connection.close()

    #def con(self):
    #    return self.connection

    def addMessage(self,cmd,buffer):
        out_buffer = cmd.encode()
        out_buffer = out_buffer + (self.end_param.encode())
        out_buffer = out_buffer + ( buffer.encode())
        out_buffer = out_buffer + (self.end_param.encode())
        out_buffer = out_buffer + (b'\n')

        #print("--------",len(out_buffer))
        s=0
        e=0
        while e != len(out_buffer):
            e = s+32
            #print(s,e)
            if (e >= len(out_buffer))  :
                e = len(out_buffer)

            self.messageQueue.append(out_buffer[s:e])
            print ("add", out_buffer[s:e])
                       
            s=e


        print (out_buffer)
        '''
                #self.connection.write(cmd.encode())
                #self.connection.write(self.end_param.encode())
                #self.connection.flush()
                b = buffer.encode()
                #print(b)
                if (len(b) < 32):
                    self.connection.write(buffer.encode())
                    self.connection.write(self.end_param.encode())
                    self.connection.write(b'\n')
                    self.connection.flush()
                 else:
                    print("--------",len(b))
                    s=0
                    e=0
                    while e != len(b):
                      
                        e = s+32
                        print(s,e)
                        if (e >= len(b))  :
                            e = len(b)

                        print (b[s:e])
                        self.connection.write(b[s:e])
                        s=e
                
                    self.connection.write(b'\n')
                    self.connection.flush()
        '''

    def write(self,cmd,buffer):
        with self._lock:
            #print("Send", buffer,self.currentMessage)
         
            self.addMessage(cmd,buffer)
           
                #self._write(cmd,buffer)
        if (self.currentMessage == None):
               self.onACK()

    def onACK(self):
        with self._lock:
            if (self.currentMessage != None):
                self.currentMessage=None

            if (len( self.messageQueue)>0):
                    msg = self.messageQueue[0]
                    self.currentMessage=msg
                    del self.messageQueue[0]
                    print ("send",msg)
                    self.messageTime = datetime.now()
                    self.connection.write(msg)
                    self.connection.write(self.end_block.encode())
                    #self.connection.write(b'\n')
                    self.connection.flush()

                    '''
                        msg_arr = self.messageQueue[0]
                        self.currentMessage=msg_arr
                        print("Send queue ", msg_arr)
                        del self.messageQueue[0]
                        #self._write(msg_arr[0],msg_arr[1])
                    '''

    def ping(self):
        pass
    
    def tick_ping(self):
        while self.ancora:
          if (self.currentMessage!=None ):
                seconds_elapsed  =datetime.now() - self.messageTime
                if (seconds_elapsed > 10):
                    print("ERROR TIMEOUT")
                    self.currentMessage=None

       

   
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
                        l = self.connection.readline()
                        #print("<=",l)
                        line = l.decode('utf-8').rstrip()
                        #print("<=",line)
                        if (line.startswith("ACK")):
                            self.onACK()
                        elif (line.startswith("vw")):
                            #print(repr(line[2]))
                            args = line.split(sep=self.end_param)

                            #i = line.index(self.end_param,3)
                            #pin = int(line[3:i])
                            pin = int(args[1])
                            #print ("pin = " + str(pin))
                            #if (self.isReady):
                            self.memory.set(self,pin,args[2].rstrip())

                            self.onMemory.emit("onWrite",pin,self.memory.get(pin))
                        else:
                            if (line.startswith("CMD")):
                                logger.info(line)
                                command = line[4:]
                                args = command.split(sep=self.end_param)

                                if (args[0].rstrip() =="STARTUP"):
                                    logger.info("CONNECTION READY")
                                    self.isReady=True
                                    
                                #print(command,args)
                                if (args[0].rstrip() =="RUN_TIME"):
                                      #print (args[1] )
                                      Time_Event("RUN_TIME",str(int(args[1])/1000))
                                if (args[0].rstrip() =="DATE"):
                                      #print (args[1] )
                                      Time_Event("DATE",str(args[1]))
                            else:
                                logger.info(line)
            
            except serial.SerialException as e:
                self.isOpen=False
                self.isReady=False
                #e = sys.exc_info()[0]
                print (e)
                logger.error("Connecting .."+str(e) )

            except Exception as e:
                traceback.print_exc()
                #print ("...",e.__traceback__)
                logger.error(str(e) )

            time.sleep(0.1)





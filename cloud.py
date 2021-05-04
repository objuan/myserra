#!/usr/bin/env python3
from sys import stdout
import serial
import time
from threading import Thread
import sys
import blynklib
from enum import Enum
from eventhandler import EventHandler

def char_range(c1, c2):
    """Generates the characters from `c1` to `c2`, inclusive."""
    for c in range(ord(c1), ord(c2)+1):
        yield chr(c)

class VirtualPinMode(Enum):
     NULL = 0
     READ_TIME = 1
     READ_WRITE = 2

#class Protocol(object):
#    
#    def _pack_msg(self, msg_type, *args, **kwargs):
#        data = ('\0'.join([str(curr_arg) for curr_arg in args])).encode('utf-8')
#        return struct.pack('!BHH', msg_type, self._get_msg_id(**kwargs), len(data)) + data
        
class VirtualPin:
    name="s"
    pin=0
    value=None
    mode = VirtualPinMode.NULL

    def __init__(self,pin):
        self.pin=pin

    def get(self):
        return self.value

    def getBool(self):
        return str(self.value)== '1'

    #
    def read(self,con):
        c = "_vr "+ str(self.pin) +"\n"
        con.write(c.encode())

    def write(self,con,val):
        self.value=val
        if (self.mode == VirtualPinMode.NULL):
            self.mode=VirtualPinMode.READ_WRITE

        print ("[CLOUD] " + str(self.pin) +"="+str(self.value))
        self.send(con)

    def out_write(self,con,val):
        self.value=val
        if (self.mode == VirtualPinMode.NULL):
            self.mode=VirtualPinMode.READ_WRITE

        print ("[<< CLOUD] " + str(self.pin) +"="+str(self.value))
        self.send(con)

    def send(self,com):
        #print("_wm")
        c = "_vw "+ str(self.pin) +" "+str(self.value)+"\n"
        aa = c.encode(encoding='ASCII',errors='strict')
        #print(aa)
        com.write(aa)
        #com.write(bytes(c, 'utf-8'))

    def onConnect(self,con):
        if (self.mode == VirtualPinMode.READ_WRITE ):
            self.send(con)

#############
### NOTE: 0 is system message
class SharedMemory:  

    pins = {}
  
    def __init__(self):
        for c in range(0, 128):
            self.pins[c]=VirtualPin(c)

    def get(self,pin):
        return self.pins[pin].get()  

    def getBool(self,pin):
        return self.pins[pin].getBool()  

    def read(self,con,pin_list):
        for c in pin_list:
           self.pins[c].read(con)  

    def write(self,con,pin,val):
        if (pin==0):
            #system message
            self.onConnect(con)
            print("Started ") 

            #self.pins[0].com.write("_wm "+self.value+ "\n")
        else:    
            self.pins[pin].write(con,val)

    def out_write(self,con,pin,val):
        self.pins[pin].out_write(con,val)

    def onConnect(self,con):
        for key in self.pins:
            #if (self.pins[key].mode == VirtualPinMode.READ_WRITE ):
                self.pins[key].onConnect(con)

class ArduinoClient:  

    port = "COM7"
    baud_rate = 9600
    end_param='\x00'
    isOpen=False

    def __init__(self,port,baud_rate,memory):
        self.port=port
        self.baud_rate=baud_rate
        self.memory=memory
        self.event_handler = EventHandler('onConnect', 'onDisconnect') 
        #self.event_handler.link(self.__on_newuser_join, 'onConnect')

    def start(self):
        print("Started")
        #self.memory = SharedMemory()

        #t = Thread(target=self.run, args=())
        #t.start() 
        #self.run();

    def con(self):
        return self.ser

  

    def tick(self):

            #while True:
            try:
                if (not self.isOpen):
                    self.ser = serial.Serial(self.port, self.baud_rate, timeout=1)
                    #ser.setDTR(True)
                    self.ser.flush()
                    self.isOpen=True
                    self.event_handler.fire('onConnect',self)
                    print("CLOUD Connected  at ",self.port) 
                else:
                    #while True:
                    if self.ser.in_waiting > 0:
                        line = self.ser.readline().decode('utf-8').rstrip()
                        #print(line)
                        if (line.startswith("vw")):
                            #print(repr(line[2]))
                            i = line.index(self.end_param,3)
                            pin = int(line[3:i])
                            #print ("pin = " + str(pin))

                            self.memory.out_write(self.ser,pin,line[i+1:].strip()[:-1])
                        else:
                            print(line)
            
            except Exception as e:
                if (self.isOpen):
                    self.event_handler.fire('onDisconnect',self)
                self.isOpen=False
                #e = sys.exc_info()[0]
                print("CLOUD Connecting ..",e) 
                time.sleep(1)



############################
class BaseBoard:
    timers = []

    def addTimer(self,time_secs,callback):
        self.timers.append({"time_len" : time_secs,"time":time.time(),"callback": callback})

    def __init__(self,client,memory):
        self.memory=memory
        self.client=client

    def write(self,pin,val):
        self.memory.write(self.client.con(),pin,val)

    def tick(self):

        for timer in self.timers: 
            delta =   time.time() - timer["time"] 
            if (delta > timer["time_len"] ):
                timer["time"]  = time.time()
                #print(delta)
                timer["callback"] ()
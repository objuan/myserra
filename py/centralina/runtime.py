
from django.db import models
from django.utils.translation import gettext_lazy as _
from enum import Enum
from pyfirmata2 import  INPUT,OUTPUT
from .ws_service import *
import json
import logging
from .cloud import VirtualPinMode

logger = logging.getLogger(__name__)

def Connect_Event(message):
     if (GetConn()):
            GetConn().fire( ' {"type" : "connect", "msg":"'+message+'"}')

def Switch_Event(sw,message):
     if (GetSWEvent()):
            GetSWEvent().fire( ' {"type" : "sw",  "id" : '+str(sw.id)+', "state" : "'+sw.state+'", "pin_value" : "'+str(sw.pin_value)+'", "msg":"'+message+'"}')

def Var_Event(sw,message):
     if (GetVarEvent()):
            GetVarEvent().fire( ' {"type" : "var",  "id" : '+str(sw.id)+',  "value" : "'+str(sw.value)+'", "msg":"'+message+'"}')


class Memory() :
    board_map = {}
    commands= []
    manager=None

memory = Memory()

def RegisterManager(manager):
    global memory
    memory.manager = manager

def GetManager():
    return memory.manager 

def GetControl(board):
    return memory.board_map[board.name]

def RegisterControl(board,client):
    memory.board_map[board.name] = client
  

class BoardControl():

    # sampling rate: 10Hz
    samplingRate = 10

    def __init__(self,board,client):
        self.board=board
        self.client=client
        client.onMemory.on("onWrite", self.onWrite)

    ## from arduino
    def onWrite(self,pin,value):
        #print("onWrite ", pin,value)
       
        for sw in self.board.switch_set.all():
            if (sw.switchType.mode=="I" and pin == sw.pin):
                #print("onRead  I ",sw.pin,value)
                sw.setPinValue(value)
                Switch_Event(sw,"STATE " + sw.state)
            if (sw.switchType.mode=="O" and pin == sw.pin):
                #print("onRead  O ",sw.pin,value)
                sw.setPinValue(value)
                Switch_Event(sw,"STATE " + sw.state)

        for var in self.board.variable_set.all():
            if (pin == var.pin):
                #print("onReadV  ",var.pin,value)
                var.setPinValue(value)
                Var_Event(var,"")
                
                
        #print("CREATE BOARD CONTROLLER ", model)

    def onConnect(self):
        logger.info("CONTROLLER " +str(self.board))
    
        '''
        for sw in self.board.switch_set.all():
            logger.info ("SWITCH START " + sw.name + " " +str(sw.switchType.mode))
            if (sw.switchType.mode=="O"):
                #arduino.digital[sw.pin].mode = OUTPUT
                logger.info ("START SET VALUE %d %d" , sw.pin , sw.pin_value)
                arduino.digital[sw.pin].write(sw.pin_value)
                self.client.write()
        '''

        for var in self.board.variable_set.all():
            if  ((var.varType =="text_bool") 
                 or (var.varType =="btn_toggle")):
                self.client.setPinMode(var.pin,VirtualPinMode.DIGITAL)

            self.client.read(var.pin)

        #print(memory)
        '''
        #arduino.samplingOn(1000 / self.samplingRate)

        arduino.digital[PING_PIN].mode = OUTPUT
        arduino.digital[PING_PIN].write(False)

        for sw in self.board.switch_set.all():
            logger.info ("SWITCH START " + sw.name + str(sw.switchType.mode)+"'")
            if (sw.switchType.mode=="O"):
                arduino.digital[sw.pin].mode = OUTPUT
                logger.info ("START SET VALUE %d %d" , sw.pin , sw.pin_value)
                arduino.digital[sw.pin].write(sw.pin_value)

            elif (sw.switchType.mode=="I"):
                arduino.digital[sw.pin].mode = INPUT
                v =  arduino.digital[sw.pin].read()
                if (v != sw.pin_value or sw.state == ''):
                    print("INIT READ  ",sw.pin,v)
                    sw.setPinValue(v)
        '''


    def reconnect(self):
        global memory
        GetManager().reconnect()

    def stop(self):
        global memory
        GetManager().stop()
        '''
        arduino = GetArduino(self.board)
        memory.connection["active"] = False
        try:
            return arduino.digital[pin].read()
        except Exception as e:
            print("ERROR ",e)
        arduino.exit()
        '''

    c=0
    ping_tick=True
    old_conn=""
    def tick(self):
       
        '''
        arduino = GetArduino(self.board)

        ## PING

        
        try:
                #self.write(8,self.ping_tick)
                self.ping_tick= not self.ping_tick
                arduino.digital[PING_PIN].write(self.ping_tick)
        except Exception as e:
            print("ERROR ",e)
            memory.connection["active"]=True
            return
        #print("ping")
        if (self.old_conn != memory.connection["active"]):
            Connect_Event("CONNECTED ")    
        
        ## INPUTS

        for sw in self.board.switch_set.all():
            
            if (sw.switchType.mode=='I'):
                v =  arduino.digital[sw.pin].read()
                if (v != sw.pin_value or  sw.state == ''):
                    self.c=self.c+1
                    print("read  ",sw.pin,v,self.c)
                    sw.setPinValue(v)
                    Switch_Event(sw,"STATE " + sw.state)
                    
               

            #print("rick ",sw)
        '''

    '''
    def read(self,pin):
        arduino = GetArduino(self.board)
        try:
            print("read ",pin,arduino)
            return arduino.digital[pin].read()
        except Exception as e:
            print("ERROR ",e)
            memory.connection["active"]=True
    '''
    def write(self,pin, value):
        #global memory
        #arduino = GetArduino(self.board)

        print("WRITE ",pin,value)

        self.client.write(pin,value)

        '''
        #pin3 = arduino.get_pin('d:3:o')
        #print(pin)
        try:
            self.client.write(pin,value)
            return True
        except Exception as e:
            print("ERROR ",e)
            memory.connection["active"]=True
            return False
        #p = arduino.get_pin(pin)
        #p.write(value)
        #print("WRITE "+str(pin)+"=" +str(value))
        '''

class SwitchControl(BoardControl):

    pin=""

    def __init__(self,board,switch):
        self.value = False
        self.board=board
        self.switch=switch

        #print("CREATE SWITCH CONTROLLER ", switch, switch.switchType.mode )

    def setPinValue(self,pin_value):
        print("setPinValue "+str(self.pin)+"=" +str(pin_value))

        if (self.switch.switchType.mode == "I"):
            pass
            #self.pin = "d:"+str(self.switch.pin)+":i"
        if (self.switch.switchType.mode == "O"):
            self.write(self.switch.pin,pin_value)
            #self.pin = "d:"+str(self.switch.pin)+":o"

        #self.write(self.pin,pin_value)

'''
    ### SwitchStateType     
    def pinState(self):
         return self.state 
 
    # value : True = HI
    def setPinValue(self,pin_value):
        print("setPinValue "+str(self.model.pin)+"=" +str(pin_value))

        ss = lambda  v : 'open' if v else 'close'
        self.state =ss(pin_value)
        #self.save()
        if (pin_value == self.model.PIN_HI):
            print ("Set Pin " + str(self.model.pin)+"=" + "HI")
        else:
            print ("Set Pin " + str(self.model.pin)+"=" + "LOW")

    def toJson(self):
        return json.dumps(self, default=lambda o: o.__dict__)
        '''

    
   


#!/usr/bin/env python3
from sys import stdout
import time
import sys
from utils import *

SOLENOID_ON =False
SOLENOID_OFF =True

RELE_ON =False
RELE_OFF =True

class BaseBoard:
    timers = []

    def addTimer(self,time_secs,callback):
        self.timers.append({"time_len" : time_secs,"time":time.time(),"callback": callback})

    def tick(self):

        for timer in self.timers: 
            delta =   time.time() - timer["time"] 
            if (delta > timer["time_len"] ):
                timer["time"]  = time.time()
                #print(delta)
                timer["callback"] ()

class OsmosiBoard(BaseBoard):
    # come la board
    #WATER_IN_SOLENOID_PIN = "47" 
    #WATER_OUT_RELE_PIN = "44"

    #TOP_SWITCH_PIN = "53"  
    #FILL_SWITCH_PIN = "51"  
    #DANGER_SWITCH_PIN = "49" 

    WATER_IN_SOLENOID_PIN = "2" 
    WATER_OUT_RELE_PIN = "3"

    TOP_SWITCH_PIN = "4"  
    FILL_SWITCH_PIN = "5"  
    DANGER_SWITCH_PIN = "6" 

    WATER_STATE ="IDDLE" 

    def __init__(self,board):
        self.board=board
        Log("START OSMOSI")

        self.WATER_IN_SOLENOID = board.get_pin('d:'+self.WATER_IN_SOLENOID_PIN+':o')
        self.WATER_OUT_RELE = board.get_pin('d:'+self.WATER_OUT_RELE_PIN+':o')

        self.TOP_SWITCH = board.get_pin('d:'+self.TOP_SWITCH_PIN+':i')
        self.FILL_SWITCH = board.get_pin('d:'+self.FILL_SWITCH_PIN+':i')
        self.DANGER_SWITCH = board.get_pin('d:'+self.DANGER_SWITCH_PIN+':i')

        self.TOP_SWITCH.register_callback(self.onSwitchChanged)
        self.TOP_SWITCH.enable_reporting()
        self.FILL_SWITCH.register_callback(self.onSwitchChanged)
        self.FILL_SWITCH.enable_reporting()
        self.DANGER_SWITCH.register_callback(self.onSwitchChanged)
        self.DANGER_SWITCH.enable_reporting()

        #self.addTimer(2.0 , self.updateValues)
        #self.addTimer(2.0 , self.test)

    def onSwitchChanged(self,value):
        Debug("sw " + str(value))
        
    def isFull(self):
        return str(self.TOP_SWITCH.read()) == 'True'
    

    def needWater(self):
        return str(self.FILL_SWITCH.read()) == 'True'

    def dump(self):
        Log("WATER_STATE = "+str(self.WATER_STATE))

        Log("TOP_SWITCH = "+str(self.TOP_SWITCH.read()))
        Log("FILL_SWITCH = "+str(self.FILL_SWITCH.read()))
        Log("DANGER_SWITCH = "+str(self.DANGER_SWITCH.read()))
       
    def tick(self):
        self.dump()
        if (self.WATER_STATE =="IDDLE"):
            if (self.needWater()):
                self.WATER_STATE = "STATE_FILL"
                self.WATER_IN_SOLENOID.write(SOLENOID_ON)
                Log("WATER > FILLING")
        elif (self.WATER_STATE =="STATE_FILL"):
            if (self.isFull()):
                self.WATER_STATE = "IDDLE"
                self.WATER_IN_SOLENOID.write(SOLENOID_OFF)
                Log("WATER > IDDLE")


    

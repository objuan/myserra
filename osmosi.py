#!/usr/bin/env python3
from sys import stdout
import time
import sys
from cloud import *



class OsmosiBoard(BaseBoard):
    # come la board
    '''
    TOP_SWITCH_PIN = 53  
    FILL_SWITCH_PIN = 51  
    DANGER_SWITCH_PIN = 49  

    WATER_IN_SOLENOID_PIN = 47  
    WATER_OUT_RELE_PIN = 44
    '''
    TOP_SWITCH_PIN = 2  
    FILL_SWITCH_PIN = 3  
    DANGER_SWITCH_PIN = 4  

    WATER_IN_SOLENOID_PIN = 5  
    WATER_OUT_RELE_PIN = 6

    WATER_STATE_PIN = 101  
    WATER_ENABLE_PIN = 102

    pumpOpen = False

    @property
    def TOP_SWITCH(self):
        return self.memory.getBool(self.TOP_SWITCH_PIN)
 
    @property
    def FILL_SWITCH(self):
        return self.memory.getBool(self.FILL_SWITCH_PIN)

    @property
    def DANGER_SWITCH(self):
        return self.memory.getBool(self.DANGER_SWITCH_PIN)
 
    @property
    def WATER_STATE(self):
        return self.memory.get(self.WATER_STATE_PIN)

    def __init__(self,client,memory):
        super().__init__(client,memory)

        client.event_handler.link(self.onConnect, 'onConnect')
        #self.addTimer(2.0 , self.updateValues)

        #self.addTimer(2.0 , self.test)

    def onConnect(self,client):
        print("OSMOSI onConnect.." ,client.port )

    def updateValues(self):
        #print("updateValues")

        self.pumpOpen= not self.pumpOpen
        self.setPump(self.pumpOpen)

        print ("TOP_SWITCH",self.TOP_SWITCH)
        print ("FILL_SWITCH",self.FILL_SWITCH)
        print ("DANGER_SWITCH",self.DANGER_SWITCH)
        print ("WATER_STATE",self.WATER_STATE)

        self.memory.read(self.client.con(),[self.WATER_IN_SOLENOID_PIN,
           self.WATER_OUT_RELE_PIN,self.TOP_SWITCH_PIN,
           self.FILL_SWITCH_PIN,self.DANGER_SWITCH_PIN,self.WATER_STATE_PIN])

    def test(self):
        print("test")
        self.memory.write(self.client.con(),10,"ll")

    ## accende/spenge il riempimento
    def setEnable(self, enable):
         self.write(self.WATER_ENABLE_PIN, 1 if enable else 0)

    ## accende/spenge la pompa
    def setPump(self, open):
         self.write(self.WATER_OUT_RELE_PIN, 1 if open else 0)

  

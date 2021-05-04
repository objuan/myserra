#!/usr/bin/env python3
from sys import stdout
import time
import sys
from cloud import *
from recipes import *
import json 

class LabBoard(BaseBoard):
   
    recipt={"a":1, "b":"tt"}

    LAB_PUMP_1_PIN = 110 
    LAB_PUMP_2_PIN = 111 

    def __init__(self,client,memory):
        super().__init__(client,memory)
       
        client.event_handler.link(self.onConnect, 'onConnect')
        #self.addTimer(2.0 , self.test)

    def onConnect(self,client):
       
        print("LAB onConnect.." ,client.port )
        #self.addTimer(2.0 , self.updateValues)

    def updateValues(self):
        print("updateValues")
        rec = json.dumps(HuettRecipe().__dict__)
        print(rec)
        aa = '012345679012345679012345679012345679012345679012345679012345679'
        self.buildRecipt(aa)


    def buildRecipt(self,recipt):
        pass
        #self.write(self.LAB_RECIPE_PIN ,str(recipt) )
    
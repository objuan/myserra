import logging
from .Common import *
from .Config import *
from enum import Enum

logger = logging.getLogger(__name__)

class LabSym:
    
    class State(Enum):
        IDDLE = 0
        FILLING = 1
 

    state = State.IDDLE
    filling_percent=0

    def __init__(self,lab):
        self.lab=lab


    def Log(self,*args):
        LabInfo("[SYM " + self.lab.name  +  "]" , *args)

    def start(self):
        self.Log("=== SYM START ===")
        setSymMode(True)
        self.lab.distance_empty.set(30)
        self.lab.ph.set(7)
        self.lab.ec.set(600)
        self.lab.temperature.set(19)

    ####################################

    def fillFromTank(self,percent):
        self.Log("[SYM] FILL ",percent)
        self.lab.distance_empty.set(30)
        self.lab.distance.set(self.lab.distance_empty.get())

        self.state = LabSym.State.FILLING
        self.filling_percent=percent

    def fillEC(self,delta,percent):
        v = delta * (percent / 100)
        self.Log("[SYM] FILL DELTA EC", delta," with  ",v)
        self.lab.ec.set(self.lab.ec.get() +  v)
        
    def tick(self):
        #print("[SYM] ", self.state  ,  self.lab.fillPencent(),"%")

        if (self.state == LabSym.State.FILLING):
            current = self.lab.fillPencent()
            if (current < self.filling_percent):
                self.lab.distance.set(self.lab.distance.get()-10)
            else:
               
                self.state = LabSym.State.IDDLE
      

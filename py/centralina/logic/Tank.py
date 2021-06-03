
import logging
from .Common import *
from .Config import *

logger = logging.getLogger(__name__)

class Tank:
    def __init__(self,name,maxLiters):
        self.name=name
        self.maxLiters=maxLiters

        LabInfo("TANK "+name," init L:",maxLiters)
       
        self.pump_in = Pump(LAB_TANK1_IN)
        self.pump_out = Pump(LAB_TANK1_OUT)

    def refill(self):
        logger.info("REFILL %s %d",self.name)
       


    def tick(self):
        pass
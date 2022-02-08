
from django.db import models
import logging
from .Common import *
from .Lab import *
from .Chrono import *
from .Tank import *
import threading
import time
import traceback
from datetime import datetime

logger = logging.getLogger(__name__)

_logicManager=None

def GetLab():
   global _logicManager
   return _logicManager.lab

class LogicManager:
   def __init__(self):

      self.chrono = Chrono()
      self.lab = Lab(self,"lab1")
      global _logicManager
      _logicManager = self

      #########

      self.tank1 = Tank("tank1",80)

      #########

      self.ancora=True
      t = threading.Thread(target=self.tick,args=[],daemon=True)
      t.start() 
        
      ##### test
      if False:
         self.lab.startSym()
         self.lab.setTarget(self.tank1,6,1000,10,10)
         self.lab.cmd_tank_analyze()
         
        
   def tabkByID(self,id):
        if (str(id) == "1"):
            return self.tank1
     
   def stop(self):
        logger.info("LogicManager Stopped")
        self.ancora=False

   def tick(self):
        while(self.ancora):
            self.lab.tick()
            time.sleep(0.1)

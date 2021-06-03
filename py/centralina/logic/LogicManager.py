
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

class LogicManager:
   def __init__(self):

      self.chrono = Chrono()
      self.lab = Lab("lab1")

      #########

      self.tank1 = Tank("tank1",80)

      #########

      self.ancora=True
      t = threading.Thread(target=self.tick,args=[],daemon=True)
      t.start() 
        
      ##### test
      if True:
         self.lab.startSym()
         self.lab.setTarget(self.tank1,6,1000,10,10)
         self.lab.cmd_tank_analyze()
         
        
   def stop(self):
        logger.info("LogicManager Stopped")
        self.ancora=False

   def tick(self):
        while(self.ancora):
            self.lab.tick()
            time.sleep(1)

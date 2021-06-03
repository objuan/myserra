
import logging
from .Common import *
from .Config import *

logger = logging.getLogger(__name__)

class Chrono:
    def __init__(self):
        pass
        
    def startup(self, Tank):
        pass

    def tick(self):

        print ("LAB fill:",self.litres(),self.distance_empty.get() )
        
        pass
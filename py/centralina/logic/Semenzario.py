import logging
from ..models import WaterAnalysis
from .Common import *
from .Config import *
from .LabSym import *
from .LabIA import *
from .LabFiller import *
from enum import Enum
from datetime import datetime
import urllib.request

logger = logging.getLogger(__name__)

class Semenzario():
    

    def __init__(self):
        self.board = Board.objects.get(pk=8)

    def update(self):
        serialized_data = urllib.request.urlopen("http://"+self.board.net_address+"/state").read()

        self.data = json.loads(serialized_data)
   



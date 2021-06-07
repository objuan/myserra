import logging
from ..models import WaterAnalysis
from .Common import *
from .Config import *
from .LabSym import *
from .LabIA import *
from .LabFiller import *
from enum import Enum
from datetime import datetime

logger = logging.getLogger(__name__)


class LabAction(Enum):
     NONE = ''
     FILL_IN = 'FILL_IN'
     FILL_OUT = 'FILL_OUT'
     WAIT = 'WAIT'
     ANALYZE = 'ANALYZE'
     SYNC_EC = 'SYNC_EC'
     SYNC_PH = 'SYNC_PH'

##############

class Lab(StateMachine):
    
    ANALYZE_PERCENT = 10
    FILL_PERCENT = 50

    ## args
    filling_percent=0
    waitingTime = 0
    waitingStart= None

    #target
    target_tank = None
    target_ec = 0
    target_ph=0
    ph_tolerance_perc=0
    ec_tolerance_perc=0

    #####
    currentAnalysis = None

    def __init__(self,name):
         StateMachine.__init__(self,name)
         self.ia = LabIA(self)
         self.filler = LabFiller(self)
         self.name=name
         self.ec = ECMeter(LAB_EC_VALUE,LAB_EC_K)   
         self.ph = PHMeter(LAB_PH_VALUE,LAB_PH_VOLT,LAB_PH_REF_4,LAB_PH_REF_6)   
         self.area = LAB_BASE_AREA
         self.temperature = Termperature(LAB_TEMPERATURE)
         self.distance = DistanceMeter(LAB_DISTANCE)
         self.distance_empty = DistanceMeter(LAB_DISTANCE_EMPTY)
      
      
    ## sym
    def startSym(self):
        self.sym = LabSym(self)
        self.sym.start()

    ###############

    def Log(self,*args):
        LabInfo("[LAB " + self.name  +  "]" , *args)
    def Debug(self,*args):
        LabDebug("[LAB " + self.name  +  "]" , *args)

    def totalLitres(self):
        return (self.distance_empty.get() * self.area) / 1000
  
    def litres(self):
        return self.totalLitres() - (self.distance.get() * self.area) / 1000
        
     
    def fillPencent(self):
        return int(100.0 * (self.litres() / self.totalLitres()))
   
    def readSensors(self):
        a = WaterAnalysis.create(self.target_tank.name, self.ph.get(), self.ec.get() , self.temperature.get() )
        a.save()
        self.currentAnalysis = a
        return a

    ##############

    def setTarget(self,tank,ph,ec, ph_tolerance_perc, ec_tolerance_perc):
        self.target_tank=tank
        self.target_ec = ec
        self.target_ph = ph
        self.ph_tolerance_perc=ph_tolerance_perc
        self.ec_tolerance_perc=ec_tolerance_perc
        self.Log( "Set target" ,tank.name,"ph",ph,"+-",ph_tolerance_perc,"ec",ec,"+-",ec_tolerance_perc)
    
    ####### HI LEVEL #######
  
    def cmd_tank_analyze(self):
        self.cmd_fill_in_at(20)
        if isSymMode():
            self.cmd_wait(1)
        else:
            self.cmd_wait(2)
        self.cmd_analyze()

    ###### LOW LEVEL ########

    def cmd_fill_in_at(self,percent):
        self.pushAction( Action(LabAction.FILL_IN , percent)) 

    def cmd_fill_out(self):
        self.pushAction( Action(LabAction.FILL_OUT )) 

    def cmd_analyze(self):
        self.pushAction( Action(LabAction.ANALYZE , 0)) 

    def cmd_sync_ec(self):
        self.pushAction( Action(LabAction.SYNC_EC )) 
   
    def cmd_sync_ph(self):
        self.pushAction( Action(LabAction.SYNC_PH )) 

        
    #######################

    def onLabFillerEnd_EC_ADD(self):
        self.Log("ON LAB FILLER END : EC ADD")
        self.end(self.current_action)
 
    def onLabFillerEnd_PH_ADD(self):
        self.Log("ON LAB FILLER END : PH ADD")
        self.end(self.current_action)

    #       
    def onExecute(self, action: Action):

        self.Debug("Execute " , action.name)

        if (action.name == LabAction.FILL_IN):
            ## fill action
            self.Log("FILL ",action.value,"%" )
            self.filling_percent=action.value 
            self.Log("OPEN IN PUMP ")
            self.target_tank.pump_in.open()
            try:
                self.sym.fillFromTank(self.filling_percent)
            except AttributeError:
                pass

        elif (action.name == LabAction.WAIT):
            self.Log("WAITING ",action.value )
            self.waitingTime = action.value 
            self.waitingStart = datetime.now()

        elif (action.name  == LabAction.ANALYZE):
            self.Log("ANALYZE ")
            a = self.readSensors()
            # logica , prima ec poi ph
            self.Log("GET " , a)

            self.end(action)

            self.cmd_sync_ec()
            self.cmd_sync_ph()

        elif (action.name == LabAction.SYNC_EC):
            self.Log("SYNC EC ")
            self.filler.syncEC(self.onLabFillerEnd_EC_ADD)
        
        elif (action.name  == LabAction.SYNC_PH):
            self.Log("SYNC PH ")
            self.filler.syncPH(self.onLabFillerEnd_PH_ADD)

    def onTickAction(self, action: Action):
        if (action.name == LabAction.FILL_IN):
                if (self.fillPencent() >= self.filling_percent):
                    self.end(action)
       
    def onTick(self):
        
        self.filler.tick()
        try:
            self.sym.tick()
        except AttributeError:
            pass
    
    #########################

    def command(self,cmd,data):
        self.Log(" CMD", cmd,data)
        if (cmd =='calibrate'):
            self.filler.calibrate(data)
        if (cmd =='test_time'):
            self.filler.test_time_pump(data)

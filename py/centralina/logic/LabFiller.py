import logging
from ..models import WaterAnalysis
from .Common import *
from .Config import *
from .LabSym import *
from enum import Enum
from datetime import datetime

logger = logging.getLogger(__name__)


class LabFillerAction(Enum):
     EC_ADD = 'EC_ADD'
     PH_ADD = 'PH_ADD'
     WATER_ADD = 'WATER_ADD'

class LabFiller(StateMachine):
  
    def __init__(self,lab):
        StateMachine.__init__(self,lab.name+"_FIL")
        self.lab=lab
        self.endHandler=None
        self.ec_in = [Pump(LAB_EC_IN_A),Pump(LAB_EC_IN_B)]
        self.ph_in = Pump(LAB_PH_IN)
        self.mixer = Pump(LAB_MIX_PUNP)
        pass

    def Log(self,*args):
        LabInfo("[LAB "+ self.name  +  "]" ,*args)

    def exit(self):
        self.end(self.current_action)
        self.endHandler()

    def needWaterFill(self):
        self.lab.readSensors()
        min = self.lab.target_ec - (self.lab.target_ec * self.lab.ec_tolerance_perc) / 100
        max = self.lab.target_ec + (self.lab.target_ec * self.lab.ec_tolerance_perc) / 100
        self.Log("Check EC", self.lab.currentAnalysis.ec," [", min,"-",max,"]")
        return self.lab.currentAnalysis.ec > max  #or self.lab.currentAnalysis.ec > max

    def needECFill(self):
        self.lab.readSensors()
        min = self.lab.target_ec - (self.lab.target_ec * self.lab.ec_tolerance_perc) / 100
        max = self.lab.target_ec + (self.lab.target_ec * self.lab.ec_tolerance_perc) / 100
        self.Log("Check EC", self.lab.currentAnalysis.ec," [", min,"-",max,"]")
        return self.lab.currentAnalysis.ec < min  #or self.lab.currentAnalysis.ec > max

    def needPHFill(self):
        self.lab.readSensors()
        min = self.lab.target_ph - (self.lab.target_ph * self.lab.ph_tolerance_perc) / 100
        max = self.lab.target_ph + (self.lab.target_ph * self.lab.ph_tolerance_perc) / 100
        self.Log("Check PH", self.lab.currentAnalysis.ph," [", min,"-",max,"]")
        return self.lab.currentAnalysis.ph < min # or self.lab.currentAnalysis.ph > max

    def addEC(self):
        if (self.needECFill()):
            #while self.needECFill():
            litres = self.lab.litres()
            ec_delta =  self.lab.target_ec - self.lab.currentAnalysis.ec
            self.Log("sync EC", self.lab.currentAnalysis.ec," TARGET", self.lab.target_ec," Lt:",litres, " delta:",ec_delta)
            #compute
            # X : ec_delta = LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML : 1000

            comp_ml_list = self.lab.ia.getAddEC()
            '''
            ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML) / 1000
            ml_a = ec_1000_per_litro * litres 

            ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_B_1000_X_LITRO_IN_ML) / 1000
            ml_b = ec_1000_per_litro * litres 
            '''

            self.Log("FILL EC", "A ml:" , comp_ml_list[0]," B ml:",comp_ml_list[1])

            ## ACTIONS #####
            for index,com_ml in enumerate(comp_ml_list):
                self.cmd_open_ms(self.ec_in[index], com_ml* LAB_PUMP_6MM_ML_PER_SECONDS)
                self.cmd_open_ms(self.mixer, LAB_MIXER_TIME_SECS)

            try:
                self.lab.sym.fillEC(ec_delta,50)
            except AttributeError:
                pass

            #recursion
            self.cmd_ec_add()
        else:
            self.exit()
            #pass


    ######## LOW LEVEL ######

    def cmd_ec_add(self):
        self.pushAction(Action(LabFillerAction.EC_ADD))

    def cmd_ph_add(self):
        self.pushAction(Action(LabFillerAction.PH_ADD))

    def cmd_water_add(self):
        self.pushAction(Action(LabFillerAction.WATER_ADD))

    ######## HI LEVEL ########

    def syncEC(self,endHandler):
        self.endHandler=endHandler
        self.cmd_ec_add()
        pass

    
     ######### VIRTUALS ####

    def onExecute(self, action: Action):

        self.Log("Execute " , action)
        if (action.name == LabFillerAction.EC_ADD):
            self.end(action)
            self.addEC()
           
    def onTickAction(self, action: Action):
        pass

    def onTick(self):
        pass
    
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
     WATER_ADD = 'WATER_ADD',
     CALIB_WEIGHT_START = 'CALIB_WEIGHT_START',
     CALIB_WEIGHT_END = 'CALIB_WEIGHT_END'

class LabFiller(StateMachine):
  
    def __init__(self,lab):
        StateMachine.__init__(self,lab.name+"_FIL")
        self.lab=lab
        self.endHandler=None
        self.ec_in = [PumpWeight(LAB_EC_IN_A,LAB_EC_IN_A_WEIGHT),Pump(LAB_EC_IN_B)]
        self.ph_in = Pump(LAB_PH_IN)
        self.mixer = Pump(LAB_MIX_PUNP)
        self.water_in = Pump(LAB_WATER_IN)

        pass

    def Log(self,*args):
        LabInfo("[LAB "+ self.name  +  "]" ,*args)
    def Debug(self,*args):
        LabDebug("[LAB "+ self.name  +  "]" ,*args)

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
        return self.lab.currentAnalysis.ph > max # or self.lab.currentAnalysis.ph > max

    def addWater(self):
        if (self.needWaterFill()):
            
            litres = self.lab.ia.getAddWater()

            self.Log("FILL WATER", " litres:" , litres)

            #self.cmd_open_ms(self.ph_in, litres* LAB_PUMP_6MM_ML_PER_SECONDS)
            #self.cmd_open_ms(self.mixer, LAB_MIXER_TIME_SECS)

            try:
                self.lab.sym.fillWater(litres)
            except AttributeError:
                pass

            #recursion, at begin
            self.insertAction(Action(LabFillerAction.WATER_ADD))
            #self.cmd_water_add()
        else:
            self.end(self.current_action) #non exit
#

    def addEC(self):
        if (self.needECFill()):
            #compute
            comp_ml_list = self.lab.ia.getAddEC()

            self.Log("FILL EC", "A ml:" , comp_ml_list[0]," B ml:",comp_ml_list[1])

            ## ACTIONS #####
            for index,com_ml in enumerate(comp_ml_list):
                self.cmd_open_millilitres(self.ec_in[index], com_ml)
                self.cmd_open_ms(self.mixer, LAB_MIXER_TIME_SECS)

            try:
                ec_delta =  self.lab.target_ec - self.lab.currentAnalysis.ec
                self.lab.sym.fillEC(ec_delta,50)
            except AttributeError:
                pass

            #recursion
            self.insertAction(Action(LabFillerAction.EC_ADD))
        else:
            self.exit()

    def addPH(self):
        if (self.needPHFill()):
            #compute
            ph_ml = self.lab.ia.getAddPH()

            self.Log("FILL PH", ph_ml)

            ## ACTIONS #####
            self.cmd_open_millilitres(self.ph_in, ph_ml)
            self.cmd_open_ms(self.mixer, LAB_MIXER_TIME_SECS)

            try:
                ph_delta =  self.lab.target_ph - self.lab.currentAnalysis.ph
                self.lab.sym.fillPH(ph_delta,50)
            except AttributeError:
                pass

            #recursion
            #self.cmd_ph_add()
            self.insertAction(Action(LabFillerAction.PH_ADD))
        else:
            self.exit()
            
    ######## LOW LEVEL ######

    def cmd_ec_add(self):
        self.pushAction(Action(LabFillerAction.EC_ADD))

    def cmd_ph_add(self):
        self.pushAction(Action(LabFillerAction.PH_ADD))

    def cmd_water_add(self):
        self.pushAction(Action(LabFillerAction.WATER_ADD))

    def cmd_calib_weight_start(self,pump):
        self.pushAction(Action(LabFillerAction.CALIB_WEIGHT_START,pump))
        
    def cmd_calib_weight_end(self,pump):
        self.pushAction(Action(LabFillerAction.CALIB_WEIGHT_END,pump))

    ######## HI LEVEL ########

    def syncEC(self,endHandler):
        self.endHandler=endHandler
        self.cmd_water_add()
        self.cmd_ec_add()
        pass

    def syncPH(self,endHandler):
        self.endHandler=endHandler
        self.cmd_ph_add()
        pass
    
     ######### VIRTUALS ####

    def onExecute(self, action: Action):

        self.Debug("Execute " , action)
        if (action.name == LabFillerAction.EC_ADD):
            self.end(action)
            self.addEC()
        elif (action.name == LabFillerAction.PH_ADD):
            self.end(action)
            self.addPH()
        elif (action.name == LabFillerAction.WATER_ADD):
            self.end(action)
            self.addWater()
        elif (action.name == LabFillerAction.CALIB_WEIGHT_START):
            self.end(action)
            args = action.value
            weight = args[0].weight.value
            self.Log("weight calib.. END start weight: " ,weight+ "gr")
            args[0].calib.filled_gr_start = float(weight) - float(args[1])
            #print(args[0].calib)
            args[0].calib.save()
        elif (action.name == LabFillerAction.CALIB_WEIGHT_END):
            self.end(action)
            args = action.value
            weight = args[0].weight.value
            self.Log("weight calib.. END weight: " ,weight+ "gr")
            args[0].calib.filled_gr_end = float(weight) - float(args[1])
            args[0].calib.gr_at_seconds =  float( args[0].calib.filled_gr_end)  /  float(args[2] )
            #print(args[0].calib)
            args[0].calib.save()

    def onTickAction(self, action: Action):
        pass

    def onTick(self):
        pass
    
    ################### CALIBRATE

    def pumpById(self,id):
        if (id == self.ec_in[0].id):
            return self.ec_in[0] 
        if (id == self.ec_in[1].id):
            return self.ec_in [1]
        if (id == self.ph_in.id):
            return self.ph_in 

    def calibrate(self,data):
        self.Log(" CALIBRATE", data)
        pump = self.pumpById(data['id'])

        seconds = data['time_secs']
        self.Log(" pump", pump,seconds)

        if (pump.calib.calibrateType =="TIME"):
            self.cmd_open_ms(pump, seconds)
        else:
        
           self.Log("weight calib.. start weight: " , pump.weight.value+ "gr")
           self.cmd_open_ms(pump, seconds)
           self.cmd_calib_weight_start([pump, pump.weight.value,seconds])
           self.cmd_wait(10) ## acqua tirna giù
           self.cmd_calib_weight_end([pump, pump.weight.value,seconds])


    def test_time_pump(self,data):
        
        pump = self.pumpById(data['id'])
        ml = int(data['calib_test_ml'])

        self.Log("TEST TIME PUMP", pump.name , "ml:", ml)
        self.cmd_open_millilitres(pump,ml)
      


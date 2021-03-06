import logging
from ..models import WaterAnalysis
from .Common import *
from .Config import *
from .LabSym import *
from enum import Enum
from datetime import datetime

logger = logging.getLogger(__name__)

class FertilizerComponent:
     def __init__(self,name,ec_1000_x_litre_in_ml):
        self.name=name
        self.ec_1000_x_litre_in_ml=ec_1000_x_litre_in_ml

class Fertilizer:
    components = []
    def __init__(self,name):
        self.name=name
    def addComponent(self,comp):
        self.components.append(comp)

class BCUZZ_Fertilizer(Fertilizer):
     def __init__(self):
        Fertilizer.__init__(self,"BCUZZ A+B")
        self.addComponent(FertilizerComponent("HydroA",LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML ))
        self.addComponent(FertilizerComponent("HydroB",LAB_ATAMI_EC_B_1000_X_LITRO_IN_ML ))

#########################################################################

class LabIA:
    
    def __init__(self,lab):
        self.lab=lab
        self.ferilizer = BCUZZ_Fertilizer()
        pass

    def Log(self,*args):
        LabInfo("[IA " + self.lab.name  +  "]" , *args)

    ## return array of  ec_1000_x_litre_in_ml components 
    def getAddEC(self):

        litres = self.lab.litres()
        ec_delta =  self.lab.target_ec - self.lab.currentAnalysis.ec
        self.Log("sync EC", self.lab.currentAnalysis.ec," TARGET", self.lab.target_ec," Lt:",litres, " delta:",ec_delta)
        
        ret = []
        for com in  self.ferilizer.components:
            #compute
            # X : ec_delta = LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML : 1000
            ec_1000_per_litro = (ec_delta * com.ec_1000_x_litre_in_ml)  / 1000
            #ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML) / 1000
            #ml_a = ec_1000_per_litro * litres 
            ml = ec_1000_per_litro * litres 

            self.Log("EC ",com.name, "ec.fact:",ec_1000_per_litro,"  ml:",ml)

            ret.append(ml)
            #ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_B_1000_X_LITRO_IN_ML) / 1000
            #ml_b = ec_1000_per_litro * litres 

        return ret
        #self.Log("FILL EC", "A ml:" , ml_a," B ml:",ml_b)

    def getAddPH(self):

        litres = self.lab.litres()
        ph_delta =  self.lab.target_ph - self.lab.currentAnalysis.ph
        self.Log("sync PH", self.lab.currentAnalysis.ph," TARGET", self.lab.target_ph," Lt:",litres, " delta:",ph_delta)
        
       
         #compute
        # X : ec_delta = LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML : 1000
        ph_1_per_litro = (ph_delta * LAB_PH_DOWN_1_ML_PER_LITRES / 1000) 
            #ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML) / 1000
            #ml_a = ec_1000_per_litro * litres 
        ml = ph_1_per_litro * litres 

        self.Log("PH ","ph.fact:",ph_1_per_litro,"  ml:",ml)

        return ml

    def getAddWater(self):
 
        litres = self.lab.litres()
        ec_delta =    self.lab.currentAnalysis.ec-self.lab.target_ec
        self.Log("sync EC WATER", self.lab.currentAnalysis.ec," TARGET", self.lab.target_ec," Lt:",litres, " delta:",ec_delta)
         
         #compute
        # X : ec_delta = LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML : 1000
        factor = (ec_delta * LAB_WATER_EC_1000_X_LITRO_IN_LITRES / 1000) 
            #ec_1000_per_litro = (ec_delta * LAB_ATAMI_EC_A_1000_X_LITRO_IN_ML) / 1000
            #ml_a = ec_1000_per_litro * litres 
        litersToAdd = factor * litres 

        self.Log("WATER ","water.fact:",factor,"  litersToAdd:",litersToAdd)

        return litersToAdd
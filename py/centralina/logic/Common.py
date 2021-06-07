
import abc
import logging
import traceback
logger = logging.getLogger(__name__)
from ..models import *
from enum import Enum
from datetime import datetime

lab_symmode = False

def setSymMode(symMode):
    global lab_symmode
    lab_symmode= symMode

def isSymMode():
    global lab_symmode
    return lab_symmode

class SWState(Enum):
     OPEN = "open"
     CLOSE = "close"

class ProxySwitch:
    def __init__(self,sw_id):
        #print("add ",var_id,Variable.objects)
        self.sw=Switch.objects.get(pk=sw_id)
        #print ( self.var)
        self.sw.board.get_controller().register_sw(self.sw.id,self.onWrite)
        self.name = self.sw.name
        self.id=sw_id
        if (self.sw.state == "open"):
                self.state = SWState.OPEN
        else:
                self.state = SWState.CLOSE

    def state(self):
        return self.state

    def isOpen(self):
        return self.state == SWState.OPEN

    def open(self):
        #self.state=SWState.OPEN
        print("SW ", self.sw.name,self.state)
        if (not lab_symmode):
                self.sw.command("open" )
    def close(self):
        #self.state=SWState.CLOSE
        print("SW ", self.sw.name, self.state)
        if (not lab_symmode):
                self.sw.command("close" )

    ## FROM ARDUINO
    def onWrite(self,value):
        if (not lab_symmode):
            print(">>SW ", self.sw.name, value)
            if (value == "open"):
                self.state = SWState.OPEN
            else:
                self.state = SWState.CLOSE
    def __str__(self):
        return "PROXYSW "+self.name

class Pump(ProxySwitch):
    def __init__(self,sw_id):
        ProxySwitch.__init__(self, sw_id) 
        try:
            self.calib = LabPumpCalibrate.objects.get(id=sw_id)
        except:
            logger.error("calib not found "+str( sw_id))
            self.calib = LabPumpCalibrate()

    def __str__(self):
        return "PUMP " +self.name

##############################################

class ProxyVar:
    def __init__(self,var_id):
        #print("add ",var_id,Variable.objects)
        self.var=Variable.objects.get(pk=var_id)
        #print ( self.var)
        self.var.board.get_controller().register_var(self.var.id,self.onWrite)
        self.value = self.var.value

    def get(self):
        return self.value

    def set(self,value):
        self.value=value
        print("SET ", self.var.name, value)
        if (not lab_symmode):
            self.var.board.get_controller().write(self.var.pin,value ) 
    
    ## FROM ARDUINO
    def onWrite(self,value):
        if (not lab_symmode):
            #print(">>SET ", self.var.name, value)
            self.value = value
            
class ECMeter:
    def __init__(self,value_id,k_id):
        try:
            self.value = ProxyVar(value_id)
            self.k = ProxyVar(k_id)
        except Exception  as e:
            traceback.print_exc()
            logger.error (str(e))    
    def get(self):
        return float(self.value.get())
    def set(self,v):
        self.value.set(v)

class PHMeter:
    def __init__(self,value_id,voltage_id,ref_4_id,ref_6_id):
        try:
            self.value = ProxyVar(value_id)
            self.voltage = ProxyVar(voltage_id)
            self.ref_4 = ProxyVar(ref_4_id)
            self.ref_6 = ProxyVar(ref_6_id)
        except Exception  as e:
            traceback.print_exc()
            logger.error (str(e))  
    def get(self):
        return float(self.value.get())
    def set(self,v):
         self.value.set(v)

class Termperature:
    def __init__(self,value_id):
        try:
            self.value = ProxyVar(value_id)
        except Exception  as e:
            logger.error (str(e))  
    def get(self):
        return float(self.value.get())
    def set(self,v):
        self.value.set(v)


class DistanceMeter:
    def __init__(self,value_id):
        try:
            self.value = ProxyVar(value_id)
        except Exception  as e:
            traceback.print_exc()
            logger.error (str(e))  
    def get(self):
        return float(self.value.get())
    def set(self,v):
        self.value.set(v)

#info


#logging
def _LabLog(id,level,*args):
    ret=""
    for arg in args:
       ret+=" " +str(arg)
    if (level=="DEBUG"):
        logger.debug(id+" " +ret)
    elif (level=="WARN"):
        logger.warn(id+" " +ret)
    elif (level=="ERROR"):
        logger.error(id+" " +ret)
    else:
        logger.info(id+" " +ret)

    a = LabLog.create(id,level,ret )
    a.save()
    #print("[LOG] "+datetime.now().strftime("%Y-%m-%d-%H:%M:%S") ,actor,ret)
    

def LabInfo(id,*args):
    _LabLog(id,"INFO",*args)

def LabDebug(id,*args):
    _LabLog(id,"DEBUG",*args)

def LabWarn(id,*args):
    _LabLog(id,"WARN",*args)

def LabError(id,*args):
    _LabLog(id,"ERROR",*args)
#############################################

class Action:
    name=""
    value = None
    onEnd = None
    def __init__(self,name,value=None,onEnd=None):
        self.name=name
        self.value = value
        self.onEnd=onEnd

    def __str__(self):
        if (self.value!=None):
            return "ACTION "+ str(self.name)+" "+self.value.__str__()
        else:
            return "ACTION "+ str(self.name)

class StateMachine(metaclass=abc.ABCMeta):

    #state = "IDDLE"
   

    def __init__(self,name):
        self.name=name
        self.actions = [] ## non mettere nella classe , sono statice ??? 
        self.current_action=None
        pass
  
    def Log(self,*args):
        LabDebug("[STA " + self.name  +  "]" , *args)
    def Debug(self,*args):
        LabDebug("[STA " + self.name  +  "]" , *args)

    def pushAction(self , action):
        #self.Log("Add",action.name)
        self.actions.append(action)

    def insertAction(self , action):
        #self.Log("Add",action.name)
        self.actions.insert(0,action)

    def cmd_wait(self,seconds,onEnd=None):
        self.pushAction( Action("WAIT",seconds))
     
    def cmd_open(self,pump):
        self.pushAction( Action("OPEN",pump))
    
    def cmd_close(self,pump):
        self.pushAction( Action("CLOSE",pump))
      
    def cmd_open_ms(self,pump,seconds):
        self.cmd_open(pump)
        self.cmd_wait( seconds)
        self.cmd_close(pump)

    def cmd_open_millilitres(self,pump,ml):
        self.cmd_open_ms(pump,ml / pump.calib.ml_at_seconds)

    #######################
 
    @abc.abstractmethod
    def onExecute(self, action: Action):
        """Load in the data set"""
        raise NotImplementedError

    @abc.abstractmethod
    def onTickAction(self, action: Action):
        """Load in the data set"""
        raise NotImplementedError

    @abc.abstractmethod
    def onTick(self):
        """Load in the data set"""
        raise NotImplementedError

    def execute(self,action):
        #self.Log("Execute sub " ,action.name)

        if (action.name== "WAIT"):
            self.Log("WAITING ",action.value)
            self.waitingTime = float(action.value)
            self.waitingStart = datetime.now()
            #self.setState("WAITING")
        elif (action.name== "OPEN"):
            self.Log("OPEN ",action.value.name)
            action.value.open()
            self.end(action)

        elif (action.name== "CLOSE"):
            self.Log("CLOSE ",action.value.name)
            action.value.close()
            self.end(action)
        else:
            self.onExecute(action)

    ### end action
    def end(self,action):
        self.Debug("End " , action.__str__())
        #self.setState("IDDLE")
        self.current_action =None

    ###########

    def tick(self):
        #print ( self.name,self.current_action)
        self.onTick()

        if (self.current_action == None):
            if (len(self.actions) > 0):
                self.current_action = self.actions[0]
                del self.actions[0]
                self.execute(self.current_action)
           
        #print ("LAB fill:",self.litres(),self.distance_empty.get() )
        if (self.current_action != None):
            
            if (self.current_action.name == "WAIT"):
                if (datetime.now() - self.waitingStart ).total_seconds() >= self.waitingTime:
                    self.end(self.current_action)
            else:
                self.onTickAction(self.current_action )
          
          
        
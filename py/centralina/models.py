from django.db import models
from django.utils.translation import gettext_lazy as _
# Create your models here.
from centralina.runtime import *
from enum import Enum
from .ws_service import *
import parsedatetime
from datetime import datetime, timezone
import os

class Board(models.Model):
    name = models.CharField(max_length=50)
    description = models.CharField(max_length=100,default='', blank=True, null=True)
    cpu_type = models.CharField(max_length=50,default='', blank=True, null=True)
    usb_address_win = models.CharField(max_length=200,default='', blank=True, null=True)
    usb_address_lx = models.CharField(max_length=200,default='', blank=True, null=True)
    net_address = models.CharField(max_length=200,default='', blank=True, null=True)
    wifi_name = models.CharField(max_length=200,default='', blank=True, null=True)
    enable_cpu = models.BooleanField(default=True)

    def usb_address(self):
        if os.name == 'nt':
            return self.usb_address_win
        else:
            return self.usb_address_lx

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        #self._controller = BoardControl(self)

    def get_controller(self):
         return GetControl(self)

    def get_current(self):
         Board.objects.get(id= request.session['board'] )
        
    def command(self,cmd):

        print("CMD "+str(self)+"=" +str(cmd))
        if (cmd =="restart"):
            self.get_controller().reconnect()
        if (cmd =="stop"):
            self.get_controller().stop()


    def __str__(self):
        return "BOARD "+self.name

class SwitchType(models.Model):
    name = models.CharField(max_length=50)
    description = models.CharField(max_length=100)
    voltage = models.IntegerField(default=12)
    open_value = models.BooleanField(default=True)

    class SwitchMode(models.TextChoices):
        INPUT = 'I', _('Input')
        OUTPUT = 'O', _('Output')

    mode = models.CharField(
        max_length=1,
        choices=SwitchMode.choices,
        default=SwitchMode.INPUT
    )

    def __str__(self):
        return self.name

class Switch(models.Model):
    CMD_OPEN = 'open'
    CMD_CLOSE = 'close'
    CMD_TOGGLE = 'toggle'
    PIN_HI = True
    PIN_LOW = False

 
    #@property
    #def state(self):
    #    print("Getting value...")
    #    return self._runstate

    board = models.ForeignKey(Board, on_delete=models.CASCADE)
    switchType = models.ForeignKey(SwitchType, on_delete=models.CASCADE)
    name = models.CharField(max_length=50)
    description = models.CharField(blank=True,max_length=100)
    pin = models.IntegerField(default=1)
   
    ## runtime
    #state = models.CharField(max_length=10,default='')
    class SwitchState(models.TextChoices):
        UNKNOW = ''
        OPEN = 'open'
        CLOSE = 'close'

    state = models.CharField(
        max_length=5,
        choices=SwitchState.choices,
        default=SwitchState.UNKNOW
    )
    pin_value = models.BooleanField(default=False)

    class StartupMode(models.TextChoices):
        DB = 'db', _('Db')
        HARDWARE = 'hw', _('Hardware')

    startupMode = models.CharField(
        max_length=2,
        choices=StartupMode.choices,
        default=StartupMode.HARDWARE
    )

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        #print ("board",self.board)
        #self._controller = SwitchControl(self.board,self)
        #self._controller = SwitchControl(self)
        # add your own logic

    def pinState(self):
         return self.pin_value

    def setPinValue(self,value):
        #print("set",self.state,self.pin_value,value)
        if (value != None):
            ss = lambda  v : 'open' if v else 'close'
            v=value
            #if (not self.switchType.open_value):
           #     v=not value

            self.state = ss(v)
            self.pin_value=value
            #print("sewt",self.state,self.pin_value)
            self.save()
            #event


    def command(self,cmd):

        print("CMD "+str(self.pin)+"=" +str(cmd))

        new_state = "open"
        if (cmd == self.CMD_CLOSE): # inverto
            new_state = "close"
        elif (cmd == self.CMD_TOGGLE): # inverto
            if (self.state =="open"):
                new_state = "close"

        pin_value = self.PIN_HI
       # if (not self.switchType.open_value):
       #     pin_value=self.PIN_LOW

        #print("a "+str(self.pin)+"=" +str(pin_value))

        if (new_state =="close"):
            pin_value = not pin_value
           
        print("new  "+str(self.pin)+" => " +str(new_state)+" = " +str(pin_value))

        self.state =new_state
        self.pin_value=pin_value
      
        #self.setPinValue(pin_value)

        self.save()

        self.board.get_controller().write(self.pin,pin_value)
        

    def Save(self):
        self.save()
        print("save")

    def __str__(self):
        return self.board.__str__()+" -> "+ self.name

    
var_map = {}

class Variable(models.Model):
    
    board = models.ForeignKey(Board, on_delete=models.CASCADE)
    name = models.CharField(max_length=50)
    description = models.CharField(blank=True,max_length=100)
    value = models.CharField(blank=True,default='',max_length=255)
    pin = models.IntegerField(default=1)
    updated = models.DateTimeField(default=datetime.now)
    
    ## runtime
    #state = models.CharField(max_length=10,default='')
    class VarType(models.TextChoices):
        UNKNOW = ''
        TEXT_BOOL = 'text_bool'
        TEXT_INT = 'text_int'
        TEXT_REAL = 'text_real'
        TEXT_STRING = 'text_string'
        BTN_TOGGLE = 'btn_toggle',
        JSON = 'json',

    varType = models.CharField(
        max_length=12,
        choices=VarType.choices,
        default=VarType.TEXT_STRING
    )

    class SaveMode(models.TextChoices):
        NONE = '', _('None')
        ALWAYS = '0', _('Always')
        sec_10 = '10', _('10 secs')
        sec_30 = '30', _('30 secs')
        min_1 = '60', _('1 min')
        min_10 = '600', _('10 min')
        hour_10 = '3600', _('1 hour')

    saveMode = models.CharField(
        max_length=5,
        choices=SaveMode.choices,
        default=SaveMode.NONE
    )

    class StartupMode(models.TextChoices):
        NONE = '', _('None')
        DB = 'db', _('Db')
        HARDWARE = 'hw', _('Hardware')

    startupMode = models.CharField(
        max_length=2,
        choices=StartupMode.choices,
        default=StartupMode.NONE
    )

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def pinState(self):
         return self.pin_value
   
    def setPinValue(self,value):
        #print("set",self.pin,value)
        if (value != None):
            self.value=value
            #self.updated = datetime.datetime()
            self.save()
            #event

    def command(self,cmd):

        print("CMD VAR "+str(self.pin)+"=" +str(cmd))
        if (cmd =="TOGGLE"):
            self.value = not (str(self.value) =="True")
            self.board.get_controller().write(self.pin, self.value)

    def save(self, *args, **kwargs):
        #def Save(self):
        self.updated = datetime.now()
        #print ("save", self)
        if (self.saveMode!=""):
            #history
            ss = int(self.saveMode)
            
            if (self.id in  var_map):
                tt =  var_map[self.id].updated
                #print (datetime.now())
                #print (tt)
                elapsedTime = datetime.now()  - tt
                if (elapsedTime.total_seconds() > ss):
                    #print ("history")
                    var_map[self.id] =  self
                    v = VariableHistory.create(self,float(self.value))
                    v.save()
            else:
                var_map[self.id] =  self
                v = VariableHistory.create(self,float(self.value))
                v.save()
            

        super(Variable, self).save(*args, **kwargs)
        #super().save(*args, **kwargs)

    def __str__(self):
        return self.board.__str__()+" . "+ self.name

   

class VariableHistory(models.Model):
    time = models.DateTimeField(primary_key=True, default=datetime.now)
    variable = models.ForeignKey(Variable, on_delete=models.CASCADE)
    value = models.FloatField()

    @classmethod
    def create(cls, variable,value):
        vv = cls(variable=variable,value=value)
        return vv

    def save(self, *args, **kwargs):
        self.save_and_smear_timestamp(*args, **kwargs)
    
    def save_and_smear_timestamp(self, *args, **kwargs):
        """Recursivly try to save by incrementing the timestamp on duplicate error"""
        try:
            super().save(*args, **kwargs)
        except IntegrityError as exception:
            # Only handle the error:
            #   psycopg2.errors.UniqueViolation: duplicate key value violates unique constraint "1_1_farms_sensorreading_pkey"
            #   DETAIL:  Key ("time")=(2020-10-01 22:33:52.507782+00) already exists.
            if all (k in exception.args[0] for k in ("Key","time", "already exists")):
                # Increment the timestamp by 1 µs and try again
                self.time = str(parse_datetime(self.time) + datetime.timedelta(microseconds=1))
                self.save_and_smear_timestamp(*args, **kwargs)

#####################################
# LAB
#####################################

class WaterAnalysis(models.Model):
    tank=models.CharField(max_length=20)
    ph =models.FloatField(default=0)
    ec=models.FloatField(default=0)
    temperature = models.FloatField(default=0)
    time = models.DateTimeField(primary_key=True, default=datetime.now)
  
    @classmethod
    def create(cls, tank,ph,ec,temperature):
        vv = cls(tank=tank,ph=ph,ec=ec,temperature=temperature)
        return vv

    def __str__(self):
        return "TANK "+self.tank+" ph:"+str(self.ph)+" ec:" + str(self.ec)+" temp:"+ str(self.temperature)

class LabLog(models.Model):
    time = models.DateTimeField(primary_key=True, default=datetime.now)
    id=models.CharField(max_length=10)
    level=models.CharField(max_length=10)
    message=models.TextField()
  
    @classmethod
    def create(cls, id,level,message):
        vv = cls(id=id,level=level,message=message)
        return vv

    def __str__(self):
        return "LOG "+self.id+" "+str(self.time) +" " +str(self.level)+" " + str(self.message)


class LabAI(models.Model):
    time = models.DateTimeField(primary_key=True, default=datetime.now)
    tank=models.CharField(max_length=20)
     
    class OperationType(models.TextChoices):
        EC_ADD = 'ec_add'
        PH_ADD = 'ph_add'
        WATER_ADD = 'water_add'
    
    operationType = models.CharField(
        max_length=10,
        choices=OperationType.choices,
        default=OperationType.EC_ADD
    )
    lab_liters =models.FloatField(default=0)
    estimate_tank_liters =models.FloatField(default=0)
    start_value =models.FloatField(default=0)
    target_value =models.FloatField(default=0)
    final_value =models.FloatField(default=0)
    value_to_ml_factor =models.FloatField(default=0)

class LabPumpCalibrate(models.Model):
    time = models.DateTimeField(primary_key=True, default=datetime.now)
    id=models.IntegerField(default=0)
    time_secs=models.IntegerField(default=0)
    #readed
    filled_ml=models.IntegerField(default=0)
    filled_gr_end=models.IntegerField(default=0)
    filled_gr_start=models.IntegerField(default=0)
    
    class CalibrateType(models.TextChoices):
        TIME = 'TIME'
        WEIGHT = 'WEIGHT'
    
    calibrateType = models.CharField(
        max_length=10,
        choices=CalibrateType.choices,
        default=CalibrateType.TIME
    )

    # calcolato
    ml_at_seconds=models.FloatField(default=0)
    gr_at_seconds=models.FloatField(default=0)
    gr_lost=models.IntegerField(default=0)


class WaterAdditive(models.Model):
    name=models.CharField(max_length=20)
    description=models.CharField(max_length=50)

    class WaterAdditiveType(models.TextChoices):
        PH_DOWN = 'PH_DOWN'
        PH_UP= 'PH_UP'
        FERTILIZER = 'FERTILIZER'
        WATER_WELL = 'WATER_WELL'
        WATER_OSMOTIC = 'WATER_OSMOTIC'
    
    additiveType = models.CharField(
        max_length=15,
        choices=WaterAdditiveType.choices,
        default=WaterAdditiveType.PH_DOWN
    )


  
  
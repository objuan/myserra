from django.db import models
from django.utils.translation import gettext_lazy as _
# Create your models here.
from centralina.runtime import *
from enum import Enum
from .ws_service import *

class Board(models.Model):
    name = models.CharField(max_length=50)
    description = models.CharField(max_length=100,default='', blank=True, null=True)
    cpu_type = models.CharField(max_length=50,default='', blank=True, null=True)
    usb_address = models.CharField(max_length=200,default='', blank=True, null=True)
    net_address = models.CharField(max_length=200,default='', blank=True, null=True)
    wifi_name = models.CharField(max_length=200,default='', blank=True, null=True)

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._controller = BoardControl(self)

    def onConnect(self):
        self._controller.onConnect()

    def get_controller(self):
         return self._controller 

    def get_current(self):
         Board.objects.get(id= request.session['board'] )
        
    def command(self,cmd):

        print("CMD "+str(self)+"=" +str(cmd))
        if (cmd =="restart"):
            self._controller.reconnect()
        if (cmd =="stop"):
            self._controller.stop()
    def tick(self):
        self._controller.tick()

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

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        #print ("board",self.board)
        self._controller = SwitchControl(self.board,self)
        #self._controller = SwitchControl(self)
        # add your own logic

    def pinState(self):
         return self.pin_value

    def setPinValue(self,value):
        print("set",self.state,self.pin_value,value)
        if (value != None):
            ss = lambda  v : 'open' if v else 'close'
            v=value
            if (not self.switchType.open_value):
                v=not value

            self.state = ss(v)
            self.pin_value=value
            print("sewt",self.state,self.pin_value)
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
        if (not self.switchType.open_value):
            pin_value=self.PIN_LOW

        #print("a "+str(self.pin)+"=" +str(pin_value))

        if (new_state =="close"):
            pin_value = not pin_value
           
        print("new  "+str(self.pin)+" => " +str(new_state)+" = " +str(pin_value))

        self.state =new_state
        self.pin_value=pin_value
      
        #self.setPinValue(pin_value)

        self.save()
        self._controller.setPinValue(pin_value)
            
    # value : open  | close
    '''
    def setState(self,state_value):
        print("setPinValue "+str(self.pin)+"=" +str(pin_value))
2
        #ss = lambda  v : 'open' if v else 'close'
        self.state =ss(state_value)
        self.save()
        
        if (state_value == "open"):
            setPinValue(True)
        else:
             setPinValue(True)
  '''     
    #pin_value = True, False
    def setPinValue_bp(self,pin_value):
        print("setPinValue "+str(self.pin)+"=" +str(pin_value))

        self.pin_value=pin_value

        self._controller.setPinValue(pin_value)

        #ss = lambda  v : 'open' if v else 'close'
        #self.state =ss(pin_value)
        #elf.save()

        #if (pin_value == self.PIN_HI):
        #    print ("Set Pin " + str(self.pin)+"=" + "HI")
        #else:
        #    print ("Set Pin " + str(self.pin)+"=" + "LOW")
    def Save(self):
        self.save()
        print("save")

    def __str__(self):
        return self.board.__str__()+" -> "+ self.name

    
   


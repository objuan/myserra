from django.db import models

# Create your models here.

class Board(models.Model):
    name = models.CharField(max_length=50)
    description = models.CharField(max_length=100,default=None, blank=True, null=True)
    cpu_type = models.CharField(max_length=50,default=None, blank=True, null=True)
    usb_address = models.CharField(max_length=200,default=None, blank=True, null=True)
    net_address = models.CharField(max_length=200,default=None, blank=True, null=True)
    wifi_name = models.CharField(max_length=200,default=None, blank=True, null=True)

    def get_current(self):
         Board.objects.get(id= request.session['board'] )
        
    def __str__(self):
        return self.name

    

class SwitchType(models.Model):
    name = models.CharField(max_length=50)
    description = models.CharField(max_length=100)
    voltage = models.IntegerField(default=12)
    def __str__(self):
        return self.name

class Switch(models.Model):
    CMD_OPEN = 'open'
    CMD_CLOSE = 'close'
    CMD_TOGGLE = 'toggle'
    PIN_HI = True
    PIN_LOW = False

    board = models.ForeignKey(Board, on_delete=models.CASCADE)
    switchType = models.ForeignKey(SwitchType, on_delete=models.CASCADE)
    name = models.CharField(max_length=50)
    description = models.CharField(blank=True,max_length=100)
    pin = models.IntegerField(default=1)
    on_hi = models.BooleanField(default=True)
    ## runtime
    state = models.CharField(max_length=10)

    def pinState(self):
         return self.state == "open" 

    def command(self,cmd):

        print("a "+str(self.pin)+"=" +str(cmd))

        pin_value = self.PIN_HI
        if (not self.on_hi):
            pin_value=self.PIN_LOW
        print("a "+str(self.pin)+"=" +str(pin_value))

        if (cmd == self.CMD_CLOSE): # inverto
            pin_value = not pin_value
        elif (cmd == self.CMD_TOGGLE): # inverto
            pin_value = not self.pinState()

        print("a "+str(self.pin)+"=" +str(pin_value))

        self.setPinValue(pin_value)
            
    # value : True = HI
    def setPinValue(self,pin_value):
        print("setPinValue "+str(self.pin)+"=" +str(pin_value))

        ss = lambda  v : 'open' if v else 'close'
        self.state =ss(pin_value)
        self.save()
        if (pin_value == self.PIN_HI):
            print ("Set Pin " + str(self.pin)+"=" + "HI")
        else:
            print ("Set Pin " + str(self.pin)+"=" + "LOW")

    def __str__(self):
        return self.board.__str__()+" -> "+ self.name

    
   


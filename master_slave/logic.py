import time
from datetime import datetime
from arduino import *

SWITCH_HI = 0
SWITCH_LOW = 1

class Switch:

    def __init__(self,name,pin) :
        print("SWITCH ADD ", name,"pin",pin)
        self.name=name
        self.pin=pin
        self.open=False
        self.timeEnabled=True
        self.timeActive=False
        pinMode(pin, OUTPUT)
        digitalWrite(self.pin,SWITCH_LOW)
        pass

    def setTime(self,start,end):
        self.start =  datetime.strptime(start, "%H:%M:%S")
        self.end = datetime.strptime(end, "%H:%M:%S")
        print("SET TIME", self.name,"start:",self.start,"end:",self.end)

    def eval(self,datetime):

        if (not self.timeEnabled):
            return
        
        self.timeActive =  (datetime>= self.start and datetime<= self.end)
       
        if ( self.open != self.timeActive):
            print(self.name," STATE ", self.open )

            self.open=self.timeActive
            if (self.timeActive):
                digitalWrite(self.pin,SWITCH_HI)
            else:
                digitalWrite(self.pin,SWITCH_LOW)

        pass
    def toggle(self):
        print(self.name," TOGGLE " )
        self.open=not  self.open
        self.timeEnabled=False
        if ( self.open):
                digitalWrite(self.pin,SWITCH_HI)
        else:
                digitalWrite(self.pin,SWITCH_LOW)

    def toggleAuto(self):
        print(self.name," TOGGLE AUTO" )
        self.timeEnabled=not  self.timeEnabled
      
    def desc(self):
        return self.name+ " state:"+ str(self.open)+" " \
            +"start:"+str(self.start)+ "end:"+ str(self.end)\
            + " timeEn:"+ str(self.timeEnabled)\
            + " timeActive:"+ str(self.timeActive)


# ==========
# start time
ortoLungo=None
ortoLungo_PIN=22
ortoLungo_start_time = "21:51:00"
ortoLungo_end_time = "21:52:00"

ortoCasa=None
ortoCasa_PIN=24
ortoCasa_start_time = "21:51:00"
ortoCasa_end_time = "21:52:00"

def getOrtoLungo():
    return ortoLungo

def getOrtoCasa():
    return ortoCasa

def setup():
    print("setup init")

    '''
    pinMode(2,OUTPUT)
    digitalWrite(2,1)
    analogWrite(3,22)
    analogRead(3)
    digitalRead(2)
    '''

    global ortoLungo
    ortoLungo = Switch("OrtoLungo",ortoLungo_PIN)
    ortoLungo.setTime(ortoLungo_start_time,ortoLungo_end_time)

    global ortoCasa
    ortoCasa = Switch("OrtoCasa",ortoCasa_PIN)
    ortoCasa.setTime(ortoCasa_start_time,ortoCasa_end_time)

    print("setup end")

def loop():

    now = datetime.now()
    _current_time = now.strftime("%H:%M:%S")
    current_time  = datetime.strptime(_current_time , "%H:%M:%S")

    #print(current_time)

    ortoLungo.eval(current_time)
    ortoCasa.eval(current_time)

    time.sleep(1)
    pass


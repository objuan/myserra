import time
from datetime import datetime
from arduino import *


class Switch:

    def __init__(self,name,pin) :
        print("SWITCH ADD ", name,"pin",pin)
        self.name=name
        self.pin=pin
        self.open=False
        pinMode(pin, OUTPUT)
        pass

    def setTime(self,start,end):
        self.start =  datetime.strptime(start, "%H:%M:%S")
        self.end = datetime.strptime(end, "%H:%M:%S")
        print("SET TIME", self.name,"start:",self.start,"end:",self.end)

    def eval(self,datetime):

        active = (datetime>= self.start and datetime<= self.end)
       
        if ( self.open != active):
            print(self.name," STATE ", self.open )

            self.open=active
            if (active):
                digitalWrite(self.pin,1)
            else:
                digitalWrite(self.pin,0)

        pass
    def toggle(self):
        print(self.name," TOGGLE " )
        self.open=not  self.open
        if ( self.open):
                digitalWrite(self.pin,1)
        else:
                digitalWrite(self.pin,0)
    
    def desc(self):
        return self.name+ " state:"+ str(self.open)+" "+"start:"+str(self.start)+ "end:"+ str(self.end)

# ==========
# start time
ortoLungo=None
ortoLungo_PIN=2
ortoLungo_start_time = "21:51:00"
ortoLungo_end_time = "21:52:00"

ortoCasa=None
ortoCasa_PIN=3
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

    print(current_time)

    ortoLungo.eval(current_time)
    ortoCasa.eval(current_time)

    time.sleep(1)
    pass


import serial
import time
import threading


INPUT = 'I'
OUTPUT = 'O'

conn=None

end_param='\x00'
end_block='\x01'

def setConnection(c):
    global conn
    conn=c

def send(msg):
    #print(">>" + msg)
    conn.write((msg+"\n").encode())
    #conn.write(end_block.encode())

def pinMode( pin, mode):
    print (">pinMode",pin,mode)
    send(""+str(pin)+" S " +str(mode))
  
def digitalWrite( pin, value):
    print (">digitalWrite",pin,value)
    send(""+str(pin)+" W D " +str(value))

def analogWrite( pin, value):
    print (">analogWrite",pin,value)
    send(""+str(pin)+" W A " +str(value))

readedValue=None

def analogRead( pin):
    print (">analogRead",pin)
    global readedValue
    readedValue=None
    #print ("pinMode",pin,mode)
    send(""+str(pin)+" R A ")
    while(readedValue== None):
        pass
    print (">analogRead",pin,"=",readedValue )
    return readedValue

def digitalRead( pin):
    print (">digitalRead..",pin)
    global readedValue
    readedValue=None
    #print ("pinMode",pin,mode)
    send(""+str(pin)+" R D ")
    while(readedValue== None):
        pass
    print (">digitalRead",pin,"=",readedValue )
    return readedValue


started=False
def isStarted():
    readBuffer()
    return started
    
def readBuffer():
  global readedValue
  while conn.in_waiting > 0:
    l = conn.readline()
    line = l.decode('utf-8').rstrip()
    print("<=",line)
    data = line.split(' ')
    if (data[0] == '[LOG]'):
        args = line.split(sep=end_param)
        #print (args)
        if (args[1] == "INIT"):
            global started 
            started = True

        if (args[1] == "<<analogRead("):
            readedValue=args[6]
            #print("< "+readedValue)

        if (args[1] == "<<digitalRead("):
            readedValue=args[6]
            #print("< "+readedValue)
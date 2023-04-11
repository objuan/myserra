import serial
import time
import threading

from flask import Flask, render_template, Response, request, redirect, url_for

host_name = "0.0.0.0"
port = 80
app = Flask(__name__)

'''
INPUT = 'I'
OUTPUT = 'O'

conn=None
end_param='\x00'
end_block='\x01'

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
'''
# ====================

from arduino import *
from logic import *

# ====================

'''
def loop_thread():
      while True:
        readBuffer()
        loop()
        time.sleep(0.01)

def readBuffer():
  global readedValue
  while conn.in_waiting > 0:
    l = conn.readline()
    line = l.decode('utf-8').rstrip()
    #print("<=",line)
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
    
   
started=False
def isStarted():
    readBuffer()
    return started

'''  

running=True

def start_thread():
    while not isStarted():
        readBuffer()
        time.sleep(0.01)

def loop_thread():
      while running:
        readBuffer()
        loop()
        time.sleep(0.01)

@app.route("/s")
def hello_world():
    return "<p>Serra console!</p>"

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/ortoLungo/", methods=['POST'])
def call_ortoLungo():
    #Moving forward code
    getOrtoLungo().toggle()
    forward_message =getOrtoLungo().desc()
    return render_template('index.html', forward_message=forward_message)

@app.route("/ortoCasa/", methods=['POST'])
def call_ortoCasa():
    #Moving forward code
    getOrtoCasa().toggle()
    forward_message =getOrtoCasa().desc()
    return render_template('index.html', forward_message=forward_message)

#t = threading.Thread(target=lambda: app.run(host=host_name, port=port, debug=True, use_reloader=False))
t = threading.Thread(target=lambda: app.run(host=host_name, port=port))
t.start()

try:
    with serial.Serial('COM5', 9800, timeout=1) as ser:
        setConnection(ser)
        #conn=ser
        
        x = threading.Thread(target=start_thread, args=())
        x.start()

        while not isStarted():
            pass

        print("=== STARTED ===")
        setup()

        x = threading.Thread(target=loop_thread, args=())
        x.start()

        while running:
            pass

except KeyboardInterrupt:
    running=False
    pass



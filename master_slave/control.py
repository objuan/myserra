import serial
import time
import threading

from flask import Flask, render_template, Response, request, redirect, url_for

serial_port='COM6'
#host_name = "0.0.0.0"
host_name = "127.0.0.1"
port = 81
app = Flask(__name__)

# ====================

from arduino import *
from logic import *

# ====================


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

def returnStd():
    ortoLungo_message =getOrtoLungo().desc()
    ortoCasa_message =getOrtoCasa().desc()
    return render_template('index.html', ortoLungo_message=ortoLungo_message,ortoCasa_message=ortoCasa_message)

@app.route("/")
def index():
    return returnStd()

@app.route("/ortoLungo/", methods=['POST'])
def call_ortoLungo():
    #Moving forward codecmd
    getOrtoLungo().toggle()
    return returnStd()

@app.route("/ortoLungo_auto/", methods=['POST'])
def call_ortoLungo_auto():
    #Moving forward codecmd
    getOrtoLungo().toggleAuto()
    return returnStd()

@app.route("/ortoCasa/", methods=['POST'])
def call_ortoCasa():
    #Moving forward code
    getOrtoCasa().toggle()
    return returnStd()

@app.route("/ortoCasa_auto/", methods=['POST'])
def call_ortoCasa_auto():
    #Moving forward code
    getOrtoCasa().toggleAuto()
    return returnStd()

#t = threading.Thread(target=lambda: app.run(host=host_name, port=port, debug=True, use_reloader=False))
t = threading.Thread(target=lambda: app.run(host=host_name, port=port))
t.start()

try:
    with serial.Serial(serial_port, 9800, timeout=1) as ser:
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



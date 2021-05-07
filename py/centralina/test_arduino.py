#!/usr/bin/env python3
from sys import stdout
import time
import sys
#from cloud import *

from pyfirmata2 import Arduino, util,INPUT
from utils import *

PORT = "COM10"   #'/dev/tty.usbserial-A6008rIF'
baud_rate = 9600
end_param='\x00'

class AnalogPrinter:

    def __init__(self):
        # sampling rate: 10Hz
        self.samplingRate = 10
        self.timestamp = 0
        self.board = Arduino(PORT)

    def start(self):
        self.board.analog[0].register_callback(self.myPrintCallback)
        self.board.samplingOn(1000 / self.samplingRate)
        self.board.analog[0].enable_reporting()

    def myPrintCallback(self, data):
        print("%f,%f" % (self.timestamp, data))
        self.timestamp += (1 / self.samplingRate)

    def stop(self):
        self.board.samplingOff()
        self.board.exit()

# sampling rate: 10Hz
samplingRate = 10

if __name__ == '__main__':

    PORT =  Arduino.AUTODETECT

    Log("Connecting " + str(PORT))
    #memory = SharedMemory()
    board = Arduino(PORT)
    #board.digital[13].write(1)

    Log("Connected")

    board.samplingOn(1000 / samplingRate)

    #mega = {
    #         'digital' : tuple(x for x in range(54)),
    #         'analog' : tuple(x for x in range(16)),
    #        'pwm' : tuple(x for x in range(2,14)),
    #        'use_ports' : True,
    #         'disabled' : (0, 1, 14, 15) # Rx, Tx, Crystal
    #         }

    def myCallback(v):
        print("kk",v)

    #board.analog[0].register_callback(myCallback)
    #board.analog[0].enable_reporting()

    #digital_0 = board.get_pin('d:6:i')
    #digital_0.enable_reporting()

    #osmosi = OsmosiBoard(board)

    #client = ArduinoClient(port,baud_rate,memory)
    #client.start()
      
    #osmosi = OsmosiBoard(client, memory)
    #it = util.Iterator(board)
    #it.start()
    #board.analog[0].enable_reporting()
    #board.analog[0].read()

    #analog_0 = board.get_pin('a:0:i') #‘i’ for input, ‘o’ for output, ‘p’ for pwm

    board.digital[5].mode = INPUT
    while True:

        v = board.digital[5].read()
        print(v)
        #if str(digital_0.read()) == 'True':
        #    print("Button pressed")
        #elif str(digital_0.read()) == 'False':
        #    print("Button not pressed")
        #else:
        #    print("Button has never been pressed")

        #client.tick()
        #osmosi.tick()
        time.sleep(1)

    board.exit()
         
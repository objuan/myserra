#!/usr/bin/env python3
from sys import stdout
import time
import sys
from cloud import *
from osmosi import *
from lab import *


port = "COM5"
baud_rate = 115200

if __name__ == '__main__':

    
    memory = SharedMemory()

    client = ArduinoClient(port,baud_rate,memory)
    client.start()
      
    osmosi = OsmosiBoard(client, memory)
    lab = LabBoard(client, memory)

    while True:
        client.tick()
        osmosi.tick()
        lab.tick()
        time.sleep(0.1)
         
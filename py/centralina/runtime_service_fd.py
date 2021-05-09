
from django.db import models
from django.utils.translation import gettext_lazy as _
from enum import Enum
import json
from .models import *
from .runtime import Connect_Event

from .runtime import MustReconnect,OnReconnect,RegisterArduino,GetArduino
from pyfirmata2 import Arduino, util
import threading
import time
import logging

logger = logging.getLogger(__name__)


def ConnectBoards():
    logger.info ("------INIT ARDUINO-----------")
    OnReconnect()

    PING_PIN = 2
    
    def Connect(board):
        try:
            Connect_Event("CONNECTING " + board.usb_address)    

            #arduino = Arduino(board.usb_address)
            arduino = Arduino(Arduino.AUTODETECT)
            RegisterArduino(board.usb_address,arduino)
            logger.info ("CONNECTED"  + board.usb_address)
            Connect_Event("CONNECTED "+ board.usb_address)    
            
            #inizializzo i pin in ingrresso
         
            board.onConnect() 
            '''
            for sw in board.switch_set.all():
                 logger.info ("SWITCH START " + sw.name)
                 if (sw.switchType.mode=="O"):
                    logger.info ("INIT VALUE %d %d" , sw.pin , sw.pin_value)
                    arduino.digital[sw.pin].write(sw.pin_value)
            '''
            return True

        except Exception  as e:
            logger.error ("ERROR CONNETTING " + board.usb_address+ " "+str(e))    
            Connect_Event("ERROR CONNETTING")    
            return False


    for b in Board.objects.all():
        logger.info ("BOARD " + b.name +" " + b.usb_address)
        #board_map[b.id] = BoardControl(b)
        try:

            Connect(b)

            logger.info("START TIMER")

            def Timer(memory):
                c=0
                while True:
                    if (MustReconnect()):
                        logger.info ("RECONNECT")
                        for b in Board.objects.all():
                            if (Connect(b)):
                                OnReconnect()
                     
                    #print ("TICK",c, memory.connection)
                    c=c+1
                    time.sleep(1)

            def Ping(board):
                c=0
 
                while True:
                    #v = GetArduino(board).digital[PING_PIN].read(PING_WRITE_PIN)
                    #if (not cont.read(PING_WRITE_PIN)):
                    #    Event("PING ERROR")    
                    #else:
                    #    Event("PING OK")    

                   
                    #print ("PING")

                    board.tick()
                  
                    c=c+1
                    time.sleep(1)

            t = threading.Thread(target=Timer,args=[memory],daemon=True)
            t.start()

            ping = threading.Thread(target=Ping,args=[b],daemon=True)
            ping.start()

        except Exception  as e:
            logger.error ("ERROR CONNETTING "+str(b.usb_address)+str(e))
            
    logger.info ("----------------")

ConnectBoards()





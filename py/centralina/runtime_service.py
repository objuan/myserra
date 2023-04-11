
from django.db import models
from django.utils.translation import gettext_lazy as _
from enum import Enum
import json
from .models import *
from .runtime import *
import datetime
from .runtime import RegisterControl,GetControl,RegisterManager #OnReconnect MustReconnect
from .cloud import *
import threading
import time
import logging
import traceback
from .config import *
from .logic import *

logger = logging.getLogger(__name__)

arduino_map = {}
arduino_list = []
control_list = []

class BoardManager():

    shared_memory = SharedMemory()
    ancora =True

    def ConnectArduino(self,memory,arduino):
        logger.info ("------INIT ARDUINO AT "+arduino.port)

        try:
        
                    Connect_Event("CONNECTED "+ arduino.port)    
                    
                    #inizializzo i pin in ingrresso

                    ## system message

                    dt = datetime.now()

                    print ("CURRENT DATE" , dt)
                    memory.write(arduino,DATETIME_SET_VPIN,dt.strftime("%Y-%m-%d-%H-%M-%S"))
                    # board

                    try:
                        for b in Board.objects.all():  
                            if (b.enable_cpu):
                                client = SharedClient(memory,arduino)
                                control = BoardControl(b,client)
                                b._controller = control
                                control_list.append(control)
                                control.onConnect() 

                                RegisterControl(b,control)

                                logger.info("CONTROLLER TOTAL " + str(len(control_list)))

                        Connect_Event("CONNECTED AT"+str(arduino.port) )

                        self.manager =  LogicManager()

                        
                    except Exception  as e:
                        traceback.print_exc()
                        logger.error ("ERROR INIT " + b.name+ " "+str(e))    
                        Connect_Event("ERROR INIT")  

                    return True

        except Exception  as e:
                traceback.print_exc()
                logger.error ("ERROR CONNETTING " + arduino.port+ " "+str(e))    
                Connect_Event("ERROR CONNETTING")    
                return False

    # entry point
    def ConnectBoards(self):
        global ancora
        ancora =True
        logger.info ("------INIT ARDUINO-1----------")

        for b in Board.objects.all():
                logger.info ("Start "+str(b.name))

                if (not b.usb_address() in  arduino_map):
                    a= ArduinoClient(b.usb_address(),115200,self.shared_memory)
                    arduino_map[b.usb_address()] =  a
                    arduino_list.append(a)
                    a.start()
                #ConnectArduino(arduino_map[b.usb_address])

        def Timer():
                    c=0
                    while ancora:
                        
                        for arduino in arduino_list:
                            if (arduino.popConnChanged()):
                                if (arduino.isReady):
                                    client = self.ConnectArduino(self.shared_memory,arduino)
                                else:
                                    Connect_Event("DISCONNECTED" )
                                    for c in control_list:
                                        if (c.client.arduino == arduino):
                                            logger.info("CONTROLLER REMOVED " +str(c.board.name))
                                            control_list.remove(c)
                                            logger.info("CONTROLLER TOTAL " + str(len(control_list)))
                                        

                        #    if ( not arduino.isReady):
                        #        logger.info ("RECONNECT")
                        #        ConnectArduino(shared_memory,arduino)
                        # 
                        #print ("TICK",c)
                        #c=c+1
                        time.sleep(2)
        
        def Ping():
                    c=0
    
                    while ancora:
                        for arduino in arduino_list:
                            arduino.ping()

                        c=c+1
                        time.sleep(1)

        def DtSync():

                    while ancora:
                        time.sleep(3600)

                        for arduino in arduino_list:
                            dt = datetime.now()
                            print ("CURRENT DATE" , dt)
                            self.shared_memory.write(arduino,DATETIME_SET_VPIN,dt.strftime("%Y-%m-%d-%H-%M-%S"))
                   

        t = threading.Thread(target=Timer,args=[],daemon=True)
        t.start()

        ping = threading.Thread(target=Ping,args=[],daemon=True)
        ping.start()

        dt_sync = threading.Thread(target=DtSync,args=[],daemon=True)
        dt_sync.start()

    def Start(self):
        self.ConnectBoards()

    def reconnect(self):
        global arduino_map,arduino_list,control_list
     
        self.ConnectBoards()

    def stop(self):
        global arduino_map,arduino_list,control_list
     
        Connect_Event("DISCONNECTED" )
        for arduino in arduino_list:
            print("stop")
            arduino.stop()
        arduino_map = {}
        arduino_list = []
        control_list = []
     
# commentare per la migrazione

#main_control = BoardManager()
#main_control.Start()

#RegisterManager(main_control)









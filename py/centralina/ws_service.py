import json
import asyncio
import async_to_sync
from channels.generic.websocket import WebsocketConsumer
import threading
import time

_log=None
_conn=None
_sw=None
_var=None

def GetLog():
    #print("Wlog ",str(_log))
    return _log

def GetConn():
    #print("Wlog ",str(_log))
    return _conn

def GetSWEvent():
    #print("Wlog ",str(_log))
    return _sw

def GetVarEvent():
    #print("Wlog ",str(_log))
    return _var

class ConnectionConsumer(WebsocketConsumer):
    def __init__(self):
        global _conn
        WebsocketConsumer.__init__(self)
        _conn=self


    def Timer(self):
        #c=0
        while self.Ancora:
                    #print("tick",c)
                    #c=c+1
                    for m in self.messages:
                        #print(m)
                        self.send(m)

                    self.messages.clear()
                    time.sleep(1)

    def connect(self):
        print("WS CONNECTED")
        self.messages = []
        self.accept()
        self.Ancora=True
        self.task= threading.Thread(target=self.Timer,args=[],daemon=True)
        self.task.start()

    #@shared_task
    def fire(self,message):
        #print("FIRE " , message)
        self.messages.append(str(message))

    def disconnect(self, close_code):
        print("WS DISCONNECTED")
        self.Ancora=False
        pass


class VarEventConsumer(WebsocketConsumer):
    def __init__(self):
        global _var
        WebsocketConsumer.__init__(self)
        _var=self


    def Timer(self):
        #c=0
        while self.Ancora:
                    #print("tick",c)
                    #c=c+1
                    for m in self.messages:
                        #print(m)
                        self.send(m)

                    self.messages.clear()
                    time.sleep(1)

    def connect(self):
        print("WS CONNECTED")
        self.messages = []
        self.accept()
        self.Ancora=True
        self.task= threading.Thread(target=self.Timer,args=[],daemon=True)
        self.task.start()

    #@shared_task
    def fire(self,message):
        #print("FIRE " , message)
        self.messages.append(str(message))

    def disconnect(self, close_code):
        print("WS DISCONNECTED")
        self.Ancora=False
        pass

class SWEventConsumer(WebsocketConsumer):
    def __init__(self):
        global _sw
        WebsocketConsumer.__init__(self)
        _sw=self


    def Timer(self):
        #c=0
        while self.Ancora:
                    #print("tick",c)
                    #c=c+1
                    for m in self.messages:
                        #print(m)
                        self.send(m)

                    self.messages.clear()
                    time.sleep(1)

    def connect(self):
        print("WS CONNECTED")
        self.messages = []
        self.accept()
        self.Ancora=True
        self.task= threading.Thread(target=self.Timer,args=[],daemon=True)
        self.task.start()

    #@shared_task
    def fire(self,message):
        #print("FIRE " , message)
        self.messages.append(str(message))

    def disconnect(self, close_code):
        print("WS DISCONNECTED")
        self.Ancora=False
        pass

class LogConsumer(WebsocketConsumer):
    def __init__(self):
        global _log
        WebsocketConsumer.__init__(self)
        #print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
        _log=self


    def Timer(self):
        #c=0
        while self.Ancora:
                    #print("tick",c)
                    #c=c+1
                    for m in self.messages:
                        #print(m)
                        self.send(m)

                    self.messages.clear()
                    time.sleep(1)


    def connect(self):
        print("WS CONNECTED")
        self.messages = []
        #(self.channel_layer.group_add( "room","ch"))
        self.accept()

        self.Ancora=True

        self.task= threading.Thread(target=self.Timer,args=[],daemon=True)
           
        self.task.start()
        #self.send("pippo")

    #@shared_task
    def fire(self,message):
        self.messages.append(message)

    def disconnect(self, close_code):
        print("WS DISCONNECTED")
        self.Ancora=False
        pass

    '''     
    def receive(self, text_data):
        print("receive",text_data)
        text_data_json = json.loads(text_data)
        message = text_data_json['message']

        self.send(text_data=json.dumps({
            'message': message
        }))
    '''


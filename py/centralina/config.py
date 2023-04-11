
DATETIME_SET_VPIN=20

import json

config_obj=None

print("load config")

with open('cfg/board.json', 'r') as f:
    config_obj = json.load(f)

#for  x  in config_obj:  
#    print(x["ID"])

def getConfig():
    return  config_obj

def saveConfig(data):
    global config_obj
    with open('cfg/board.json', 'w') as f:
        config_obj = data
        print(config_obj)
        json_string = json.dumps(data)
        f.write(json_string)

def getBoard(id):
    for x in config_obj:
        if (x["ID"]== id):
            return x
    return None

def getPin(id,number):
    b = getBoard(id)
    for x in b["PINS"]:
        if (str(x["PIN"])== str(number)):
            return x
    return None
#print(config_obj)
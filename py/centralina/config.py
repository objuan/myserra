
DATETIME_SET_VPIN=20

import json

config_obj=None

print("load config")

with open('cfg/board.json', 'r') as f:
    config_obj = json.load(f)

for  x  in config_obj:  
    print(x["ID"])
#print(config_obj)
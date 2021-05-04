// Code by marco cecchini

#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <Arduino.h>

File dataFile;
#define LOGFILE "datalog.txt"

class WebServer {
public:

  WebServer(){
    
  }

  void setup()
  {
     Serial.println("Opening logfile for write.");
    // Open up the file we're going to log to!
    dataFile = SD.open(LOGFILE, FILE_WRITE);
    if (! dataFile) {
      Serial.println("error opening log file");
      // Wait forever since we cant write data
      while (1) ;
    }
  
  }

  void loop()
  {
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
    {
      Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Received from :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        
        if(wifi.send(mux_id, buffer, len)) {
            Serial.print("send back ok\r\n");
        } else {
            Serial.print("send back err\r\n");
        }
        
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } else {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }
        
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
   }
 }
};

#endif

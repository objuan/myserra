// Code by marco cecchini

#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <Arduino.h>

File dataFile;
#define LOGFILE "datalog.txt"

class WebServer {
public:

  WiFi *connection;

  WebServer(WiFi *connection):connection(connection){
    
  }

  void setup()
  {
     Serial.println("Opening logfile for write.");
    // Open up the file we're going to log to!
   /* dataFile = SD.open(LOGFILE, FILE_WRITE);
    if (! dataFile) {
      Serial.println("error opening log file");
      // Wait forever since we cant write data
      while (1) ;
    }
  */
  }

  String GetCurrentTime()
  {
      DateTime now = RTC.now();
      
       char message[50];
      long epoch = now.unixtime();
      int Year = now.year();
      int Month = now.month();
      int Day = now.day();
      int Hour = now.hour();
      int Minute = now.minute();
      int Second = now.second();
      sprintf(message, "%ld,%d/%d/%d %02d:%02d:%02d",epoch,Year,Month,Day,Hour,Minute,Second );
      return message;
  }
  

  void loop()
  {
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        // extract path from request
        int state=0;
        int len = strlen(buffer);
        String path="";
        for(int i=0;i<len;i++)
        {
          if (buffer[i] == 'G' && state == 0) state++;
          else if (buffer[i] == 'E' && state == 1) state++;
          else if (buffer[i] == 'T' && state == 2) state++;
          else if (buffer[i] == ' ' && state == 3) state++;
          else if (state == 4)
          {
            if (buffer[i] == ' ')  state =5;
            else
              path+=(char)buffer[i];
          }
          
        }

// scarto
        if (!path.startsWith(F("/favicon.ico")))
        {
         
           // Serial.println("----------------------");
           // Serial.println(path);
  
            //buffer[0] = 0;
          //  ProcessRequest(path,mux_id, buffer, len);
/*
           connection->println(mux_id,"ssssssssssss\r\n\r\n");
           
           connection->println(mux_id,"aaaaaaaaaaaaaaaaaaaaaaa\r\n\r\n");

    connection->println(mux_id,"11\r\n\r\n");

    connection->println(mux_id,"22\r\n\r\n");

    connection->println(mux_id,"33\r\n\r\n");
    */
         //   strcpy(buffer,"HTTP/1.0\r\n\r\n");
          //  strcpy(buffer,"sdddddddddddddddddddddddddddd\r\n\r\n");
         //   len = strlen(buffer);
            
            //Serial.print("STATUS:");
           // Serial.print(i);
        //   // Serial.print(wifi.getIPStatus().c_str());
            Serial.println("----------------------");
            
            Serial.print("Received from :");
            Serial.print(mux_id);
            Serial.print("[");
            for(uint32_t i = 0; i < len; i++) {
                Serial.print((char)buffer[i]);
            }
            Serial.print("]\r\n");
            Serial.println("----------------------");

             ProcessRequest(path,mux_id, buffer, len);
             
         /*   if(wifi.send(mux_id, buffer, len)) {
                Serial.print("send back ok\r\n");
            } else {
                Serial.print("send back err\r\n");
            }
            */
    
            // --
    
        /*    strcpy(buffer,"bbbbbbbbbb\r\n\r\n");
            len = strlen(buffer);
            wifi.send(mux_id, buffer, len);
            */
                     
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
       // Serial.print("Status:[");
      //  Serial.print(wifi.getIPStatus().c_str());
      //  Serial.println("]");
        
     }
   }
    
   void ProcessRequest(String &path,uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size)
   {
     Serial.println("-1");
    connection->println(mux_id,"5555555555555555555sssssss\r\n\r\n");
    Serial.println("-1");
   // return;
    
    // tolgo il "/"
      path = path.substring(1);

      File dataFile = SD.open(path);
      if (! dataFile) {
        Serial.print("error opening file: ");
        Serial.println(path);
        return;
    }

       // HEADER

Serial.println("-2");
     connection->println(mux_id,"ssssssssssss\r\n\r\n");
Serial.println("-2");
     return;
     
    //connection->println(mux_id,"aaaaaaaaaaaaaaaaaaaaaaa\r\n\r\n");
      //connection->println(mux_id,"HTTP/1.0\r\n\r\n");

       //connection->println(mux_id,"HTTP/1.1 200 OK\r\n\r\n");
   /*    connection->println(mux_id,"Content-Type: text/html\r\n");
       
       connection->println(mux_id,"Content-Type: text/html\r\n");
       connection->println(mux_id,"Connection: close\r\n");  // the connection will be closed after completion of the response
       connection->println(mux_id,"Refresh: 5\r\n");  // refresh the page automatically every 5 sec
       connection->println(mux_id,"\r\n");
      */    
     // read from the file until there's nothing else in it:
    while (dataFile.available()) {
       // Serial.write(dataFile.read());
     //  connection->print(mux_id,dataFile.read());
    }
    
    // close the file:
    dataFile.close();
    
   }
};

#endif


#include "SoftwareSerial.h"

#define WIFI_DEBUG true
#define WIFI_FASTBOOT 

class WiFi
{
  SoftwareSerial& esp8266;
  
  String ip;
  
  public:

    WiFi (SoftwareSerial& serial) : esp8266(serial)
    {
    }

    String getLocalIP(){
      return ip;
    }
    
    String getIPStatus(void)
   {
      String list;
      delay(100);
      rx_empty();
      esp8266.println(F("AT+CIPSTATUS"));
      bool ok = recvFindAndFilter(F("OK"), F("\r\r\n"), F("\r\n\r\nOK"), list);
      return list;
   }

    void setup(String ssid,String password)
    {
       Serial.println("WIFI setup");
       
   #ifndef WIFI_FASTBOOT
      
        sendData(F("AT+RST\r\n"),2000,WIFI_DEBUG); // reset module
      
        sendData(F("AT+CWMODE=1\r\n"),2000,WIFI_DEBUG); // station. hosto mode
        //sendData("AT+CWMODE=3\r\n",2000,WIFI_DEBUG); // configure as access point and client
        //sendData("AT+CWMODE=2\r\n",2000,WIFI_DEBUG); // configure as access point
      
        //sendData("AT+CIPAP=\"192.168.0.200\"",2000,WIFI_DEBUG);
      
        // AP
        //sendData("AT+CWSAP=\"IGARDEN\",\"alicepi1\",2,3",2000,WIFI_DEBUG);
      //  sendData(F("AT+CWJAP=\"VIOFILIALI\",\"alicepi1\""),2000,WIFI_DEBUG);

        sATCWJAP(ssid,password);
        wait(10000,WIFI_DEBUG);
      // IP
        
      
        //DHCP
       // sendData("AT+CWDHCP=0,1",2000,WIFI_DEBUG);
        
        sendData(F("AT+CIFSR\r\n"),1000,WIFI_DEBUG); // get ip address
        //sendData("AT+CIPAP?\r\n",1000,WIFI_DEBUG); // get ip address
        
         #endif
  
        sendData(F("AT+CIPMUX=0\r\n"),1000,WIFI_DEBUG); // configure for multiple connections
        sendData(F("AT+CIPMUX=1\r\n"),1000,WIFI_DEBUG); // configure for multiple connections
        
        sendData(F("AT+CIPSERVER=0\r\n"),1000,WIFI_DEBUG); // turn on server on port 80
        sendData(F("AT+CIPSERVER=1,80\r\n"),1000,WIFI_DEBUG); // turn on server on port 80

         sendData(F("AT+CIPSTO=30\r\n"),1000,WIFI_DEBUG); //timeout
  }
  
   void println(uint8_t mux_id,const char *str)
   {
      //esp8266.println(str);
      send(mux_id,str,strlen(str));
   }
   
   void print(uint8_t mux_id,const char *str)
   {
      //esp8266.print(str);
      send(mux_id,str,strlen(str));
   }
    
   bool releaseTCP(void)
  {
    rx_empty();
    esp8266.println(F("AT+CIPCLOSE"));
    return recvFind(F("OK"), 5000);
  }

bool releaseTCP(uint8_t mux_id)
{
    String data;
    rx_empty();
    esp8266.print(F("AT+CIPCLOSE="));
    esp8266.println(mux_id);
    
    data = recvString(F("OK"), F("link is not"), 5000);
    if (data.indexOf(F("OK")) != -1 || data.indexOf(F("link is not")) != -1) {
        return true;
    }
    return false;
}


  String sendData(String command, const int timeout, boolean debug)
  {
      String response = "";
  
      if(debug)
      {
        Serial.print(command);
      }
      esp8266.print(command); // send the read character to the esp8266
      
      long int time = millis();
      
      while( (time+timeout) > millis())
      {
        while(esp8266.available())
        {
          
          // The esp has data so display its output to the serial window 
          char c = esp8266.read(); // read the next character.
          response+=c;
        }  
      }
      
      if(debug)
      {
        Serial.print(response);
      }
      
      return response;
  }

   String wait(const int timeout, boolean debug)
  {
      String response = "";
  
      long int time = millis();
      
      while( (time+timeout) > millis())
      {
        while(esp8266.available())
        {
          
          // The esp has data so display its output to the serial window 
          char c = esp8266.read(); // read the next character.
          response+=c;
        }  
      }
      
      if(debug)
      {
        Serial.print(response);
      }
      
      return response;
  }
  

    uint32_t recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
  {
      return recvPkg(buffer, buffer_size, NULL, timeout, NULL);
  }
  
  uint32_t recv(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
  {
      uint8_t id;
      uint32_t ret;
      ret = recvPkg(buffer, buffer_size, NULL, timeout, &id);
      if (ret > 0 && id == mux_id) {
          return ret;
      }
      return 0;
  }
  
  uint32_t recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
  {
      return recvPkg(buffer, buffer_size, NULL, timeout, coming_mux_id);
  }
  
bool sATCWJAP(String ssid, String pwd)
{
    String data;
    rx_empty();
    esp8266.print(F("AT+CWJAP=\""));
    esp8266.print(ssid);
    esp8266.print(F("\",\""));
    esp8266.print(pwd);
    esp8266.println(F("\""));

 
   
    return false;
}


  uint32_t recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id)
  {
    String data;
    char a;
    int32_t index_PIPDcomma = -1;
    int32_t index_colon = -1; /* : */
    int32_t index_comma = -1; /* , */
    int32_t len = -1;
    int8_t id = -1;
    bool has_data = false;
    uint32_t ret;
    unsigned long start;
    uint32_t i;
    
    if (buffer == NULL) {
        return 0;
    }
    
    start = millis();
    while (millis() - start < timeout) {
        if(esp8266.available() > 0) {
            a = esp8266.read();
            data += a;

         // Serial.print(a);
          //    Serial.print(".");
        }

        index_PIPDcomma = data.indexOf("+IPD,");
        if (index_PIPDcomma != -1) {
            index_colon = data.indexOf(':', index_PIPDcomma + 5);
            if (index_colon != -1) {
                index_comma = data.indexOf(',', index_PIPDcomma + 5);
                /* +IPD,id,len:data */
                if (index_comma != -1 && index_comma < index_colon) { 
                    id = data.substring(index_PIPDcomma + 5, index_comma).toInt();
                    if (id < 0 || id > 4) {
                        return 0;
                    }
                    len = data.substring(index_comma + 1, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                } else { /* +IPD,len:data */
                    len = data.substring(index_PIPDcomma + 5, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                }
                has_data = true;
                break;
            }
        }
    }
    
    if (has_data) {

     //  Serial.print("111111111111111");
       
        i = 0;
        ret = len > buffer_size ? buffer_size : len;
        start = millis();
        while (millis() - start < 3000) {
            while(esp8266.available() > 0 && i < ret) {
                a = esp8266.read();
                buffer[i++] = a;
            }
            if (i == ret) {
                rx_empty();
                if (data_len) {
                    *data_len = len;    
                }
                if (index_comma != -1 && coming_mux_id) {
                    *coming_mux_id = id;
                }
                return ret;
            }
        }
    }
    return 0;
  }
  
    void rx_empty(void) 
    {
        while(esp8266.available() > 0) {
            esp8266.read();
        }
    }

    bool recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout = 1000)
  {
      String data_tmp;
      data_tmp = recvString(target, timeout);
      if (data_tmp.indexOf(target) != -1) {
          int32_t index1 = data_tmp.indexOf(begin);
          int32_t index2 = data_tmp.indexOf(end);
          if (index1 != -1 && index2 != -1) {
              index1 += begin.length();
              data = data_tmp.substring(index1, index2);
              return true;
          }
      }
      data = "";
      return false;
  }
  String recvString(String target, uint32_t timeout)
  {
      String data;
      char a;
      unsigned long start = millis();
      while (millis() - start < timeout) {
          while(esp8266.available() > 0) {
              a = esp8266.read();
        if(a == '\0') continue;
              data += a;
          }
          if (data.indexOf(target) != -1) {
              break;
          }   
      }
      #ifdef WIFI_DEBUG
      Serial.print("> ");
      Serial.println(data);
      #endif
      return data;
  }
  
  String recvString(String target1, String target2, uint32_t timeout)
  {
      String data;
      char a;
      unsigned long start = millis();
      while (millis() - start < timeout) {
          while(esp8266.available() > 0) {
              a = esp8266.read();
        if(a == '\0') continue;
              data += a;
          }
          if (data.indexOf(target1) != -1) {
              break;
          } else if (data.indexOf(target2) != -1) {
              break;
          }
      }
      return data;
  }
  
  String recvString(String target1, String target2, String target3, uint32_t timeout)
  {
      String data;
      char a;
      unsigned long start = millis();
      while (millis() - start < timeout) {
          while(esp8266.available() > 0) {
              a = esp8266.read();
        if(a == '\0') continue;
              data += a;
          }
          if (data.indexOf(target1) != -1) {
              break;
          } else if (data.indexOf(target2) != -1) {
              break;
          } else if (data.indexOf(target3) != -1) {
              break;
          }
      }
      return data;
  }
  
  bool recvFind(String target, uint32_t timeout)
  {
      String data_tmp;
      data_tmp = recvString(target, timeout);
      if (data_tmp.indexOf(target) != -1) {
          return true;
      }
      return false;
  }
  bool send(const uint8_t *buffer, uint32_t len)
  {
      return sATCIPSENDSingle(buffer, len);
  }
  
  bool send(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
  {
      return sATCIPSENDMultiple(mux_id, buffer, len);
  }
  bool sATCIPSENDSingle(const uint8_t *buffer, uint32_t len)
  {
      rx_empty();
      esp8266.print(F("AT+CIPSEND="));
      esp8266.println(len);
      if (recvFind(">", 5000)) {
          rx_empty();
          for (uint32_t i = 0; i < len; i++) {
              esp8266.write(buffer[i]);
          }
          return recvFind(F("SEND OK"), 10000);
      }
      return false;
  }
  bool sATCIPSENDMultiple(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
  {
      rx_empty();
      esp8266.print(F("AT+CIPSEND="));
      esp8266.print(mux_id);
      esp8266.print(F(","));
      esp8266.println(len);
      if (recvFind(">", 5000)) {
          rx_empty();
          for (uint32_t i = 0; i < len; i++) {
              esp8266.write(buffer[i]);
          }
          return recvFind(F("SEND OK"), 10000);
      }
      return false;
  }
};


// I garden
//@vmfoo - 7/19/2014

#include <Arduino.h>

//
//#define DEBUG
#define SOFT_SERIAL


#include "SoftwareSerial.h"

#define WIFI_DEBUG true

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

    void setup()
    {
       Serial.println("WIFI setup");
       
      if (true)
      { 
        sendData("AT+RST\r\n",2000,WIFI_DEBUG); // reset module
      
        sendData("AT+CWMODE=1\r\n",2000,WIFI_DEBUG); // station. hosto mode
        //sendData("AT+CWMODE=3\r\n",2000,WIFI_DEBUG); // configure as access point and client
        //sendData("AT+CWMODE=2\r\n",2000,WIFI_DEBUG); // configure as access point
      
        //sendData("AT+CIPAP=\"192.168.0.200\"",2000,WIFI_DEBUG);
      
        // AP
        //sendData("AT+CWSAP=\"IGARDEN\",\"alicepi1\",2,3",2000,WIFI_DEBUG);
        sendData("AT+CWSAP=\"VIOFILIALI\",\"alicepi1\"",2000,WIFI_DEBUG);
      
      // IP
        
      
        //DHCP
       // sendData("AT+CWDHCP=0,1",2000,WIFI_DEBUG);
        
        sendData("AT+CIFSR\r\n",1000,WIFI_DEBUG); // get ip address
        //sendData("AT+CIPAP?\r\n",1000,WIFI_DEBUG); // get ip address
        
      }
      
        sendData("AT+CIPMUX=0\r\n",1000,WIFI_DEBUG); // configure for multiple connections
        sendData("AT+CIPMUX=1\r\n",1000,WIFI_DEBUG); // configure for multiple connections
        
        sendData("AT+CIPSERVER=0\r\n",1000,WIFI_DEBUG); // turn on server on port 80
        sendData("AT+CIPSERVER=1,80\r\n",1000,WIFI_DEBUG); // turn on server on port 80
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

              Serial.print(".");
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


// ---------- GENERAL -----------

//#define USE_HUMIDITY
//#define USE_RTC
//#define USE_SD
#define USE_WIFI
#define _DEBUG

#ifdef USE_SD && USE_WIFI
#define USE_WEB
#endif

// ---------- CONFIG -----------

// ---- SD -----

//DS, change this to match your SD shield or module;

#define sd_chipSelect  4 

// ---- RTC -----

//#define RTC_PIN 4

// ---- WI-FI -----

#ifdef USE_WIFI

//#include "ESP8266.h"

//#define SSID        "XGARDEN"
#define SSID        "VIOFILIALI"
#define PASSWORD    "alicepi1"
#define PORT  "8080"           // using port 8080 by default

SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
//ESP8266 wifi(mySerial);
WiFi wifi(mySerial);

#define dbg Serial
#define esp mySerial    

uint8_t buffer[256] = {0};
 
#endif

// ---- IGROMETRO -----

#define IGROMETRO_PORT1 A1
#define IGROMETRO_PORT2 A2

// ---- HUMIDITY -----

#define DHT11_PIN 4
#define HUMIDITY_WAIT_SECS  2

// ---------------------
 
//The RTC Library needs Wire
#ifdef USE_RTC
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
#endif

#ifdef USE_SD
//The SDlibrary needs SPI
#include <SPI.h>
#include "SD.h"
//Some SD Card code borrowed from Adafruit library examples
// set up variables using the SD utility library functions:

#endif

#ifdef USE_HUMIDITY
//library to read the temp/humid sensor
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
#include "dht11.h"
dht11 DHT;
#endif

#ifdef USE_WEB
#include "webserver.h"
WebServer webServer;
#endif


// =================================================


struct TimeWait
{
  long waitTimeS;
  long lastTime;

  TimeWait(long _waitTimeS){
    waitTimeS=_waitTimeS;
    lastTime = 0;
 //   lastTime= mills();
  }

  #ifdef USE_RTC
  bool IsActive( DateTime now){
    if ( (now.secondstime() - lastTime) > waitTimeS)
    {
      lastTime= now.secondstime();
      return true;
    }
    else
      return false;
  }
  #endif
};

// =================================================

TimeWait humidityWait(HUMIDITY_WAIT_SECS);

// =================================================

// ===============================================
// SETUP
// ===============================================



void setup() {
   Serial.begin(9600); 

  
   Serial.println(F("Initializing igarder"));

#ifdef USE_WIFI
   esp.begin(9600);

  wifi.setup();
  
#ifdef A
    Serial.print(F("FW Version:"));
  //  Serial.println(wifi.getVersion().c_str());
      
  //  if (wifi.setOprToStationSoftAP()) {
    if (wifi.setOprToStation()){
   // if (wifi.setOprToSoftAP()){
        Serial.print(F("to station  ok\r\n"));
    } else {
        Serial.print(F("to station  err\r\n"));
    }

 /*  if (wifi.setIP("192.168.0.200")){
        Serial.print(F("setIP  ok\r\n"));
    } else {
        Serial.print(F("setIP  err\r\n"));
    }
   */ 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print(F("Join AP success\r\n"));
        Serial.print(F("IP: "));
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
         Serial.print(F("IP: "));
        Serial.println(wifi.getLocalIP().c_str());    
        Serial.print(F("Join AP failure\r\n"));
    }
    
 /*   if (wifi.enableClientDHCP(0,true)) {
        Serial.print(F("enableClientDHCPiple ok\r\n"));
    } else {
        Serial.print(F("enableClientDHCP err\r\n"));
    }
    */
    #endif

    Serial.println(wifi.getLocalIP().c_str());   
    
  /*  if (wifi.enableMUX()) {
        Serial.print(F("multiple ok\r\n"));
    } else {
        Serial.print(F("multiple err\r\n"));
    }

  //  wifi.stopTCPServer();

    // /attenzione a volte si inceppa il server , bisogna azzerarlo
    if (wifi.stopTCPServer()) {
        Serial.print(F("stop tcp server ok\r\n"));
    } else {
        Serial.print(F("stop tcp server err\r\n"));
    }
    
    if (wifi.startTCPServer(PORT)) {
        Serial.print(F("start tcp server ok\r\n"));
    } else {
        Serial.print(F("start tcp server err\r\n"));
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print(F("set tcp server timout 10 seconds\r\n"));
    } else {
        Serial.print(F("set tcp server timout err\r\n"));
    }
    */
    
 #endif

 #ifdef USE_HUMIDITY
  //Initialize the Sensor
  
  Serial.println(F("Starting Temp and Humidity Sensor"));

  Serial.print(F("LIBRARY VERSION: "));
  Serial.println(DHT11LIB_VERSION);


 // dht.begin();
#endif

#ifdef  USE_SD
  Serial.println(F("SDCard.."));

  pinMode(sd_chipSelect, OUTPUT);
  digitalWrite(sd_chipSelect, HIGH);
   
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(sd_chipSelect)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK"));

 
 #endif 

#ifdef USE_RTC
  Serial.println(F("Starting Real Time Clock"));
  Wire.begin();
  RTC.begin();
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  //uncomment this once and upload. Then comment it out and upload again
  //This will set the time the first time you upload it and if you don't upload again with it commented out it will 
  //reset the clock to the time the code was compliled each time.
  
  if (! RTC.isrunning()) {
    Serial.println(F("RTC is NOT running!"));
    // following line sets the RTC to the date &amp; time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  DateTime now = RTC.now();
  Serial.print(F("Unixtime: "));
  Serial.println(now.unixtime());
  
 #endif 

#ifdef USE_WEB
  webServer.setup();
#endif
  
  Serial.println(F("setup end"));

}

// ===============================================
// LOOP
// ===============================================

void loop()
{
#ifdef USE_RTC
  DateTime now = RTC.now();

    //now.time_t;
    /*Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */
#endif
  
  /*char temp[6]; //2 int, 2 dec, 1 point, and \0
  char hum[6];  
  char msg[13];
  
  //get the temp/humid into chars to format
  ftoa(temp,readTemp());
  ftoa(hum,readHumidity());
  
  //Compile a comma delimited string to send to the log
  sprintf(msg,"%s,%s",temp, hum);
  logThis(msg);  
  delay(3000); 
  */

/*
  dbg.print("Time: ");
  unsigned long time = millis();
  //prints time since program started
  dbg.println(time);
  // wait a second so as not to send massive amounts of data
  delay(1000);
  
   return;
   */

#ifdef USE_WEB
  //webServer.loop();
#endif

#ifdef USE_WIFI
   
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
        
        // read serial until packet_len character received
        // start from :
     /*   pb = buffer+5;
        while(*pb!=':') pb++;
        pb++;
        if (strncmp(pb, "GET /", 5) == 0) {
          wait_for_esp_response(1000);
          #ifdef _DEBUG
            dbg.println("-> serve homepage");
          #endif
          serve_homepage(ch_id);
        }
        
      }*/
    }
  }
#endif
// -------------
#ifdef USE_HUMIDITY
  if (humidityWait.IsActive(now))
  {
    readTempHumidity();
  
    Serial.print(DHT.humidity,1);
    Serial.print(",\t");
    Serial.println(DHT.temperature,1);

  }
 #endif
 
 //delay(1000);

}


void logThis(char* logmessage){
 /* char message[120];
  DateTime now = rtc.now();
  long epoch = now.unixtime();
  int Year = now.year();
  int Month = now.month();
  int Day = now.day();
  int Hour = now.hour();
  int Minute = now.minute();
  int Second = now.second();
  sprintf(message, "%ld,%d/%d/%d %02d:%02d:%02d,%s",epoch,Year,Month,Day,Hour,Minute,Second,logmessage );
  //Write the entry to the log file and console
  dataFile.println(message);
  dataFile.flush();
  // print to the serial port too:
  Serial.println(message);
  */
}


#ifdef USE_HUMIDITY
void readTempHumidity(){
 /// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//#ifdef _DEBUG
    //long time1 = mills();
//#endif
  
   int chk;
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print(F("OK,\t")); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print(F("Checksum error,\t)")); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print(F("Time out error,\t")); 
                break;
    default: 
                Serial.print(F("Unknown error,\t")); 
                break;
  } 

//#ifdef _DEBUG
    //long time2 = mills();
    //Serial.print("Call Time:\t"); 
    //Serial.println(time2-time1); 
//#endif
}
#endif

/*
int ftoa(char *a, float f)  //translates floating point readings into strings
{
  int left=int(f);
  float decimal = f-left;
  int right = decimal *100; //2 decimal points
  if (right > 10) {  //if the decimal has two places already. Otherwise
    sprintf(a, "%d.%d",left,right);
  } else { 
    sprintf(a, "%d.0%d",left,right); //pad with a leading 0
  }
}
*/


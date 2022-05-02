// I garden
//@vmfoo - 7/19/2014

#include <Arduino.h>

//
//#define DEBUG

#include "MyWiFI.h"
// ---------- GENERAL -----------

//#define USE_HUMIDITY
//#define USE_RTC
//#define USE_SD
//#define USE_WIFI
#define _DEBUG

#if (USE_SD) && (USE_WIFI)
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

uint8_t buffer[128] = {0};
 
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
WebServer webServer(&wifi);
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

#include "controller.h"

Controller controller;

void setup() {
   Serial.begin(9600); 
  
   Serial.println(F("Initializing igarder"));

#ifdef USE_WIFI
   esp.begin(9600);

  wifi.setup(SSID,PASSWORD);
  
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

  controller.setup();
  
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
  webServer.loop();
#endif

// -------------
#ifdef USE_HUMIDITY
  if (humidityWait.IsActive(now))
  {
    readTempHumidity();
/*  
    Serial.print(DHT.humidity,1);
    Serial.print(",\t");
    Serial.println(DHT.temperature,1);
*/
  }
 #endif
 
 //delay(1000);

  controller.loop();
 
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

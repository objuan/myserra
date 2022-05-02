/*
 * Created by marco cecchini
 *
 */

#define BLYNK_PRINT Serial

#include <ESP8266WebServer.h>
#define HTTP_REST_PORT 80
ESP8266WebServer server(HTTP_REST_PORT);


#define BLYNK_TEMPLATE_ID "TMPLPgelnWJW"
#define BLYNK_DEVICE_NAME "semensario"
#define BLYNK_AUTH_TOKEN "cTBbhJBp4kWOQSTiWS6cVkh0XeVXsLvz"
//#define BLYNK_AUTH_TOKEN "9Agk4hRr9jJHJKOeM80lcWimvgLoO6T1"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//#include <WidgetRTC.h>

//#include <SoftwareSerial.h>
//SoftwareSerial DebugSerial(2, 3); // RX, TX

//#include <BlynkSimpleEsp8266.h>
#include "config.h"
#include "timer.h";
#include "eprom.h"
//#include "vhandlers.h"
//#include "osmotica.h"
#include "giardino.h"
#include "irrigazione.h"
//#include "lab.h"


//The RTC Library needs Wire
#ifdef USE_RTC
//#include <Wire.h>
//#include "RTClib.h"
RTC_DS1307 rtc;
#endif

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "VIOLAFILIPPO";
//char pass[] = "alicepi1";

char ssid[] = "CASAMIA";
char pass[] = "Alicepi1";

//char ssid[] = "GIARDINO";
//char pass[] = "alicepi1";

BlynkTimer timer;
//WidgetRTC rtc;

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  //Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  //Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

BLYNK_WRITE(V20) //Button luci
{
  
}

DateTime now;

String str_DateTime()
{
    //DateTime now = rtc.now();
    char buf1[100];
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
    return String(buf1);
}
String str_DateTime(const DateTime& now)
{
    //DateTime now = rtc.now();
    char buf1[100];
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
    return String(buf1);
}


void clockDisplay()
{
  Blynk.virtualWrite(V1, str_DateTime(now));
}

void mydigitalWrite(int pin, int value)
{
  #ifdef SYM_MODE
  Serial.print("==> digitalWrite pin=");
  Serial.print(pin);
  Serial.print("=");
  Serial.println(value);
  #else
  digitalWrite(pin,value);
  #endif
}


void printDateTime(const DateTime& now)
{
  Log(str_DateTime(now).c_str());
  /*
    //DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
 //   Serial.print(" (");
  //  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    */
}

void printDateTimeln(const DateTime& now)
{
    printDateTime(now);
    Serial.println();
}



// ========== REST ===========

void getHelloWord() {
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}
 
void getState() {
   
    server.send(200, "text/json", "..");
}
 
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
            F("Welcome to the Giardino REST Web Server"));
    });
    server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
    server.on(F("/state"), HTTP_GET, getState);
}


/*
 *  CONNECT DIAGRAM
 *  
 *  TOP   1 -> water up 
 *  
 *  
 *  FILL  1 -> water down 
 *  
 *  
 *  DANGER 1 -> water down 
 * 
 * 
 */

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);

 Blynk.begin(auth, ssid, pass);
  
  //osmotica_setup();
  giardino_setup();
  irrigazione_setup();
 // lab_setup();
 
 // virtualWrite(0,"INIT");
//  com.Register(CMD_PING, OnPing);


#ifdef USE_RTC
  Serial.println(F("Starting Real Time Clock"));
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  // if (! rtc.isrunning()) {
  if (false) // lanciare per aggiustare l'ora
  {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
   printDateTime(rtc.now());
 #endif 
 

  // Setup a function to be called every second
 // timer.setInterval(1000L, clockDisplay);

  restServerRouting();
  server.begin();
  Log("HTTP server started");
}


int i_time=0;
// the loop function runs over and over again forever
void loop() 
{
  Blynk.run();
  
  now = rtc.now();

  server.handleClient();
   
   // SERIAL 
  printDateTimeln(now);

  Blynk.virtualWrite(V1,str_DateTime(now).c_str());


//  Com_Tick();
 
 // osmotica_loop();
  giardino_loop(now);
  irrigazione_loop(now);
  //lab_loop();
 
 //virtualWrite(10,"pippo");

// virtualRead(11,"pippo");

 // Debug("tick",i_time);
  i_time++;
 //virtualWrite(2,33);

   delay(1000);

}

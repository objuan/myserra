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

#include "config.h"
#include "common.h"
#include "timer.h"

#include "orto.h"


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "VIOLAFILIPPO";
//char pass[] = "alicepi1";

char ssid[] = "CASAMIA";
char pass[] = "Alicepi1";

BlynkTimer timer;

BLYNK_CONNECTED()
{
    Blynk.syncAll();
    Blynk.sendInternal("rtc", "sync"); //request current local time for device
}

String str_DateTime(const DateTime &now)
{
    //DateTime now = rtc.now();
    char buf1[100];
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
    return String(buf1);
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

// ================================

void clockDisplay()
{
  Blynk.sendInternal("rtc", "sync"); 
}

// ===============================================

//char mem_send[BLYNK_MAX_SENDBYTES];

void setup() {
  //Serial.begin(9600);
  Serial.begin(38400);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(60000L, clockDisplay); // uno al minuto
  restServerRouting();
  server.begin();
  Log("HTTP server started");
  
}

unsigned long clock_time=0;
int i_time=0;
unsigned long last_time=0;
unsigned long last_time1=0;
unsigned long web_time=0;
unsigned long cpu_time=0;

BLYNK_WRITE(InternalPinRTC) {   //check the value of InternalPinRTC  
  long t = param.asLong();      //store time in t variable
  web_time = t;
  Serial.print("Unix time: ");  
  Serial.print(t);              //prints time in UNIX format to Serial Monitor
  Serial.println();
}

// the loop function runs over and over again forever
void loop() 
{
  timer.run();
  Blynk.run();
  
  server.handleClient();
  
  clock_time=millis();

  if (clock_time - last_time> 1000)
  {
    last_time = clock_time;

   // manager.tick();

    i_time++;

    web_time+= (clock_time-cpu_time) / 1000;
    cpu_time = clock_time;

    DateTime now = DateTime(web_time);

    Blynk.virtualWrite(VPIN_CLOCK_DISPLAY,str_DateTime(now).c_str());
    Blynk.virtualWrite(VPIN_CLOCK_ETA,i_time);

     
     orto_loop(now);

  }
//   delay(1000);

}


 void Switch::tick(const DateTime &now)
    {
      // Serial.println(str_DateTime(now).c_str());

       if (mode == SwitchMode::OFF)
          value=0;
       else 
          value =  ( mode == SwitchMode::OPEN || timer->isOn(now) )?  1 : 0;

       if (value != lastValue || oldMode != mode)
       { 
            Blynk.virtualWrite(vpin, (value==1) ?  F("ON"):F("OFF")," ( ", sw_names[mode], ")",timer->toString().c_str());
     
            lastValue=value;
            oldMode=mode;
            digitalWrite(pin, (value==1)  ? RELE_ON : RELE_OFF);

           // VirtualLog("[",str_DateTime(now).c_str(),"] ", timer->name,":",  (value==1)  ?F("OK"):F("OFF")," ( ", sw_names[mode], ")" );
       }
    }

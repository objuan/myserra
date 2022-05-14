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

#include <MemoryFree.h>
#include "virtual_elements_manager.h"

//#include <WidgetRTC.h>
//#include <SoftwareSerial.h>
//SoftwareSerial DebugSerial(2, 3); // RX, TX

#include "config.h"


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "VIOLAFILIPPO";
//char pass[] = "alicepi1";

char ssid[] = "CASAMIA";
char pass[] = "Alicepi1";

BlynkTimer timer;
//WidgetRTC rtc;

BLYNK_CONNECTED()
{
   Blynk.sendInternal("rtc", "sync"); //request current local time for device
  // Change Web Link Button message to "Congratulations!"
  //Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  //Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
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

BLYNK_WRITE(V100) {  _cloudWrite(V100,param[0].asInt()); }
BLYNK_WRITE(V101) {  _cloudWrite(V101,param[0].asInt()); }
BLYNK_WRITE(V102) {  _cloudWrite(V102,param[0].asInt()); }
BLYNK_WRITE(V103) {  _cloudWrite(V103,param[0].asInt()); }
BLYNK_WRITE(V104) {  _cloudWrite(V104,param[0].asInt()); }
BLYNK_WRITE(V105) {  _cloudWrite(V105,param[0].asInt()); }
BLYNK_WRITE(V106) {  _cloudWrite(V106,param[0].asInt()); }
BLYNK_WRITE(V107) {  _cloudWrite(V107,param[0].asInt()); }
BLYNK_WRITE(V108) {  _cloudWrite(V108,param[0].asInt()); }
BLYNK_WRITE(V109) {  _cloudWrite(V109,param[0].asInt()); }
BLYNK_WRITE(V110) {  _cloudWrite(V110,param[0].asInt()); }

BLYNK_WRITE(InternalPinRTC) {   //check the value of InternalPinRTC  
  long t = param.asLong();      //store time in t variable
  //Serial.print("Unix time: ");  
  //Serial.print(t);              //prints time in UNIX format to Serial Monitor
  //Serial.println();
  _cloudWrite(127,t);
}

void clockDisplay()
{
  Blynk.sendInternal("rtc", "sync"); 
}

// ===============================================

VirtualElementManager manager("MA", &Serial,true);
//VirtualElementManager *manager_lab;
char mem_send[BLYNK_MAX_SENDBYTES];

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


// the loop function runs over and over again forever
void loop() 
{
  timer.run();
  Blynk.run();
  
  server.handleClient();
  
  //i_time++;

  clock_time=millis();

  if (clock_time - last_time> 1000)
  {
    last_time = clock_time;

    manager.tick();

    i_time++;

    Blynk.virtualWrite(126,i_time);
   // _cloudWrite(126,i_time);
  }
  else
  {
    manager.fast_tick();

  }
//   delay(1000);

}

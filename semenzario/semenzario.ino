/* Comment this out to disable prints and save space */


#define TEMPERATURE_TARGET 23
#define ORA_START 8
#define ORA_FINE 20

// ================



#define BLYNK_PRINT Serial

  
#include <ESP8266WebServer.h>
#define HTTP_REST_PORT 80
ESP8266WebServer server(HTTP_REST_PORT);

//#define BLYNK_TEMPLATE_ID "TMPLPgelnWJW"
//#define BLYNK_DEVICE_NAME "semensario"
//#define BLYNK_AUTH_TOKEN "cTBbhJBp4kWOQSTiWS6cVkh0XeVXsLvz"
#define BLYNK_AUTH_TOKEN "9Agk4hRr9jJHJKOeM80lcWimvgLoO6T1"

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>


LiquidCrystal_I2C lcd(0x27, 16, 4);

#define DHT11_PIN D11
#define RELE_TMP_PIN D12
#define RELE_LUCI_PIN D13

#include "dht11.h"

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FilippoViola";
char pass[] = "alicepi1";

//char ssid[] = "GIARDINO";
//char pass[] = "alicepi1";

BlynkTimer timer;
WidgetRTC rtc;

String currentTime;
String currentDate;
bool luce_accesa = false;
dht11 DHT;

bool temp_attiva=false;
bool en_luci=true;
bool en_resistenza=true;
/*
// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

*/
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  //Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  //Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

BLYNK_WRITE(V20) //Button luci
{
  en_luci =  param.asInt()==1;
}
BLYNK_WRITE(V21) //Button resistenza
{
   en_resistenza =  param.asInt()==1; 
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
 
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  currentDate = String(day()) + " " + month() + " " + year();
  
 
  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V2, currentDate);
}

float _temperature;
float _humidity;
float mois;
void temperature()
{
  // return;
  
    mois = analogRead(A0);

   int chk;
  //Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }

  _humidity =  DHT.humidity;
  _temperature =  DHT.temperature;
  
  Blynk.virtualWrite(V3, DHT.humidity);
  Blynk.virtualWrite(V4, DHT.temperature);
  Blynk.virtualWrite(V5, mois);

  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.print(DHT.temperature,1);
  Serial.print(",\t");
  Serial.println(mois,1);

  lcd.setCursor(0,0);
  lcd.print("Temperatura "); 
  lcd.setCursor(13,0);
  lcd.print(DHT.temperature); 
  //lcd.setCursor(17,0);
  //lcd.print("??");
   
  lcd.setCursor(0,1); //Defining positon to write from second row,first column .
  lcd.print("Umidita Aria"); 
  lcd.setCursor(13,1);
  lcd.print(DHT.humidity); 
  lcd.setCursor(17,1);
  lcd.print("%");

  lcd.setCursor(0,2); //Defining positon to write from second row,first column .
  lcd.print("Umidita Suolo "); 
  lcd.setCursor(13,2);
  lcd.print(mois); 

}
int c=0;
void switch_temperatura(bool accesa)
{  Serial.print("tmp");
   Serial.println(accesa);
   digitalWrite(RELE_TMP_PIN, (accesa) ? LOW : HIGH);
   temp_attiva = accesa;
   int v = (temp_attiva) ? 1 : 0;
   Blynk.virtualWrite(V7, accesa);
   
}
void switch_luci(bool accesa)
{ 
    Serial.print("LUCI");
  Serial.println(accesa);
 
   digitalWrite(RELE_LUCI_PIN, (accesa) ? LOW : HIGH);
   luce_accesa = accesa;
   int v = (luce_accesa) ? 1 : 0;
   Blynk.virtualWrite(V8, luce_accesa);
   
}

void test_temp() {

  if (temp_attiva == true){
    switch_temperatura(true);
   }
  else{
   switch_temperatura(false);
  }
 
  temp_attiva = !temp_attiva;

   Serial.println(temp_attiva);
  delay(2000);              // attende per un secondo.
}

// ================

void setup()
{
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

   // Begin synchronizing time
  rtc.begin();
  
  //dht.begin();
   
  lcd.begin(); //Defining 16 columns and 2 rows of lcd display

  //lcd.backlight(); //To Power ON /OFF the back light
  lcd.noBacklight(); //To Power ON /OFF the back light

 // Setup a function to be called every second
  timer.setInterval(1000L, clockDisplay);
  timer.setInterval(1000L, temperature);

  pinMode(A0, INPUT);
  
  pinMode(RELE_TMP_PIN, OUTPUT);
  pinMode(RELE_LUCI_PIN, OUTPUT);
  

  switch_luci(false);
  switch_temperatura(false);
  
  restServerRouting();
  server.begin();
  Serial.println("HTTP server started");
}

void calibraTemperatura()
{
  if (_temperature < TEMPERATURE_TARGET && en_resistenza)
  {
    // troppo bassa 
    switch_temperatura(true);
  }
  else if ( _temperature- TEMPERATURE_TARGET  >0.5)
  {
    switch_temperatura(false);
  }
  
}



void periodo_luci()
{
  int h = hour();

   Blynk.virtualWrite(V9, h);
 // Serial.print("ORA: ");
  //Serial.println(h);
  
  bool accesa = (h >= ORA_START && h <= ORA_FINE)  && en_luci ;
  if (accesa != luce_accesa)
  {
      luce_accesa = accesa;

      switch_luci(luce_accesa);
  }
  
   
}

// ========== REST ===========

void getHelloWord() {
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}
 
void getState() {
    String temperature = String(_temperature, 1);
    String humidity = String(_humidity, 1);
    String smois = String(mois);
    String res =  String("{\"temp\":")+  temperature+",\"humidity\":"+humidity+",\"mois\":"+smois+",\"sw_tmp\":"+((temp_attiva)? "1": "0")+",\"sw_luci\":"+((luce_accesa)? "1": "0")+"}";
    //DHT.humidity
    //DHT.temperature
    server.send(200, "text/json", res);
}
 
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
            F("Welcome to the Semenzario REST Web Server"));
    });
    server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
    server.on(F("/state"), HTTP_GET, getState);
}

// ========= LOOP =======

void loop()
{
  Blynk.run();

  timer.run();

 server.handleClient();

   calibraTemperatura();

   periodo_luci();

//  switch_luci(false);
//  switch_temperatura(true);
  
   delay(1000);
 //test_temp();
 //switch_temperatura(true);
 
}

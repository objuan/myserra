// Now using ESP8266.....
// Sample Arduino Json Web Server
// Created by Benoit Blanchon.
// Heavily inspired by "Web Server" from David A. Mellis and Tom Igoe


#include "ArduinoJson.h"
#include "ESP8266WiFi.h"

#include <SoftwareSerial.h>

#define sw_serial_rx_pin 2 //  Connect this pin to TX on the esp8266
#define sw_serial_tx_pin 3 //  Connect this pin to RX on the esp8266
#define esp8266_reset_pin 4 // Connect this pin to CH_PD on the esp8266, not reset. (let reset be unconnected)

SoftwareSerial swSerial(sw_serial_rx_pin, sw_serial_tx_pin);

// the last parameter sets the local echo option for the ESP8266 module..
ESP8266wifi wifi(swSerial, swSerial, esp8266_reset_pin, Serial);//adding Serial enabled local echo and wifi debug

// needed to avoid link error on ram check
/*extern "C"
{
//#include "user_interface.h"
}
*/
//ADC_MODE(ADC_VCC);

//WiFiServer server(80);
//WiFiClient client;

const char* ssid = "VIOFILIALI";
const char* password = "alicepi1";

/*
float pfDew,pfHum,pfTemp,pfVcc;
bool readRequest(WiFiClient& client) {
  bool currentLineIsBlank = true;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (c == '\n' && currentLineIsBlank) {
        return true;
      } else if (c == '\n') {
        currentLineIsBlank = true;
      } else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  return false;
}
*/
JsonObject& prepareResponse(JsonBuffer& jsonBuffer) {
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& tempValues = root.createNestedArray("temperature");
    tempValues.add(1);
  JsonArray& humiValues = root.createNestedArray("humidity");
    humiValues.add(2);
  JsonArray& dewpValues = root.createNestedArray("dewpoint");
    dewpValues.add(3);
  JsonArray& EsPvValues = root.createNestedArray("Systemv");
    EsPvValues.add(4, 3);   
  return root;
}

/*
void writeResponse(WiFiClient& client, JsonObject& json) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  json.prettyPrintTo(client);
}
*/




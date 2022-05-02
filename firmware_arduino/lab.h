/*
 * Created by marco cecchini
 *
 */

#include <BlynkSimpleStream.h>
#include "config.h"
#include "vhandlers.h"
#include <ArduinoJson.h>

// constants 

//#define LAB_PUMP_1_PIN  13  // interruttore acqua piena
//#define LAB_PUMP_2_PIN  14  // interruttore acqua piena

void lab_setup() {
  
  Serial.println("Lab Started");
}

 /*   
CLOUD_ON_WRITE(LAB_PUMP_1){
  Debug("LAB_PUMP_1", param.asInt());

 // DynamicJsonDocument doc(1024);
 StaticJsonDocument<400> doc;
  DeserializationError error = deserializeJson(doc, param.asString());

  // Test if parsing succeeds.
  if (error) {
    Error("deserializeJson() failed: ");
    Error(error.f_str());
    return;
  }
  
  const char* b = doc["b"];
  int a = doc["a"];
  Debug("a",a);
 Debug("b",b);

}
*/
  
// the loop function runs over and over again forever
void lab_loop() 
{


}

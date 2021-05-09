/*
 * Created by marco cecchini
 *
 */

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>
#include "config.h"
#include "vhandlers.h"
#include "osmotica.h"
#include "lab.h"


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

unsigned long clock_time=0;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  osmotica_setup();
  lab_setup();
 
  virtualWrite(0,"INIT");
//  com.Register(CMD_PING, OnPing);

  clock_time=millis();

}

int i_time=0;
// the loop function runs over and over again forever
void loop() 
{
   // SERIAL 

  Com_Tick();
 
  osmotica_loop();
  //lab_loop();
 
 //virtualWrite(10,"pippo");

// virtualRead(11,"pippo");
  clock_time=millis();
  COMMAND("TIME ",clock_time);
  
  i_time++;
 //virtualWrite(2,33);

   delay(1000);

}

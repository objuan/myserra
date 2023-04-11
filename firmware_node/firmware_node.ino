/*
 * Created by marco cecchini
 *
 */

#include <SoftwareSerial.h>
// occhio sulla mesa 2,3 non va
SoftwareSerial DebugSerial(10,11); // RX, TX
Stream *manager_serial = &DebugSerial;

#include <BlynkSimpleStream.h>

#include "config.h"
#include "eprom.h"

#include "node.h"

//#include <MemoryFree.h>

//Node node("test1",&DebugSerial,NODE_MATER);
Node node("MAIN",&Serial,&DebugSerial,NODE_MATER);

/*
String str_DateTime(const DateTime &now)
{
    //DateTime now = rtc.now();
    char buf1[100];
    sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
    return String(buf1);
}

void printDateTime(DateTime now)
{
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
}

void printDateTimeln(DateTime now)
{
    printDateTime(now);
    Serial.println();
}
*/

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
  Serial.begin(9600);
  DebugSerial.begin(9600);
  
  Serial.println("CMD STARTUP");
}


unsigned long clock_time=0;
int i_time=0;
unsigned long last_time=0;
unsigned long last_time1=0;
unsigned long web_time=0;
unsigned long cpu_time=0;


// the loop function runs over and over again forever
void loop() 
{
  /*
   while (Serial.available() > 0 ) 
   {
     // String s = Serial.readString();
    //  Serial.print(">");
    //  Serial.print(s);

    
   }
   */
    
    
  clock_time=millis();
  
  if (clock_time - last_time> 1000)
  {
    
    last_time = clock_time;
    node.tick();
  
    i_time++;
   // node.sendACK(i_time);
  }
  else
  {
    node.tick();

  }



  // delay(1000);

}

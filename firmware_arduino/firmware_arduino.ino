/*
 * Created by marco cecchini
 *
 */

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>
//#include <BlynkSimpleEsp8266.h>
#include "config.h"
#include "timer.h";
#include "eprom.h"
#include "vhandlers.h"
//#include "osmotica.h"
#include "giardino.h"
#include "irrigazione.h"
//#include "lab.h"

#include <MemoryFree.h>
#include "virtual_elements_manager.h"

//The RTC Library needs Wire
#ifdef USE_RTC
//#include <Wire.h>
//#include "RTClib.h"
RTC_DS1307 rtc;
#endif

VirtualElementManager manager("esp",&Serial,true);
//VirtualElementManager *manager_lab;
char mem_send[BLYNK_MAX_SENDBYTES];


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
  Serial.begin(57600);

  
//  osmotica_setup();
  giardino_setup();
  irrigazione_setup();
 // lab_setup();
 
  virtualWrite(0,"INIT");
//  com.Register(CMD_PING, OnPing);

#ifdef USE_RTC
  Serial.println(F("Starting Real Time Clock"));
  VirtualLog(F("Starting Real Time Clock"));
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    VirtualLog(F("Couldn't find RTC"));
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
 
}


unsigned long clock_time=0;
int i_time=0;
unsigned long last_time=0;
unsigned long last_time1=0;


// the loop function runs over and over again forever
void loop() 
{
 // return;
  
 // Serial.println("vw 1 pippo");

  //cloudWrite(1,i_time);
  i_time++;

  clock_time=millis();
  if (clock_time - last_time> 1000)
  {
    last_time = clock_time;
   // cloudWrite(1,i_time);
    manager.tick();

    i_time++;

    // 

    #ifdef USE_RTC
      DateTime now = rtc.now();
   #else
     DateTime now = DateTime();
    #endif
    
      virtualWrite(V1,str_DateTime(now).c_str());
      
       // SERIAL 
      //printDateTimeln(now);
   
//      osmotica_loop();
      giardino_loop(now);
      irrigazione_loop(now);

      //lab_loop();
    
     // Debug("tick",i_time);
      i_time++;
       



    //
  }
  else
  {
    manager.fast_tick();

  }


  // delay(1000);

}

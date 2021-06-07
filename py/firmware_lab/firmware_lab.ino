#include "config.h"
#include "common.h"

#define DEBUG_MODE

#include <OneWire.h>
//#include <DallasTemperature.h>
#include <MemoryFree.h>

#include <SoftwareSerial.h>
SoftwareSerial LabSerial(LAB_SERIAL_RX,LAB_SERIAL_TX); // RX, TX

#include "virtual_elements_manager.h"
#include "lab.h"
#include "pumps.h"
VirtualElementManager *manager;

char mem_send[BLYNK_MAX_SENDBYTES];
char in_buffer[MAX_RECEIVE_BUFFER]; 

Lab *lab=NULL;
Pumps *pumps=NULL;

int i_time=0;
unsigned long last_time=0;
unsigned long clock_time=0;
unsigned long last_time1=0;
#define LAB_SYNC_VPIN 1

class Var_LabSync: public Var_String
{
  public:

     Var_LabSync() : Var_String(LAB_SYNC_VPIN){}

     void OnCloudWrite(BlynkParam &param){
        value = param.asString();
        Debug(F("ON LAB SYNC "), pin , " ",value);

    }
};

void setup(void)
{ 
  // Start serial communication for debugging purposes
  Serial.begin(115200);

  LabSerial.begin(57600);

  manager = new VirtualElementManager ("LAB",&LabSerial,false);
  
  // Wire.begin();

     lab = new Lab(*manager);
     pumps = new Pumps(*manager);

    manager->Add(new Var_LabSync());
  
    COMMAND(F("STARTUP"));
}

void loop(void)
{
   clock_time=millis();
  
  if (clock_time - last_time1> 10000)
  {
      last_time1 = clock_time;

     COMMAND(F("MEMORY "),freeMemory());
     cloudWrite(LabSerial,LAB_SYNC_VPIN,clock_time);
  
  }
  
  if (clock_time - last_time> 1000)
  {
     manager->tick();
     last_time = clock_time;

    if (lab!=NULL)
     lab->Logic();
     pumps->Logic();

     i_time++;
  }
  else
  { 
     manager->fast_tick();
  
     if (lab!=NULL)
      lab->LogicFast();
  }
}

/*
// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library<A
  sensors.begin();

  LabSerial.begin(9600);
}


void loop(void){ 

  while (LabSerial.available() > 0) {

    char inByte = LabSerial.read();

    Serial.write(inByte);

  }
  
   Debug("test");
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(1000);
}
*/

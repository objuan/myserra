/*
 * Created by marco cecchini
 *
 */

// -----------

#define MEGA
//#define CENTRALINA
//#define TIME

// -----------
#define LAB
#define TIME

#ifdef LAB
#include <SoftwareSerial.h>
SoftwareSerial LabSerial(3,4); // RX, TX
#endif

#include "common.h"
DateTime systemTime;
DateTime resetTime;
unsigned long resetMills;

#include <MemoryFree.h>
#include "virtual_elements_manager.h"
#include "sensors.h"

#ifdef CENTRALINA
#include "osmotica.h"
#include "vasca.h"
#include "giardino.h"
#include "led.h"
#include "actions.h"
#endif

#ifdef LAB
#include "lab.h"
#include "pumps.h"
#endif

byte WaterFlowSensor::_pulseCount[3];
int WaterFlowSensor::_pulseIndex;


VirtualElementManager manager("MA", &Serial,true);
VirtualElementManager *manager_lab;
char mem_send[BLYNK_MAX_SENDBYTES];
//char in_buffer[MAX_RECEIVE_BUFFER]; 
 
#ifdef CENTRALINA
Osmotica *osmotica=NULL;
Vasca *vasca1=NULL;
Giardino *giardino=NULL;
Leds *leds=NULL;
#endif

#ifdef LAB
Lab *lab=NULL;
Pumps *pumps=NULL;
#endif
//WaterFlowSensor *s1;
//SolenoidValve *v1;

//#define DATETIME_ACTUAL_VPIN  120
#define DATETIME_SET_VPIN  20
#define LAB_SYNC_VPIN 1

//===================================

unsigned long clock_time=0;

class Var_SetDateTime : public Var_String
{
  public:

     Var_SetDateTime() : Var_String(DATETIME_SET_VPIN){}

     void OnCloudWrite(BlynkParam &param){
 
        value = param.asString();
           Debug("ll",value);
           
        DateTime dt = ParseDateTime(value);
        setDateTime( dt);
        Debug(F("ON SET DATETIME "), pin , dt.timestamp(DateTime::timestampOpt::TIMESTAMP_FULL));
    
    }
};

class Var_LabSync: public Var_String
{
  public:

     Var_LabSync() : Var_String(LAB_SYNC_VPIN){}

     void OnCloudWrite(BlynkParam &param){
        value = param.asString();
        Debug(F("ON LAB SYNC "), pin , " ",value);

    }
};

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  Serial.setTimeout(2000);

  Log(F("STARTING"));

  //osmotica_setup();
 // lab_setup();
 #ifdef LAB
   LabSerial.begin(57600);
   manager_lab = new VirtualElementManager("LAB",&LabSerial,false);
#endif

   clock_time=millis();

//Wire.begin();

 //   setDateTime(new DateTime(2021,5,20,16,43,0));
   // setDateTime( DateTime(2021,5,20,16,43,0));
 
 #ifdef CENTRALINA
    osmotica = new Osmotica(manager);
    giardino = new Giardino(manager);
    leds = new Leds(manager);
 #endif

 #ifdef LAB
    lab = new Lab(manager,*manager_lab);
    pumps = new Pumps(manager,*manager_lab);
 #endif

    // date

   // date = manager.addVarString(DATETIME_ACTUAL_VPIN,"");
    manager.Add(new Var_SetDateTime());
   Log(F("s"));
  if (manager_lab!=NULL)
    manager_lab->Add(new Var_LabSync());
    Log(F("s"));
     //cloudWrite(0,"INIT");
     // vasca1 = new Vasca (manager,60,95.5,EPROM_VASCA1_LEVEL);

    //v1 = manager.addSolenoidValve(45,45);
    //s1 =  manager.addWaterFlowSensor(20,2,0) ;
   // s1->Begin();

   // v1->Open();

  // actions.Add(new Action_GetWater(v1,s1,1));
/*
  manager.addSwitch(4);
  manager.addSwitch(5);
  manager.addSwitch(6);

  SolenoidValve *v1 =  manager.addSolenoidValve(7);
 Pump *p1 =  manager.addPump(9);

  Var_Bool *water_fill_enable = manager.addVarBool(102) ;
Var_String *water_state= manager.addVarString(101) ;
*/
  COMMAND(F("STARTUP"));
}

int i_time=0;
unsigned long last_time=0;
unsigned long last_time1=0;

// the loop function runs over and over again forever
void loop() 
{

  
  //return;
  clock_time=millis();

  // cloudWrite(LabSerial,1,"pippo");
  if (clock_time - last_time1> 10000)
  {
     last_time1 = clock_time;

     #ifdef TIME
    DateTime now = currentDateTime();

    COMMAND(F("MEMORY "),freeMemory());
    COMMAND(F("RUN_TIME "),clock_time);
    COMMAND(F("DATE "),now.timestamp(DateTime::timestampOpt::TIMESTAMP_FULL));
    #endif
    //cloudWrite(LabSerial,1,"pippo");
    # ifdef LAB
    //SCOMMAND(LabSerial,F("RUN_TIME "),clock_time);
     cloudWrite(LabSerial,LAB_SYNC_VPIN,clock_time);
    #endif
  }
  
  if (clock_time - last_time> 1000)
  {
     //LabSerial.println(clock_time);
     //LabSerial.println("tick");

    last_time = clock_time;
    //Com_Tick();

    manager.tick();
    if (manager_lab!=NULL)
      manager_lab->tick();
    //actions.tick();
  
 #ifdef CENTRALINA
    if (osmotica!=NULL)
      osmotica->Logic();
    if (vasca1!=NULL)
      vasca1->Logic();
    if (giardino!=NULL)
      giardino->Logic();

     if (leds!=NULL)
      leds->Logic();
#endif


 #ifdef LAB
   // if (lab!=NULL)
   //  lab->Logic();
#endif

    i_time++;
  }
  else
  {
    manager.fast_tick();
    if (manager_lab!=NULL)
      manager_lab->fast_tick();
 #ifdef LAB
    // if (lab!=NULL)
    //  lab->LogicFast();
 #endif
  }

  // delay(1);

}

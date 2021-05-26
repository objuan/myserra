/*
 * Created by marco cecchini
 *
 */

//#define MEGA

//#define CENTRALINA
#define LAB
//#define TIME

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

#include "common.h"
DateTime lastTime;

//#include "vhandlers.h"
#include "virtual_elements_manager.h"
#include "sensors.h"

#include "osmotica.h"
#include "vasca.h"
#include "giardino.h"
#include "led.h"
#include "actions.h"
#include "lab.h"

byte WaterFlowSensor::_pulseCount[3];
int WaterFlowSensor::_pulseIndex;

VirtualElementManager manager;
ActionManager actions;

Osmotica *osmotica=NULL;
Vasca *vasca1=NULL;
Giardino *giardino=NULL;
Leds *leds=NULL;
Lab *lab=NULL;

WaterFlowSensor *s1;
SolenoidValve *v1;

//#define DATETIME_ACTUAL_VPIN  120
#define DATETIME_SET_VPIN  121

//Var_String *date;

//===================================

unsigned long clock_time=0;

class Var_SetDateTime : public Var_String
{
  public:

     Var_SetDateTime() : Var_String(DATETIME_SET_VPIN){}

     void OnCloudWrite(BlynkParam &param){
        value = param.asString();
        DateTime dt = ParseDateTime(value);
        setDateTime( dt);
        Debug("ON SET DATETIME ", pin , dt.timestamp(DateTime::timestampOpt::TIMESTAMP_FULL));

    }
};

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  Serial.setTimeout(2000);
  //osmotica_setup();
 // lab_setup();
 
   
//  com.Register(CMD_PING, OnPing);

   clock_time=millis();

    Wire.begin();
 //   setDateTime(new DateTime(2021,5,20,16,43,0));
   // setDateTime( DateTime(2021,5,20,16,43,0));

 #ifdef CENTRALINA

    osmotica = new Osmotica(manager);
    giardino = new Giardino(manager);
    leds = new Leds(manager);
 #endif

 #ifdef LAB
    lab = new Lab(manager);
 #endif
    
    // date

   // date = manager.addVarString(DATETIME_ACTUAL_VPIN,"");
    manager.Add(new Var_SetDateTime());

 
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
  COMMAND("STARTUP");
}

int i_time=0;
unsigned long last_time=0;

// the loop function runs over and over again forever
void loop() 
{
  
  //return;
  clock_time=millis();

  if (clock_time - last_time> 1000)
  {
    last_time = clock_time;
    //Com_Tick();

    #ifdef TIME
    DateTime now = currentDateTime();
     
    COMMAND("RUN_TIME ",clock_time);
    COMMAND("DATE ",now.timestamp(DateTime::timestampOpt::TIMESTAMP_FULL));
    #endif

    manager.tick();
    actions.tick();
  
    if (osmotica!=NULL)
      osmotica->Logic();
    if (vasca1!=NULL)
      vasca1->Logic();
    if (giardino!=NULL)
      giardino->Logic();

     if (leds!=NULL)
      leds->Logic();

    if (lab!=NULL)
      lab->Logic();

    i_time++;
  }
  else
  {
    manager.fast_tick();

     if (lab!=NULL)
      lab->LogicFast();
  }

  // delay(1);

}

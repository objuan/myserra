/*
 * Created by marco cecchini
 *
 */

//#define  MEGA

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>
#include "config.h"
//#include "vhandlers.h"
#include "virtual_elements_manager.h"

#include "osmotica.h"
#include "vasca.h"
//include "lab.h"

VirtualElementManager manager;


Osmotica osmotica(manager);
Vasca vasca1(manager,60,95.5,0);

//===================================

unsigned long clock_time=0;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  //osmotica_setup();
 // lab_setup();
 
  cloudWrite(0,"INIT");
//  com.Register(CMD_PING, OnPing);

  clock_time=millis();

  vasca1.Init();
  
/*
  manager.addSwitch(4);
  manager.addSwitch(5);
  manager.addSwitch(6);

  SolenoidValve *v1 =  manager.addSolenoidValve(7);
 Pump *p1 =  manager.addPump(9);

  Var_Bool *water_fill_enable = manager.addVarBool(102) ;
Var_String *water_state= manager.addVarString(101) ;
*/
}

int i_time=0;
// the loop function runs over and over again forever
void loop() 
{
   // SERIAL 

  //Com_Tick();

  manager.tick();
  
  osmotica.Logic();
  vasca1.Logic();
  
  //osmotica_loop();
  //lab_loop();
 
 //virtualWrite(10,"pippo");

// virtualRead(11,"pippo");
  clock_time=millis();
  COMMAND("TIME ",clock_time);

  i_time++;
 //virtualWrite(2,33);

   delay(1000);

}

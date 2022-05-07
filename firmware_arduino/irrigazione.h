/*
 * Created by marco cecchini
 *
 */
#include <EEPROM.h>
#include <BlynkSimpleStream.h>
#include "config.h"
#include "vhandlers.h"

// constants 

// SWITCHS
#ifdef MEGA
  #define POZZO_SWITCH_PIN  42  // interruttore acqua piena
  #define PERIMETRALE_SWITCH_PIN  24  
#else
 #define POZZO_SWITCH_PIN  4  // interruttore acqua piena
 #define PERIMETRALE_SWITCH_PIN  3  
#endif


// 
DateTime piante_from(2022,1,1,  9, 0,00);
DateTime piante_to(2022,1,1,    9, 1,00);
int piante_on_secs = 30;
int piante_off_secs = 30;

DateTime perimetro_from(2022,1,1, 9,2,00);
DateTime perimetro_to(2022,1,1,   9,2,15);

Timer timer_irr("IRRIGAZIONE",0);
Timer timer_perimetro("PERIMETRO_FRAGOLE",600);

//bool sw_irrigazione=false;
//bool sw_perimetro=false;

Switch sw_irrigazione(POZZO_SWITCH_PIN,V3,&timer_irr);
Switch sw_perimetro(PERIMETRALE_SWITCH_PIN,V4,&timer_perimetro);

CLOUD_ON_WRITE(103) { 

  //Serial.println("ll");
 // sw_irrigazione = param[0].asInt() == 1;
 sw_irrigazione.setMode(param[0].asInt() );

 // Log("V103 ",param[0].asString());
}
CLOUD_ON_WRITE(104) { 
  //sw_perimetro = param[0].asInt() == 1;
  sw_perimetro.setMode(param[0].asInt());
}


void irrigazione_setup() {
  
  // initialize digital pins
   pinMode(PERIMETRALE_SWITCH_PIN, OUTPUT);
   pinMode(POZZO_SWITCH_PIN, OUTPUT);

   digitalWrite(PERIMETRALE_SWITCH_PIN, RELE_OFF);
   digitalWrite(POZZO_SWITCH_PIN, RELE_OFF);
 
  Serial.println("Irrigazione Started");

  timer_irr.setInterval(piante_from,piante_to);
  //timer_irr.setMode(TimerMode::STEP_INTERVAL);
  timer_irr.setPeriod(piante_on_secs,piante_off_secs);

   timer_perimetro.setInterval(perimetro_from,perimetro_to);
  
}


// the loop function runs over and over again forever
void irrigazione_loop(DateTime now) 
{ 
  sw_irrigazione.tick(now);
  sw_perimetro.tick(now);
 //   bool irrigazione = sw_irrigazione || timer_irr.isOn(now);
  //  bool perimetro = sw_perimetro || timer_perimetro.isOn(now);

//  irrigazione=false;
 // perimetro=true;
  
   // virtualWrite(V3,irrigazione ? "ON":"OFF");;
  //  virtualWrite(V4,perimetro ? "ON":"OFF");
      
   // digitalWrite(POZZO_SWITCH_PIN,irrigazione ? RELE_ON : RELE_OFF);

   // digitalWrite(PERIMETRALE_SWITCH_PIN,perimetro ? RELE_ON : RELE_OFF);
    
}

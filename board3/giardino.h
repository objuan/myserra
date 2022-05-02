/*
 * Created by marco cecchini
 *
 */

//#include <BlynkSimpleStream.h>
#include "config.h"
//#include "vhandlers.h"

// constants 

// SWITCHS
#ifdef MEGA
 // #define PERIMETRALE_SWITCH_PIN  24  
  #define ERBA_SWITCH_PIN  22 
#else
  #define ERBA_SWITCH_PIN  2 
#endif

DateTime erba_from(2022,1,1,  22, 00,00);
DateTime erba_to(2022,1,1,    22, 15,00);

//DateTime perimetro_from(2022,1,1, 9,2,00);
//DateTime perimetro_to(2022,1,1,   9,2,30);


Timer timer_erba("ERBA",300);
//Timer timer_perimetro("PERIMETRO",600);

bool en_giardino=false;

BLYNK_WRITE(V12) //irrigazione
{
  en_giardino =  param.asInt()==1;
}

void giardino_setup() {
  
  // initialize digital pins
 // pinMode(PERIMETRALE_SWITCH_PIN, OUTPUT);
  pinMode(ERBA_SWITCH_PIN, OUTPUT);
  
  //digitalWrite(PERIMETRALE_SWITCH_PIN, RELE_OFF);
  digitalWrite(ERBA_SWITCH_PIN, RELE_OFF);

  timer_erba.setInterval(erba_from,erba_to);
//  timer_perimetro.setInterval(perimetro_from,perimetro_to);
  
  
}



// the loop function runs over and over again forever
void giardino_loop(DateTime now) 
{ 
  bool erba =  en_giardino || timer_erba.isOn(now);
  Blynk.virtualWrite(V2,erba ? 1: 0);
  mydigitalWrite(ERBA_SWITCH_PIN, erba? RELE_ON : RELE_OFF);
    
  // mydigitalWrite(PERIMETRALE_SWITCH_PIN,timer_perimetro.isOn(now) ? RELE_ON : RELE_OFF);
 
}

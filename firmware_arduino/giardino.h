/*
 * Created by marco cecchini
 *
 */

#include <BlynkSimpleStream.h>
#include "config.h"
#include "vhandlers.h"

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
//bool sw_erba=false;

Switch sw_erba(ERBA_SWITCH_PIN,V2,&timer_erba);

CLOUD_ON_WRITE(102) { 
  sw_erba.setMode(param[0].asInt() );
  //sw_erba = param[0].asInt() == 1;
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
void giardino_loop(const DateTime &now) 
{ 
  // bool on =  sw_erba || timer_erba.isOn(now);
  
//   virtualWrite(V2, on ? F("ON"):F("OFF"));

  sw_erba.tick(now);
  
  // digitalWrite(ERBA_SWITCH_PIN,on  ? RELE_ON : RELE_OFF);
    
  // mydigitalWrite(PERIMETRALE_SWITCH_PIN,timer_perimetro.isOn(now) ? RELE_ON : RELE_OFF);
 
}

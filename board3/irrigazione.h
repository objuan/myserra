/*
 * Created by marco cecchini
 *
 */
#include <EEPROM.h>
//#include <BlynkSimpleStream.h>
#include "config.h"
//#include "vhandlers.h"

// constants 

// SWITCHS
#ifdef MEGA
  #define POZZO_SWITCH_PIN  42  // interruttore acqua piena
  #define PERIMETRALE_SWITCH_PIN  24  
#else
 #define POZZO_SWITCH_PIN  3  // interruttore acqua piena
 #define PERIMETRALE_SWITCH_PIN  4  
#endif


// 
DateTime piante_from(2022,1,1,  9, 0,00);
DateTime piante_to(2022,1,1,    9, 1,00);
int piante_on_secs = 30;
int piante_off_secs = 30;

DateTime perimetro_from(2022,1,1, 9,2,00);
DateTime perimetro_to(2022,1,1,   9,2,30);

Timer timer_irr("IRRIGAZIONE",0);
Timer timer_perimetro("PERIMETRO_FRAGOLE",600);

bool en_irrigazione=false;
bool en_perimetro=false;

BLYNK_WRITE(V13) //irrigazione
{
  en_irrigazione =  param.asInt()==1;
}
BLYNK_WRITE(V14) // perimetro
{
  en_perimetro =  param.asInt()==1;
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
    bool irr =  en_irrigazione || timer_irr.isOn(now);
    Blynk.virtualWrite(V3,irr ? 1: 0);
  
    mydigitalWrite(POZZO_SWITCH_PIN,irr ? RELE_ON : RELE_OFF);

    bool perimetro =  en_perimetro || timer_perimetro.isOn(now);
    Blynk.virtualWrite(V4,perimetro ? 1: 0);
  
     mydigitalWrite(PERIMETRALE_SWITCH_PIN,perimetro ? RELE_ON : RELE_OFF);
    
}

/*
 * Created by marco cecchini
 *
 */

#include <BlynkSimpleStream.h>
#include "config.h"
#include "vhandlers.h"

// constants 

// SWITCHS
#if MEGA
  #define TOP_SWITCH_PIN  53  // interruttore acqua piena
  #define FILL_SWITCH_PIN  51  // interruttore inizzio acqua piena
  #define DANGER_SWITCH_PIN  49  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define WATER_IN_SOLENOID_PIN 47   // eletrovalvola acqua in ingresso 
  #define WATER_OUT_RELE_PIN 44    //   rele pompa di uscita
#else
  #define TOP_SWITCH_PIN  2  // interruttore acqua piena
  #define FILL_SWITCH_PIN  3  // interruttore inizzio acqua piena
  #define DANGER_SWITCH_PIN  4  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define WATER_IN_SOLENOID_PIN 5   // eletrovalvola acqua in ingresso 
  #define WATER_OUT_RELE_PIN 6    //   rele pompa di uscita
#endif

#define WATER_STATE_VPIN 101  // 
#define WATER_ENABLE_VPIN 102  // 

// the setup function runs once when you press reset or power the board

// variables will change:
int top_state = -1;         //  0 = not active, 1 = active 
int fill_state = -1;         //  0 = not active, 1 = active 
int danger_state = -1;         //  0 = not active, 1 = active 

int water_enable =0;         //  0 = not active, 1 = active 

#define STATE_IDDLE "IDDLE"
#define STATE_FILL "FILLING"

String in_water_state = STATE_IDDLE;

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

void osmotica_setup() {
  
  // initialize digital pins
  pinMode(WATER_IN_SOLENOID_PIN, OUTPUT);
  pinMode(WATER_OUT_RELE_PIN, OUTPUT);
  
  pinMode(TOP_SWITCH_PIN, INPUT);
  pinMode(FILL_SWITCH_PIN, INPUT);
  pinMode(DANGER_SWITCH_PIN, INPUT);

  digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_OFF);
  digitalWrite(WATER_OUT_RELE_PIN, RELE_OFF);
  
  Serial.println("Osmotica Started");
}

//

void loadState()
{
  
  // read the state of the switch values:
  int _top_state = digitalRead(TOP_SWITCH_PIN);
  int _fill_state = digitalRead(FILL_SWITCH_PIN);
  int _danger_state = digitalRead(DANGER_SWITCH_PIN);

  if (top_state!=_top_state)
  {
    top_state=_top_state;
    cloudWrite(TOP_SWITCH_PIN,digitalRead(TOP_SWITCH_PIN));
    //Serial.print("top_state=");
   // Serial.println(top_state);
  }
 if (fill_state!=_fill_state)
  {
    fill_state=_fill_state;
    cloudWrite(FILL_SWITCH_PIN,digitalRead(FILL_SWITCH_PIN));
   // Serial.print("fill_state=");
   // Serial.println(fill_state);
  }
  if (danger_state!=_danger_state)
  {
    danger_state=_danger_state;
    cloudWrite(DANGER_SWITCH_PIN,digitalRead(DANGER_SWITCH_PIN));
   // Serial.print("danger_state=");
   // Serial.println(danger_state);
  }
}

bool isFull()
{
  return top_state==1;
}

bool needWater()
{
  return fill_state==1;
}

CLOUD_ON_WRITE(  WATER_ENABLE_VPIN){

 water_enable =  param.asInt();
  Debug("WATER_ENABLE_VPIN" , param.asInt());
}
    
CLOUD_ON_WRITE(WATER_OUT_RELE_PIN){

   if (param.asInt()==1)
   {
      digitalWrite(WATER_OUT_RELE_PIN, RELE_ON);
      Debug("PUMP " ,"ON");
   }
   else
   {
      digitalWrite(WATER_OUT_RELE_PIN, RELE_OFF);
      Debug("PUMP " ,"OFF");
   }
      //int valPin = param.asInt();
}

CLOUD_ASK_VALUE(WATER_IN_SOLENOID_PIN){
      cloudWrite(WATER_IN_SOLENOID_PIN,digitalRead(WATER_IN_SOLENOID_PIN));
}
CLOUD_ASK_VALUE(WATER_OUT_RELE_PIN){
      cloudWrite(WATER_OUT_RELE_PIN,digitalRead(WATER_OUT_RELE_PIN));
}
CLOUD_ASK_VALUE(TOP_SWITCH_PIN){
      cloudWrite(TOP_SWITCH_PIN,digitalRead(TOP_SWITCH_PIN));
}   
CLOUD_ASK_VALUE(FILL_SWITCH_PIN){
      cloudWrite(FILL_SWITCH_PIN,digitalRead(FILL_SWITCH_PIN));
}   
CLOUD_ASK_VALUE(DANGER_SWITCH_PIN){
      cloudWrite(DANGER_SWITCH_PIN,digitalRead(DANGER_SWITCH_PIN));
} 
CLOUD_ASK_VALUE(WATER_STATE_VPIN){
      cloudWrite(WATER_STATE_VPIN,in_water_state);
}   


// the loop function runs over and over again forever
void osmotica_loop() 
{
  loadState();

  // LOGICA

 if (water_enable==1)
 {
  if (in_water_state == STATE_IDDLE)
  {
      if (needWater())
      {
         in_water_state = STATE_FILL;
         cloudWrite(WATER_STATE_VPIN,in_water_state);
         
         digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_ON);
         cloudWrite(WATER_IN_SOLENOID_PIN,digitalRead(WATER_IN_SOLENOID_PIN));
          
         Log("STATE_WATER = FILLING");
      }
   }
   else  if (in_water_state == STATE_FILL)
   {
      if (isFull())
      {
         in_water_state = STATE_IDDLE;
         cloudWrite(WATER_STATE_VPIN,in_water_state);
         
         digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_OFF);
         cloudWrite(WATER_IN_SOLENOID_PIN,digitalRead(WATER_IN_SOLENOID_PIN));
         
        Log("STATE_WATER = IDDLE");
      }
   }
 }

}

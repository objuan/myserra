/*
 * Created by marco cecchini
 *
 */

//#include <BlynkSimpleStream.h>
//#include "config.h"

// constants 


// the setup function runs once when you press reset or power the board

// variables will change:
int top_state = -1;         //  0 = not active, 1 = active 
int fill_state = -1;         //  0 = not active, 1 = active 
int danger_state = -1;         //  0 = not active, 1 = active 

int water_enable =1;         //  0 = not active, 1 = active 

#define STATE_IDDLE "IDDLE"
#define STATE_FILL "FILLING"

String in_water_state = STATE_IDDLE;

BLYNK_WRITE(VPIN_WATER_ENABLE) { 
   
   water_enable = param[0].asInt()==1;
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

void osmotica_setup() {
  
  // initialize digital pins
 
  
  pinMode(TOP_SWITCH_PIN, INPUT);
  pinMode(FILL_SWITCH_PIN, INPUT);
  pinMode(DANGER_SWITCH_PIN, INPUT);

  pinMode(WATER_IN_SOLENOID_PIN, OUTPUT);
 // pinMode(WATER_OUT_RELE_PIN, OUTPUT);
  digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_OFF);
 // digitalWrite(WATER_OUT_RELE_PIN, RELE_OFF);
  
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
   // cloudWrite(TOP_SWITCH_PIN,digitalRead(TOP_SWITCH_PIN));
    Serial.print("top_state=");
    Serial.println(top_state);
  }
 if (fill_state!=_fill_state)
  {
    fill_state=_fill_state;
   // cloudWrite(FILL_SWITCH_PIN,digitalRead(FILL_SWITCH_PIN));
    Serial.print("fill_state=");
    Serial.println(fill_state);
  }
  if (danger_state!=_danger_state)
  {
    danger_state=_danger_state;
   //cloudWrite(DANGER_SWITCH_PIN,digitalRead(DANGER_SWITCH_PIN));
    Serial.print("danger_state=");
    Serial.println(danger_state);
  }
}

bool isFull()
{
  return false;//top_state==1;
}

bool needWater()
{
  return true;//fill_state==1;
}

// the loop function runs over and over again forever
void osmotica_loop(const DateTime &now) 
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
          Blynk.virtualWrite(VPIN_WATER_STATE,"FILLING");
         
         digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_ON);
     
          Serial.println("STATE_WATER = FILLING");
         Log("STATE_WATER = FILLING");
      }
   }
   else  if (in_water_state == STATE_FILL)
   {
      if (isFull())
      {
         in_water_state = STATE_IDDLE;
         Blynk.virtualWrite(VPIN_WATER_STATE,"IDDLE");
         
         digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_OFF);
         
        Serial.println("STATE_WATER = IDDLE");
        Log("STATE_WATER = IDDLE");
      }
   }
 }
 else
 {
   if (in_water_state == STATE_FILL)
   {
    
         in_water_state = STATE_IDDLE;
         Blynk.virtualWrite(VPIN_WATER_STATE,"IDDLE");
         
         digitalWrite(WATER_IN_SOLENOID_PIN, SOLENOID_OFF);
         
        Serial.println("STATE_WATER = IDDLE");
        Log("STATE_WATER = IDDLE");

   }
 }
}

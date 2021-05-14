
#include "virtual_elements.h"


// =====================================================

class Switch : public VirtualElement_Bool
{
public:

   VirtualElement_Type getType() {return VirtualElement_Type::SWITCH ; }

   Switch(int pin) : VirtualElement_Bool(pin){
        pinMode(pin, INPUT);
        cloudWrite(this->pin,digitalRead(this->pin));
   }

    void OnCloudAskValue(){
        cloudWrite(this->pin,digitalRead(this->pin));
    }
   void tick(){
      int v = digitalRead(this->pin);

      //Debug("Switch", this->pin,v);
      if (v !=  this->value)
      {
        this->value=v;
        cloudWrite(this->pin,this->value);
      }
   }
};

class SolenoidValve : public VirtualElement_Bool
{
public:

   VirtualElement_Type getType() {return VirtualElement_Type::SOLENOID_VALVE ; }

   SolenoidValve(int pin) : VirtualElement_Bool(pin){
        pinMode(pin, OUTPUT);
        digitalWrite(pin, SOLENOID_OFF);
   }
   void Open(){
      Debug("SolenoidValve Open");
      digitalWrite(pin, SOLENOID_ON);
      cloudWrite(this->pin,1);    
   }
   void Close(){
    Debug("SolenoidValve Close");
      digitalWrite(pin, SOLENOID_OFF);
      cloudWrite(this->pin,0);    
   }
   void OnCloudWrite(BlynkParam &param){
         //Debug("OnCloudWrite", param.asInt());
         if (param.asInt()==1)
         {
            digitalWrite(pin, SOLENOID_ON);
            Debug("SolenoidValve " ,pin, "ON");
         }
         else
         {
            digitalWrite(pin, SOLENOID_OFF);
            Debug("SolenoidValve " ,pin, "OFF");
         }
    }
};


class Pump : public VirtualElement_Bool
{
public:

   VirtualElement_Type getType() {return VirtualElement_Type::PUMP ; }

   Pump(int pin) : VirtualElement_Bool(pin){
        pinMode(pin, OUTPUT);
   }
   void OnCloudWrite(BlynkParam &param){
         if (param.asInt()==1)
         {
            digitalWrite(pin, RELE_ON);
            Debug("Pump " ,pin, "ON");
         }
         else
         {
            digitalWrite(pin, RELE_OFF);
            Debug("Pump " ,pin, "OFF");
         }
    }
};


/*
 *  TRIG - connect to digital pin 12.  Can be any digital pin
 * ECHO - connect to digital pin 13.  Can be any digital pin
 * -> virtual pin 
 */
class DistanceSensor : public VirtualElement_Real
{
private:

  float temp_In_C = 20.0;  // Can enter actual air temp here for maximum accuracy or read with sensor
  float speed_Of_Sound;          // Calculated speed of sound based on air temp
  float distance_Per_uSec;      // Distance sound travels in one microsecond at that temp
  int TRIG_PIN;
  int ECHO_PIN;
  float distanceCm=0;
  int updateTime_ms = 2000;
  unsigned long lastTime=0;
public:

   VirtualElement_Type getType() {return VirtualElement_Type::DISTANCE ; }

   DistanceSensor(int virtual_pin, int TRIG_PIN,int ECHO_PIN) : VirtualElement_Real(virtual_pin){
      speed_Of_Sound = 331.1 +(0.606 * temp_In_C);  
      // Calculate the distance that sound travels in one microsecond in Centimeters
      distance_Per_uSec = speed_Of_Sound / 10000.0;
      this->TRIG_PIN=TRIG_PIN;
       this->ECHO_PIN=ECHO_PIN;
      
       pinMode(TRIG_PIN,OUTPUT);
       pinMode(ECHO_PIN,INPUT);
   }
   void OnCloudAskValue(){
        cloudWrite(this->pin,distanceCm);
    }
   void tick(){
        unsigned long  t =  millis();
        if (t - lastTime > updateTime_ms)
        {
          lastTime = t;
            float duration;
            digitalWrite(TRIG_PIN, HIGH);       // Set trigger pin HIGH 
            delayMicroseconds(10);              // Hold pin HIGH for 10 uSec
            digitalWrite(TRIG_PIN, LOW);        // Return trigger pin back to LOW again.
            duration = pulseIn(ECHO_PIN,HIGH);  // Measure time in uSec for echo to come back.

            // convert the time data into a distance in centimeters, inches and feet
            duration = duration / 2.0;  // Divide echo time by 2 to get the time for the sound to travel in one direction
            distanceCm = duration * distance_Per_uSec;
            
             this->value = distanceCm;
            cloudWrite(this->pin, this->value );
        }
        
   }
   
  
};

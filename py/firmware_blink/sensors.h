#ifndef _Sensors
#define _Sensors

#include "virtual_elements.h"


// =====================================================

class Switch : public VirtualElement_Bool
{
  int arduino_pin;
public:

   VirtualElement_Type getType() {return VirtualElement_Type::SWITCH ; }

   Switch(int virtual_pin,int arduino_pin) : VirtualElement_Bool(virtual_pin),arduino_pin(arduino_pin){
      // avoid write here
   }

   void start(){
       pinMode(arduino_pin, INPUT);
        cloudWrite(this->pin,digitalRead(this->arduino_pin));
   }

    void OnCloudAskValue(){
        cloudWrite(this->pin,digitalRead(this->arduino_pin));
    }
    void tick(){
      int v = digitalRead(this->arduino_pin);

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
  int arduino_pin;
public:

   VirtualElement_Type getType() {return VirtualElement_Type::SOLENOID_VALVE ; }

   SolenoidValve(int virtual_pin,int arduino_pin) : VirtualElement_Bool(virtual_pin),arduino_pin(arduino_pin){
       
   }
   void start(){
     pinMode(arduino_pin, OUTPUT);
     digitalWrite(arduino_pin, SOLENOID_OFF);
   }
   
   
   void Open(){
      Debug("SolenoidValve Open ",pin, " ",arduino_pin);
      digitalWrite(arduino_pin, SOLENOID_ON);
      cloudWrite(this->pin,1);    
   }
   void Close(){
    Debug("SolenoidValve Close ",pin, " ",arduino_pin);
      digitalWrite(arduino_pin, SOLENOID_OFF);
      cloudWrite(this->pin,0);    
   }
   void OnCloudWrite(BlynkParam &param){
         //Debug("OnCloudWrite", param.asInt());
         if (param.asInt()==1)
         {
            digitalWrite(arduino_pin, SOLENOID_ON);
            Debug("SolenoidValve " ,pin, "ON");
         }
         else
         {
            digitalWrite(arduino_pin, SOLENOID_OFF);
            Debug("SolenoidValve " ,pin, "OFF");
         }
    }
};


class Pump : public VirtualElement_Bool
{
  int arduino_pin;
public:
  
   VirtualElement_Type getType() {return VirtualElement_Type::PUMP ; }

   Pump(int virtual_pin,int arduino_pin) : VirtualElement_Bool(virtual_pin),arduino_pin(arduino_pin){
       
   }
    void start(){
       pinMode(arduino_pin, OUTPUT);
    }
    
   void OnCloudWrite(BlynkParam &param){
         if (param.asInt()==1)
         {
            digitalWrite(arduino_pin, RELE_ON);
            Debug("Pump " ,pin, "ON");
         }
         else
         {
            digitalWrite(arduino_pin, RELE_OFF);
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

   DistanceSensor(int virtual_pin, int TRIG_PIN,int ECHO_PIN) : VirtualElement_Real(virtual_pin),TRIG_PIN(TRIG_PIN),ECHO_PIN(ECHO_PIN){
   }
     
    void start(){
       speed_Of_Sound = 331.1 +(0.606 * temp_In_C);  
      // Calculate the distance that sound travels in one microsecond in Centimeters
       distance_Per_uSec = speed_Of_Sound / 10000.0;
       
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

  
/*
 * Measure the liquid/water flow rate using this code. 
Connect Vcc and Gnd of sensor to arduino, and the 
signal line to arduino digital pin 2.
 */
class WaterFlowSensor : public VirtualElement_Real
{
public:
  static byte _pulseCount[3];
  static int _pulseIndex;
 
  // The hall-effect flow sensor outputs approximately 4.5 pulses per second per
  // litre/minute of flow.
  float calibrationFactor = 4.5;
  //volatile byte pulseCount;
  int pulseIndex;

  // L/min
  float flowRate;
  unsigned int flowMilliLitres;
  unsigned long totalMilliLitres;
  unsigned long oldTime;
  
  int SENSOR_PIN;
  int SENSOR_INTERRUPT;
public:

    float totalLiters(){
        return float(totalMilliLitres) / 1000;
    }  
    VirtualElement_Type getType() {return VirtualElement_Type::WATER_FLOW ; }

   WaterFlowSensor(int virtual_pin, int SENSOR_PIN,int SENSOR_INTERRUPT) : VirtualElement_Real(virtual_pin){
       this->SENSOR_PIN=SENSOR_PIN;
        this->SENSOR_INTERRUPT=digitalPinToInterrupt(SENSOR_PIN);//SENSOR_INTERRUPT;

   }

   void start(){
     
        //digitalPinToInterrupt
       
        pinMode(SENSOR_PIN, INPUT);
        digitalWrite(SENSOR_PIN, HIGH);

        pulseIndex = _pulseIndex;
        _pulseIndex++;

         Log("WaterFlowSensor Init at " , pulseIndex," pin:",SENSOR_PIN," int:" ,this->SENSOR_INTERRUPT );
   }

    static inline void  pulseCounter_0()
    { 
        _pulseCount[0]++;
    }
    static inline void  pulseCounter_1()
    {  
        _pulseCount[1]++;
    }  
    static inline void  pulseCounter_2()
    {  
        _pulseCount[2]++;
    }
    
   void Begin()
   {
      _pulseCount[pulseIndex]        = 0;
      flowRate          = 0.0;
      flowMilliLitres   = 0;
      totalMilliLitres  = 0;
      oldTime           = 0;

              
        // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
        // Configured to trigger on a FALLING state change (transition from HIGH
        // state to LOW state)
        if (pulseIndex==0)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_0, FALLING);
        else if (pulseIndex==1)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_1, FALLING);
        else   if (pulseIndex==2)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_2, FALLING);
   }
    void End(){
      
    }
   
    void OnCloudAskValue(){
        cloudWrite(this->pin,float(totalMilliLitres) / 1000);
    }
    
    void tick(){
       
       if((millis() - oldTime) > 1000)    // Only process counters once per second
      { 
        // Disable the interrupt while calculating flow rate and sending the value to
        // the host
        detachInterrupt(SENSOR_INTERRUPT);
            
        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.
        flowRate = ((1000.0 / (millis() - oldTime)) * _pulseCount[pulseIndex]) / calibrationFactor;
        
        // Note the time this processing pass was executed. Note that because we've
        // disabled interrupts the millis() function won't actually be incrementing right
        // at this point, but it will still return the value it was set to just before
        // interrupts went away.
        oldTime = millis();
        
        // Divide the flow rate in litres/minute by 60 to determine how many litres have
        // passed through the sensor in this 1 second interval, then multiply by 1000 to
        // convert to millilitres.
        flowMilliLitres = (flowRate / 60) * 1000;
        
        // Add the millilitres passed in this second to the cumulative total
        totalMilliLitres += flowMilliLitres;

          /*
        unsigned int frac;
        
        // Print the flow rate for this second in litres / minute
        Serial.print("Flow rate: ");
        Serial.print(int(flowRate));  // Print the integer part of the variable
        Serial.print("L/min");
        Serial.print("\t");       // Print tab space
        */
    
        // Print the cumulative total of litres flowed since starting
     /*   Serial.print("Output Liquid Quantity: ");        
        Serial.print(totalMilliLitres);
        Serial.println("mL"); 
        Serial.print("\t");       // Print tab space
      Serial.print(totalMilliLitres/1000);
      Serial.print("L");
        */
    
        // Reset the pulse counter so we can start incrementing again
        _pulseCount[pulseIndex] = 0;
        
        // Enable the interrupt again now that we've finished sending output
          if (pulseIndex==0)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_0, FALLING);
        else if (pulseIndex==1)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_1, FALLING);
        else   if (pulseIndex==2)
          attachInterrupt(SENSOR_INTERRUPT, &WaterFlowSensor::pulseCounter_2, FALLING);
      }
   }
};
#endif

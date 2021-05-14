/*
 * Created by marco cecchini
 *
 */
#ifndef __VirtualElement
#define __VirtualElement

#include <SoftwareSerial.h>

#include <BlynkSimpleStream.h>
#include "config.h"


enum VirtualElement_Type
{
  NONE,
  SWITCH,
  SOLENOID_VALVE,
  PUMP,
  DISTANCE
};

class VirtualElement
{
public:
  int pin;
  virtual VirtualElement_Type getType() {  return VirtualElement_Type::NONE ;  }

   VirtualElement(int pin){
       this->pin=pin;
   }
    virtual void tick()
    {
    }
    virtual void OnCloudWrite(BlynkParam &param){
    }
   virtual void OnCloudAskValue(){
    }
};

class VirtualElement_Bool : public VirtualElement
{
  protected:
      int value; // 0 ,1 
  public:
     VirtualElement_Bool(int pin) : VirtualElement(pin){
        this->value=-1;
     }
     bool get(){ return value == 1;}
     
};

class VirtualElement_String : public VirtualElement
{
  protected:
      String value; 
  public:
     VirtualElement_String(int pin) : VirtualElement(pin){
        this->value="";
     }
     String get(){ return value;}
   
};


class VirtualElement_Real : public VirtualElement
{
  protected:
      float value; 
  public:
     VirtualElement_Real(int pin) : VirtualElement(pin){
        this->value=0;
     }
     float get(){ return value;}
   
};

// =======================================

class Var_Bool : public VirtualElement_Bool
{
  public:

     Var_Bool(int pin) : VirtualElement_Bool(pin){
       value=0;
     }

    
     void set(bool value){
        this->value = (value) ? 1 : 0;
        cloudWrite(this->pin, this->value );
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asInt();
        Debug("ON SET BOOL ", pin , value);
    }
};


class Var_String : public VirtualElement_String
{
  public:

     Var_String(int pin) : VirtualElement_String(pin){
     }

    
     void set(String value){
        this->value = value;
        cloudWrite(this->pin, this->value );
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asString();
        Debug("ON SET STRING ", pin , value);
    }
};


class Var_Real : public VirtualElement_Real
{
  public:

     Var_Real(int pin) : VirtualElement_Real(pin){
     }

    
     void set(float value){
        this->value = value;
        cloudWrite(this->pin, this->value );
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asFloat();
        Debug("ON SET REAL ", pin , value);
    }
};
#endif

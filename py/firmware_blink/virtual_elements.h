/*
 * Created by marco cecchini
 *
 */

#include <SoftwareSerial.h>

#include <BlynkSimpleStream.h>
#include "config.h"


enum VirtualElement_Type
{
  NONE,
  SWITCH,
  SOLENOID_VALVE,
  PUMP
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

// =====================================================

class VirtualElementManager
{
    VirtualElement* list[100];
    int count=0;

    char mem[BLYNK_MAX_SENDBYTES];
public:
  
   Switch *addSwitch(int pin) {
      Switch *sw = new Switch(pin);
      Add(sw);
      return sw;
  }
  
  SolenoidValve *addSolenoidValve(int pin) {
      SolenoidValve *sw = new SolenoidValve(pin);
       Add(sw);
      return sw;
  }

  Pump *addPump(int pin) {
      Pump *sw = new Pump(pin);
       Add(sw);
      return sw;
  }
  
  Var_Bool *addVarBool(int pin) {
      Var_Bool *sw = new Var_Bool(pin);
       Add(sw);
      return sw;
  }

  Var_String *addVarString(int pin) {
      Var_String *sw = new Var_String(pin);
       Add(sw);
      return sw;
  }

  void Add(VirtualElement *ele){
    list[count++] = ele;
  }
  VirtualElement *Find(int pin)
  {
      for(int i=0;i<this->count;i++)
        if (this->list[i]->pin == pin) return list[i];
      return NULL;
  }
  
  void tick()
  {
    while (Serial.available() > 0 ) {
      //char comando = toLowerCase(Serial.read());
      //String str = Serial.readString();
      String str = Serial.readStringUntil('\n');

      Debug("<<" , str);

     if (str.startsWith("CMD PING_REQ")) {
        COMMAND("PING_ACQ");
     }
      if (str.startsWith("_vw ")) {
       
         int idx = str.indexOf(" ",4);
         int pin = str.substring(4,idx).toInt();
         String _s=str.substring(idx+1);

       // Debug("W" , pin , _s );

      //  BlynkParamAllocated pars(_s.length());
      //  pars.add(_s);

    
         BlynkParam pars(this->mem, 0, sizeof(this->mem));
      
          pars.add(_s);
          
         //Debug("PIN2" , pin , pars.asInt());

          VirtualElement *ele = Find(pin);
          if (ele!=NULL)
            ele->OnCloudWrite(pars);
          
     // pars.
       // VirtualReq req;
       // req.pin = pin;
       // GetVWriteHandler(pin)(req,pars);
        
      }
      if (str.startsWith("_vr ")) {
       
         int pin = str.substring(4).toInt();
      
        // Debug("R" , pin );

         VirtualElement *ele = Find(pin);
          if (ele!=NULL)
              ele->OnCloudAskValue();
            
        //VirtualReq req;
       // req.pin = pin;
      //  GetVReadHandler(pin)(req);
        
      }
   }
  
    for(int i=0;i<this->count;i++)
    {
        list[i]->tick();
    }
    
  }
  
  
} ;

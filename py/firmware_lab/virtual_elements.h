/*
 * Created by marco cecchini
 *
 */
#ifndef __VirtualElement
#define __VirtualElement

#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
#include <Stream.h>

enum VirtualElement_Type
{
  NONE,
  SWITCH,
  SOLENOID_VALVE,
  WATER_FLOW,
  PUMP,
  DISTANCE
};


class VirtualElement
{
public:
  Stream *serial=NULL;
  bool fromWeb;;
  // virtual pin
  int pin;
  virtual VirtualElement_Type getType() {  return VirtualElement_Type::NONE ;  }

   VirtualElement(int pin){
       this->pin=pin;
   }
    virtual void start()
    {
    }
    virtual void tick()
    {
    }
    virtual void OnCloudWrite(BlynkParam &param){
    }
   virtual void OnCloudAskValue(){
    }
    
    template <typename... Args>
   void cloudWrite(int pin, Args... values) {
   //  char mem[BLYNK_MAX_SENDBYTES];
   /* if (fromWeb)
    {
      Debug("WEB",pin);
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add_multi(values...);

        serial->print("_vw ");
        serial->print(pin);
        serial->print(" ");
        serial->print(cmd.asStr());
         serial->print("\n");
    }
    else*/
    {
 #ifdef DEBUG_MODE
    if (serial==NULL)
        Error(F("serial null"));
#endif
    
        BlynkParam cmd(mem_send, 0, sizeof(mem_send));
        cmd.add(F("vw"));
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        serial->write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
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
   int EPROM_ADDRESS; // -1 = disabled
  public:

     Var_Bool(int pin,int EPROM_ADDRESS=-1) : VirtualElement_Bool(pin),EPROM_ADDRESS(EPROM_ADDRESS){
       value=0;
       if (EPROM_ADDRESS!=-1)
          value = EEPROM_ReadByte(EPROM_ADDRESS);
     }

    
     void set(bool value){
       //Debug("set",pin,value);
       if (this->value!=value)
       {
        this->value = (value) ? 1 : 0;
        cloudWrite(this->pin, this->value );
       }
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asInt();
        Debug(F("ON SET BOOL "), pin , value);
        if (EPROM_ADDRESS!=-1)
          EEPROM_Write(EPROM_ADDRESS,(byte)this->value);
    }
};


class Var_String : public VirtualElement_String
{
  public:

     Var_String(int pin) : VirtualElement_String(pin){
     }

    
     void set(String value){
      if (this->value!=value)
      {
        this->value = value;
        cloudWrite(this->pin, this->value );
      }
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asString();
        Debug(F("ON SET STRING "), pin , value);
    }
};


class Var_Real : public VirtualElement_Real
{
   int EPROM_ADDRESS; // -1 = disabled
  public:

     Var_Real(int pin,int EPROM_ADDRESS=-1) : VirtualElement_Real(pin),EPROM_ADDRESS(EPROM_ADDRESS){
       value=0;
       if (EPROM_ADDRESS!=-1)
          value = EEPROM_ReadFloat(EPROM_ADDRESS);
     }
    
     void set(float value){
      if (this->value!=value)
      {
        this->value = value;
        cloudWrite(this->pin, this->value );
      }
     }
     void OnCloudAskValue(){
        cloudWrite(this->pin,this->value);
     }
     virtual void OnCloudWrite(BlynkParam &param){
        value = param.asFloat();
        Debug(F("ON SET REAL "), pin , value,F(" at:"), EPROM_ADDRESS);
        if (EPROM_ADDRESS!=-1)
          EEPROM_Write(EPROM_ADDRESS,this->value);
    }
};

 // value is a json array, 3 dimension
class Var_RealVector3 : public Var_String
{
   int EPROM_ADDRESS; // -1 = disabled
   float data[3];
   
  public:

     Var_RealVector3(int pin, int EPROM_ADDRESS=-1) : Var_String(pin),EPROM_ADDRESS(EPROM_ADDRESS){
       value="";
       if (EPROM_ADDRESS!=-1)
          value = EEPROM_ReadFloat(EPROM_ADDRESS);
     }

     
   
     void Read(){
            const size_t CAPACITY = JSON_ARRAY_SIZE(3);
            StaticJsonDocument<CAPACITY> doc;
            DeserializationError error = deserializeJson(doc, value);
             if (error) {
               Error("deserializeJson() failed: ");
               Error(error.f_str());
              return ;
            }
            JsonArray array = doc.to<JsonArray>();
            data[0]=  array[0].as<float>();
            data[1]=  array[1].as<float>();
            data[2]=  array[2].as<float>();
     }
      void Write(){
            const size_t CAPACITY = JSON_ARRAY_SIZE(3);
            StaticJsonDocument<CAPACITY> doc;
            JsonArray array = doc.to<JsonArray>();
            array.add(data[0]);
            array.add(data[1]);
            array.add(data[2]);
           // value = serializeJson(doc,);
     }
};

// 
// COMMON VARS


class Var_SCHEDULING : public Var_String
{
  public:

    TimeSpan time_da; // tempo dalla mezzanotte
    TimeSpan time_a;
    int eprom_da;
    int eprom_a;

     Var_SCHEDULING(int vpin,int eprom_da,int eprom_a) : Var_String(vpin),eprom_da(eprom_da),eprom_a(eprom_a){
        long da_secs = EEPROM_ReadLong(eprom_da);
        long a_secs = EEPROM_ReadLong(eprom_a);

        time_da = TimeSpan(da_secs);
        time_a = TimeSpan(a_secs);

     }
     void start(){

        Log(F("VAR SCHEDULING INIT DA:") ,time_da.totalseconds ()," A:" ,time_a.totalseconds ());
      }

     void OnCloudWrite(BlynkParam &param){
        value = param.asString();
/*
        // DynamicJsonDocument doc(1024);
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, value);
      
        // Test if parsing succeeds.
        if (error) {
          Error("deserializeJson() failed: ");
          Error(error.f_str());
          return;
        }
        
         String da_hh = doc["da"]["HH"];
         String da_mm = doc["da"]["mm"];

         String a_hh = doc["a"]["HH"];
         String a_mm = doc["a"]["mm"];
         
         Debug("da_hh",da_hh);
         time_da = TimeSpan(3600 *  da_hh.toInt() + 60 * da_mm.toInt());
         time_a = TimeSpan(3600 *  a_hh.toInt() + 60 * a_mm.toInt());

        EEPROM_Write(eprom_da,(long)time_da.totalseconds ());
        EEPROM_Write(eprom_a,(long)time_a.totalseconds ());

        Debug(F("ON SCHEDULING "), pin,value,time_da.totalseconds (),time_a.totalseconds ()  );
*/
    }
};


#endif

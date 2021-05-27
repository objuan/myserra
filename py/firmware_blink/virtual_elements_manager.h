/*
 * Created by marco cecchini
 *
 */

#include "config.h"
#include "virtual_elements.h"
#include "sensors.h"

#define MAX_VARS 32
#define MAX_RECEIVE_BUFFER BLYNK_MAX_SENDBYTES

class VirtualElementManager
{
    VirtualElement* list[MAX_VARS];
    int count=0;

    char mem[MAX_RECEIVE_BUFFER]; 
public:
  VirtualElementManager(){
     full_str="";
     
   }
   Switch *addSwitch(int virtual_pin,int arduino_pin) {
      Switch *sw = new Switch(virtual_pin,arduino_pin);
      Add(sw);
      return sw;
  }
  
  SolenoidValve *addSolenoidValve(int virtual_pin,int arduino_pin) {
      SolenoidValve *sw = new SolenoidValve(virtual_pin,arduino_pin);
       Add(sw);
      return sw;
  }

  Pump *addPump(int virtual_pin,int arduino_pin) {
      Pump *sw = new Pump(virtual_pin,arduino_pin);
       Add(sw);
      return sw;
  }

   DistanceSensor *addDistance(int virtual_pin,int TRIG_PIN,int ECHO_PIN) {
      DistanceSensor *sw = new DistanceSensor(virtual_pin,TRIG_PIN,ECHO_PIN);
       Add(sw);
      return sw;
  }

  WaterFlowSensor *addWaterFlowSensor(int virtual_pin, int SENSOR_PIN,int SENSOR_INTERRUPT) {
        WaterFlowSensor *sw = new WaterFlowSensor(virtual_pin,SENSOR_PIN,SENSOR_INTERRUPT);
       Add(sw);
      return sw;
  }
  

  // ===============================
  

  Var_Bool *addVarBool(int pin,bool startValue=false,int eprom_address=-1) {
       Var_Bool *sw = new Var_Bool(pin,eprom_address);
       Add(sw);
       if (eprom_address==-1)
          sw->set(startValue);
      return sw;
  }

 Var_String *addVarString(int pin,const String& startValue="") {
      Var_String *sw = new Var_String(pin);
       Add(sw);
       if (startValue!="")
         sw->set(startValue);
      return sw;
  }

  Var_Real *addVarReal(int pin,float startValue=0,int eprom_address=-1) {
      Var_Real *sw = new Var_Real(pin,eprom_address);
       Add(sw);
       if (eprom_address==-1)
          sw->set(startValue);

      return sw;
  }
  
  VirtualElement* Add(VirtualElement *ele){
    if (count == MAX_VARS)
      Error("TOO VARS");
      
    list[count++] = ele;
    return ele;
  }
  VirtualElement *Find(int pin)
  {
      for(int i=0;i<this->count;i++)
        if (this->list[i]->pin == pin) return list[i];
      return NULL;
  }

 void Process(String &str)
 { 
         Debug("<<" , str);
    
         if (str.startsWith(F("CMD PING_REQ"))) {
            COMMAND(F("PING_ACQ"));
         }
    
       //  if (str.startsWith("_vw _vw")) 
       ///   str = str.substring(4);
         
          if (str.startsWith("_vw ")) {
    
             //Debug("<<" , str);
             if ( str.endsWith(F("\n")))
              str = str.substring(0,str.length()-1);
             
            
             int idx = str.indexOf(" ",4);
             int pin = str.substring(4,idx).toInt();
             String _s=str.substring(idx+1);
    
          //  Debug("W" , pin , _s );
    
          //  BlynkParamAllocated pars(_s.length());
          //  pars.add(_s);
    
        
             BlynkParam pars(this->mem, 0, sizeof(this->mem));
          
              pars.add(_s);
              
             //Debug("PIN2" , pin , pars.asInt());
    
              VirtualElement *ele = Find(pin);
              if (ele!=NULL)
                ele->OnCloudWrite(pars);
              else
                Warn("pin not found " , pin);
                
         // pars.
           // VirtualReq req;
           // req.pin = pin;
           // GetVWriteHandler(pin)(req,pars);
            
          }
          if (str.startsWith(F("_vr "))) {
           
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
  
  int incomingByte = 0;
  String full_str;
  
  void fast_tick()
  {
     ///Debug("..");

    while (Serial.available() > 0 ) 
    {
      incomingByte = Serial.read();
     // Serial.flush();
      //String c = String((char)incomingByte);
      //Debug (incomingByte);
       
      if (incomingByte == '\n')
      {
        full_str+= '\0';
        Process(full_str);
        full_str="";
        Serial.println(F("ACK"));
         Serial.flush();

      }
      else
        full_str = full_str + (char )incomingByte;
     //
    }
  }
    
void tick()
  {
    fast_tick();
  
     for(int i=0;i<this->count;i++)
    {
        list[i]->tick();
    }
  }
} ;

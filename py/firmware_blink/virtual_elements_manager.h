/*
 * Created by marco cecchini
 *
 */

#include <SoftwareSerial.h>

#include <BlynkSimpleStream.h>
#include "config.h"
#include "virtual_elements.h"
#include "sensors.h"


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

   DistanceSensor *addDistance(int vpin,int TRIG_PIN,int ECHO_PIN) {
      DistanceSensor *sw = new DistanceSensor(vpin,TRIG_PIN,ECHO_PIN);
       Add(sw);
      return sw;
  }



  Var_Bool *addVarBool(int pin,bool startValue=false) {
       Var_Bool *sw = new Var_Bool(pin);
       Add(sw);
       sw->set(startValue);
      return sw;
  }

 Var_String *addVarString(int pin,const String& startValue="") {
      Var_String *sw = new Var_String(pin);
       Add(sw);
        sw->set(startValue);
      return sw;
  }

  Var_Real *addVarReal(int pin,float startValue=0) {
      Var_Real *sw = new Var_Real(pin);
       Add(sw);
        sw->set(startValue);
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

/*
   Created by marco cecchini

*/

#include "config.h"
#include "common.h"

#define LAB_EC_SENSOR_VPIN 140
#define LAB_EC_K_VPIN 141
#define LAB_EC_TEMPERATURE_VPIN 142

#define LAB_PH_SENSOR_VPIN 143
#define LAB_PH_VOLTAGE_VPIN 144
#define LAB_PH_REF_4_VPIN 145
#define LAB_PH_REF_6_VPIN 146
#define LAB_DISTANCE_VPIN 147

enum BridgMode
{
  READ=0,
  WRITE
};
class Var_Real_Bridge;
class Var_Real_Read: public Var_Real
{
    Var_Real_Bridge *bridge;
  public:
    Var_Real_Read(Var_Real_Bridge *bridge,int pin) : Var_Real(pin),bridge(bridge){
     }
    void OnCloudWrite(BlynkParam &param);
};

class Var_Real_Write: public Var_Real
{
    Var_Real_Bridge *bridge;
  public:
    Var_Real_Write(Var_Real_Bridge *bridge,int pin) : Var_Real(pin),bridge(bridge){
     }
   // void OnCloudWrite(BlynkParam &param);
};

class Var_Real_Bridge: public Var_Real
{
      BridgMode mode;
      Var_Real_Write *rwrite;
    public:
      Var_Real_Bridge(VirtualElementManager &manager_lab,BridgMode mode, int pin,int EPROM_ADDRESS=-1) : Var_Real(pin,EPROM_ADDRESS),mode(mode){
        if (mode == BridgMode::READ)
          manager_lab.Add( new Var_Real_Read(this,pin));
        else
        {
          rwrite =  new Var_Real_Write(this,pin);
           manager_lab.Add(rwrite);
        }
      }

     void OnCloudWrite(BlynkParam &param){
        Var_Real::OnCloudWrite(param);
      
        if (mode == BridgMode::WRITE){
            
           float val = param.asFloat();
           Debug("ON BRIDGE WRITE " , pin,val);
          rwrite->set(val);
        }
     }
     
      void _OnCloudWrite(BlynkParam &param){
         float val = param.asFloat();
         set(val);
         
    }
};

 void Var_Real_Read::OnCloudWrite(BlynkParam &param){
            bridge->_OnCloudWrite(param);
    }
// ==========================================================

class Lab
{
    VirtualElementManager &manager_lab;
  
    Var_Real *var_temperature;

    //ec
     Var_Real *var_k;
    Var_Real *var_ec;

  // ph
    Var_Real *var_ph;
    Var_Real *var_ph_voltage;
    Var_Real *var_ph_ref_4;
    Var_Real *var_ph_ref_6;
    Var_Real *var_distance;

  public:
  
    Lab(VirtualElementManager &manager,VirtualElementManager &manager_lab) : manager_lab(manager_lab)
    {
      // params
      
      var_k = new Var_Real_Bridge(manager_lab,WRITE,LAB_EC_K_VPIN);
      manager.Add(var_k);

      var_ph_ref_4 = new Var_Real_Bridge(manager_lab,WRITE,LAB_PH_REF_4_VPIN);
      manager.Add(var_ph_ref_4);

      var_ph_ref_6 = new Var_Real_Bridge(manager_lab,WRITE,LAB_PH_REF_6_VPIN);
      manager.Add(var_ph_ref_6);

      // outputs
      var_ec = new Var_Real_Bridge(manager_lab,READ,LAB_EC_SENSOR_VPIN);
      manager.Add(var_ec);
      
      var_temperature = new Var_Real_Bridge(manager_lab,READ,LAB_EC_TEMPERATURE_VPIN);
      manager.Add(var_temperature);

      var_ph = new Var_Real_Bridge(manager_lab,READ,LAB_PH_SENSOR_VPIN);
      manager.Add(var_ph);

      var_ph_voltage = new Var_Real_Bridge(manager_lab,READ,LAB_PH_VOLTAGE_VPIN);
      manager.Add(var_ph_voltage);
      
     var_distance = new Var_Real_Bridge(manager_lab,READ,LAB_DISTANCE_VPIN);
      manager.Add(var_distance);
    }

    void LogicFast() {
   
    }


    void Logic() {
      
    }

};

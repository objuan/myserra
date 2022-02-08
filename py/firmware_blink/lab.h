/*
   Created by marco cecchini

*/
#ifndef __LAB
#define __LAB

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
#define LAB_WEIGHT_1_VPIN 149

enum BridgMode: byte
{
  READ=0,
  WRITE,
  READ_WRITE
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
/*
class Var_Real_Write: public Var_Real
{
    Var_Real_Bridge *bridge;
  public:
    Var_Real_Write(Var_Real_Bridge *bridge,int pin) : Var_Real(pin),bridge(bridge){
     }
   // void OnCloudWrite(BlynkParam &param);
};
*/

// ===============================================


class Var_Real_Bridge: public Var_Real
{
      BridgMode mode;
      Var_Real *rwrite;
    public:
      Var_Real_Bridge(VirtualElementManager &manager_lab,BridgMode mode, int pin,int EPROM_ADDRESS=-1) : Var_Real(pin,EPROM_ADDRESS),mode(mode){
        if (mode == BridgMode::READ)
          manager_lab.Add( new Var_Real_Read(this,pin));
        else
        {
          rwrite =  new Var_Real(this,pin);
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
          //Debug("ON BRIDGE READ " , pin,val);
         set(val);
         
    }
};

 void Var_Real_Read::OnCloudWrite(BlynkParam &param){
            bridge->_OnCloudWrite(param);
    }
// ==========================================================

class Lab
{
  
  public:
  
    Lab(VirtualElementManager &manager,VirtualElementManager &manager_lab)
    {
       
      manager.Add(new Var_Real_Bridge(manager_lab,WRITE,LAB_EC_K_VPIN));
      manager.Add(new Var_Real_Bridge(manager_lab,WRITE,LAB_PH_REF_4_VPIN));
      manager.Add( new Var_Real_Bridge(manager_lab,WRITE,LAB_PH_REF_6_VPIN));

      // outputs
      manager.Add( new Var_Real_Bridge(manager_lab,READ,LAB_EC_SENSOR_VPIN));

      manager.Add(new Var_Real_Bridge(manager_lab,READ,LAB_EC_TEMPERATURE_VPIN));

      manager.Add(new Var_Real_Bridge(manager_lab,READ,LAB_PH_SENSOR_VPIN));

      manager.Add(new Var_Real_Bridge(manager_lab,READ,LAB_PH_VOLTAGE_VPIN));
 
      manager.Add(new Var_Real_Bridge(manager_lab,READ,LAB_DISTANCE_VPIN));

      manager.Add(new Var_Real_Bridge(manager_lab,READ,LAB_WEIGHT_1_VPIN));
    }

};

#endif

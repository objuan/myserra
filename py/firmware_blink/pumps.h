/*
 * Created by marco cecchini
 *
 */

#include "config.h"
#include "common.h"
#include "lab.h"
// constants 

#define LAB_SWITCH_TANK_1_IN_VPIN  150 
#define LAB_SWITCH_TANK_1_OUT_VPIN  151

#define LAB_SWITCH_EC_IN_1_VPIN  152  // eletrovalvola ec in 1
#define LAB_SWITCH_EC_IN_2_VPIN  153  // eletrovalvola ec in 1
#define LAB_SWITCH_PH_IN_VPIN  154  //
#define LAB_SWITCH_MIX_UP_VPIN  155  //
#define LAB_SWITCH_WATER_IN_VPIN  156  //


class Bool_Proxy;
class Bool_Read: public Var_Bool
{
    Bool_Proxy *bridge;
  public:
    Bool_Read(Bool_Proxy *bridge,int pin) : Var_Bool(pin),bridge(bridge){
     }
    void OnCloudWrite(BlynkParam &param);
};

class Bool_Write: public Var_Bool
{
    Bool_Proxy *bridge;
  public:
    Bool_Write(Bool_Proxy *bridge,int pin) : Var_Bool(pin),bridge(bridge){
     }
};
class Bool_ReadWrite: public Bool_Write
{
    Bool_Proxy *bridge;
  public:
    Bool_ReadWrite(Bool_Proxy *bridge,int pin) : Bool_Write(bridge,pin),bridge(bridge){
     }
     void OnCloudWrite(BlynkParam &param);
};
    
class Bool_Proxy : public Var_Bool
{
public:

    BridgMode mode;
    Bool_Write *rwrite;
    public:
      Bool_Proxy(VirtualElementManager &manager_lab,BridgMode mode, int pin,int EPROM_ADDRESS=-1) : Var_Bool(pin,EPROM_ADDRESS),mode(mode){
        if (mode == BridgMode::READ )
          manager_lab.Add( new Bool_Read(this,pin));
        if (mode == BridgMode::WRITE  )
        {
           rwrite =  new Bool_Write(this,pin);
           manager_lab.Add(rwrite);
        }
         if (mode == BridgMode::READ_WRITE )
        {
           rwrite =  new Bool_ReadWrite(this,pin);
           manager_lab.Add(rwrite);
        }
      }

     void OnCloudWrite(BlynkParam &param){
        Var_Bool::OnCloudWrite(param);
      
        if (mode == BridgMode::WRITE || mode ==  BridgMode::READ_WRITE ){
            
           int val = param.asInt();
           Debug("ON BRIDGE BOOL " , pin,val);
           rwrite->set(val);
        }
     }
     
      void _OnCloudWrite(BlynkParam &param){
         int val = param.asInt();
         set(val);
         
    }
};

void Bool_Read::OnCloudWrite(BlynkParam &param){
   bridge->_OnCloudWrite(param);
 }
 void Bool_ReadWrite::OnCloudWrite(BlynkParam &param){
   bridge->_OnCloudWrite(param);
 }
    
class Pumps
{
   VirtualElementManager &manager_lab;
  
  public:
     Pumps(VirtualElementManager &manager,VirtualElementManager &manager_lab) : manager_lab(manager_lab)
    {
      // params
      
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_TANK_1_IN_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_TANK_1_OUT_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_EC_IN_1_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_EC_IN_2_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_PH_IN_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_MIX_UP_VPIN));
      manager.Add( new Bool_Proxy(manager_lab,READ_WRITE,LAB_SWITCH_WATER_IN_VPIN));

    }

    void Logic()
    {
    }
    
};

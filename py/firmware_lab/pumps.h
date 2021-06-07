/*
 * Created by marco cecchini
 *
 */

#include "config.h"
#include "common.h"
// constants 

#define LAB_SWITCH_TANK_1_IN_VPIN  150 
#define LAB_SWITCH_TANK_1_OUT_VPIN  151

#define LAB_SWITCH_EC_IN_1_VPIN  152  // eletrovalvola ec in 1
#define LAB_SWITCH_EC_IN_2_VPIN  153  // eletrovalvola ec in 1
#define LAB_SWITCH_PH_IN_VPIN  154  //
#define LAB_SWITCH_MIX_UP_VPIN  155  //
#define LAB_SWITCH_WATER_IN_VPIN  156  //




class Pumps
{
  
  public:
    Pumps(VirtualElementManager &manager){
      
      manager.addSolenoidValve(LAB_SWITCH_TANK_1_IN_VPIN,  LAB_SWITCH_TANK_1_IN_PIN);
      manager.addSolenoidValve(LAB_SWITCH_TANK_1_OUT_VPIN,  LAB_SWITCH_TANK_1_OUT_PIN);
      manager.addSolenoidValve(LAB_SWITCH_EC_IN_1_VPIN,  LAB_SWITCH_EC_IN_1_PIN);
      manager.addSolenoidValve(LAB_SWITCH_EC_IN_2_VPIN,  LAB_SWITCH_EC_IN_2_PIN);
      manager.addSolenoidValve(LAB_SWITCH_PH_IN_VPIN,  LAB_SWITCH_PH_IN_PIN);
      manager.addSolenoidValve(LAB_SWITCH_MIX_UP_VPIN,  LAB_SWITCH_MIX_UP_PIN);
      manager.addSolenoidValve(LAB_SWITCH_WATER_IN_VPIN,  LAB_SWITCH_WATER_IN_PIN);
      
   
    }

    void Logic()
    {
 
   
    }
    
};

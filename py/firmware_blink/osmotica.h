/*
 * Created by marco cecchini
 *
 */

#include "config.h"
#include "common.h"

// constants 

#define TOP_SWITCH_VPIN  4  // interruttore acqua piena
#define FILL_SWITCH_VPIN  5  // interruttore inizzio acqua piena
#define DANGER_SWITCH_VPIN  6  // interruttore acqua bassa per pompa
  
// eletrovalvola ingresso acqua
#define WATER_IN_SOLENOID_VPIN 7   // eletrovalvola acqua injson ingresso 
#define WATER_OUT_RELE_VPIN 9    //   rele pompa di uscita

// virtua lvars
#define WATER_STATE_VPIN 101  // 
#define WATER_ENABLE_VPIN 102  // 

#define STATE_IDDLE "IDDLE"
#define STATE_FILL "FILLING"
#define STATE_DISABLED "DISABLED"


/*
 *  CONNECT DIAGRAM
 *  
 *  TOP   1 -> water up 
 *  
 *  
 *  FILL  1 -> water down 
 *  
 *  
 *  DANGER 1 -> water down 
 * 
 * 
 */
class Osmotica
{
  Switch *top_state;
  Switch *fill_state;
  Switch *danger_state;

  SolenoidValve *in_water ;
  Pump *pump;
 
  Var_Bool *water_enable;
  Var_String *in_water_state;
  
  public:
    Osmotica(VirtualElementManager &manager){
      
        top_state=  manager.addSwitch(TOP_SWITCH_VPIN,        OSMOTICA_TOP_SWITCH_PIN);
        fill_state =  manager.addSwitch(FILL_SWITCH_VPIN,     OSMOTICA_FILL_SWITCH_PIN);
        danger_state = manager.addSwitch(DANGER_SWITCH_VPIN,  OSMOTICA_DANGER_SWITCH_PIN);
      
        in_water =  manager.addSolenoidValve(WATER_IN_SOLENOID_VPIN,  OSMOTICA_WATER_IN_SOLENOID_PIN);
        pump =  manager.addPump(WATER_OUT_RELE_VPIN,                  OSMOTICA_WATER_OUT_RELE_PIN);
      
        water_enable = manager.addVarBool(WATER_ENABLE_VPIN,true) ;
        in_water_state= manager.addVarString(WATER_STATE_VPIN,STATE_IDDLE) ;

    }
    
    bool isFull()
    {
      return top_state->get() ==true;
    }
    
    bool needWater()
    {
      return fill_state->get() == true;
    }

    void Logic()
    {

      if (water_enable->get())
      {
  
        if (in_water_state->get() == STATE_IDDLE)
        {
            if (needWater())
            {
               in_water_state->set(STATE_FILL);
               in_water->Open() ; 
                 
               Log(F("STATE_WATER = FILLING"));
            }
         }
         else  if (in_water_state->get() == STATE_FILL)
         {
            if (isFull())
            {
                 in_water_state->set(STATE_IDDLE);
                 in_water->Close() ;
               
                Log(F("STATE_WATER = IDDLE"));
            }
          }
          else  if (in_water_state->get() == STATE_DISABLED)
          { 
              in_water_state->set(STATE_IDDLE);
              in_water->Close();  
          }
     }
     else if (in_water_state->get() != STATE_DISABLED)
     {
        in_water_state->set(STATE_DISABLED);
        in_water->Close() ;
     }
     
    }
    
};

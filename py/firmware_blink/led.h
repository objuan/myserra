/*
 * Created by marco cecchini
 *
 */


#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
// constants 

#define LED_SWITCH_VPIN  135  // eletrovalvola acqua perime7rale
#define LED_SCHEDULING_VPIN  136  // json scheduling
#define LED_ENABLE_VPIN 137  // 

class Var_LED_SCHEDULING : public Var_SCHEDULING
{
  public:
     Var_LED_SCHEDULING() : Var_SCHEDULING(LED_SCHEDULING_VPIN,EPROM_LED_SCHEDULING_DA,EPROM_LED_SCHEDULING_A){
     }
};


class Leds
{
  SolenoidValve *ledSwitch ;
  Var_SCHEDULING *scheduler;
  Var_Bool *enable;
  bool isEnabled=false;
      
  public:
    Leds(VirtualElementManager &manager){
      
        ledSwitch =  manager.addSolenoidValve(LED_SWITCH_VPIN,  LEDS_SOLENOID_PIN);
      
        enable = manager.addVarBool(LED_ENABLE_VPIN,true,EPROM_LED_ENABLE) ;
        scheduler= (Var_LED_SCHEDULING*)manager.Add(new Var_LED_SCHEDULING()) ;

  #ifndef MEGA
        scheduler-> time_da = 21600; // 6
        scheduler->time_a = 72000; // 20
#endif
    }
    
  
    void Logic()
    {
      if (enable->get())
      {   
      
          DateTime now = currentDateTime();
          TimeSpan dayTime = TimeSpan(0,now.hour(), now.minute(),0);

          bool _isEnabled =  ( dayTime.totalseconds() >= scheduler->time_da.totalseconds ()
                        && dayTime.totalseconds() < scheduler->time_a.totalseconds ());

  //Debug("k",dayTime.totalseconds()," ",scheduler->time_da.totalseconds ()," ",scheduler->time_a.totalseconds ());
  
          if (_isEnabled!=isEnabled)
          {
            isEnabled=_isEnabled;

              if (isEnabled)
             {
                Debug(F("ACTIVE"));
                ledSwitch->Open();
              }
              else
              {
                Debug(F("DISABLED"));
                ledSwitch->Close();
              }
          }

      }
      
      else
      {
          if (isEnabled)
          {
              isEnabled=false;
                  Debug(F("DISABLED"));
                  ledSwitch->Close();
          }
      }
    }
};

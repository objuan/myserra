/*
 * Created by marco cecchini
 *
 */


#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
// constants 

#define PERIMETRALE_SWITCH_VPIN  130  // eletrovalvola acqua perime7rale
#define PERIMETRALE_SCHEDULING_VPIN  131  // json scheduling
#define PERIMETRALE_ENABLE_VPIN 132  // 


class Var_PERIMETRALE_SCHEDULING : public Var_SCHEDULING
{
  public:
     Var_PERIMETRALE_SCHEDULING() : Var_SCHEDULING(PERIMETRALE_SCHEDULING_VPIN,EPROM_GIARDINO_SCHEDULING_DA,EPROM_GIARDINO_SCHEDULING_A){
     }
};


class Giardino
{
  SolenoidValve *perimetrale ;
  Var_SCHEDULING *scheduler;
  Var_Bool *perimetrale_enable;
  bool isEnabled=false;
  
  public:
    Giardino(VirtualElementManager &manager){
      
        perimetrale =  manager.addSolenoidValve(PERIMETRALE_SWITCH_VPIN,  PERIMETRALE_SOLENOID_PIN);
      
        perimetrale_enable = manager.addVarBool(PERIMETRALE_ENABLE_VPIN,true,EPROM_GIARDINO_PERIMETRALE_ENABLE) ;
        scheduler= (Var_PERIMETRALE_SCHEDULING*) manager.Add(new Var_PERIMETRALE_SCHEDULING()) ;

         #ifndef MEGA
        scheduler-> time_da = 72000; // 6
        scheduler->time_a = 72000 + 60*15; // 20
#endif
    }
    
  
    void Logic()
    {
 
     if (perimetrale_enable->get())
      {
          DateTime now = currentDateTime();
          TimeSpan dayTime = TimeSpan(0,now.hour(), now.minute(),0);

          bool _isEnabled =  ( dayTime.totalseconds() >= scheduler->time_da.totalseconds ()
                        && dayTime.totalseconds() < scheduler->time_a.totalseconds ());

          if (_isEnabled!=isEnabled)
          {
            isEnabled=_isEnabled;

              if (isEnabled)
             {
                Debug(F("ACTIVE"));
                perimetrale->Open();
              }
              else
              {
                Debug(F("DISABLED"));
                perimetrale->Close();
              }
          }

      }
      
      else
      {
          if (isEnabled)
          {
              isEnabled=false;
                  Debug(F("DISABLED"));
                  perimetrale->Close();
          }
      }
    }
    
};

/*
 * Created by marco cecchini
 *
 */


#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
// constants 

#define PERIMETRALE_SWITCH_VPIN  130  // eletrovalvola acqua perime7rale
#define PERIMETRALE_ENABLE_VPIN  132  // eletrovalvola acqua perime7rale
#define PERIMETRALE_SCHEDULING_VPIN  131  // json scheduling

#define ERBA_SWITCH_VPIN  137  // eletrovalvola acqua perime7rale
#define ERBA_ENABLE_VPIN  134  // eletrovalvola acqua perime7rale
#define ERBA_SCHEDULING_VPIN  133  // json scheduling

class Var_PERIMETRALE_SCHEDULING : public Var_SCHEDULING
{
  public:
     Var_PERIMETRALE_SCHEDULING() : Var_SCHEDULING(PERIMETRALE_SCHEDULING_VPIN,EPROM_GIARDINO_SCHEDULING_DA,EPROM_GIARDINO_SCHEDULING_A){
     }
};
class Var_ERBA_SCHEDULING : public Var_SCHEDULING
{
  public:
     Var_ERBA_SCHEDULING() : Var_SCHEDULING(ERBA_SCHEDULING_VPIN,EPROM_ERBA_SCHEDULING_DA,EPROM_ERBA_SCHEDULING_A){
     }
};


class Giardino
{
  SolenoidValve *perimetrale ;
  SolenoidValve *erba ;
  
  Var_SCHEDULING *scheduler_pem;
  Var_SCHEDULING *scheduler_erba;
  
  Var_Bool *perimetrale_enable;
  Var_Bool *erba_enable;
  
  bool isEnabled[2];
  
  public:
    Giardino(VirtualElementManager &manager){
      
        perimetrale =  manager.addSolenoidValve(PERIMETRALE_SWITCH_VPIN,  GIARDINO_PERIMETRALE_SOLENOID_PIN);
        perimetrale_enable = manager.addVarBool(PERIMETRALE_ENABLE_VPIN,true,EPROM_GIARDINO_PERIMETRALE_ENABLE) ;
        
        erba =  manager.addSolenoidValve(ERBA_SWITCH_VPIN,  GIARDINO_ERBA_SOLENOID_PIN);
        erba_enable = manager.addVarBool(ERBA_ENABLE_VPIN,true,EPROM_ERBA_ENABLE) ;
       
        scheduler_pem= (Var_PERIMETRALE_SCHEDULING*) manager.Add(new Var_PERIMETRALE_SCHEDULING()) ;
        scheduler_erba= (Var_ERBA_SCHEDULING*) manager.Add(new Var_ERBA_SCHEDULING()) ;

        isEnabled[0]=isEnabled[1]=false;

#ifndef MEGA
        scheduler_pem-> time_da = 72000; // 6
        scheduler_pem->time_a = 72000 + 60*15; // 20
#endif
    }
    
  
    void Logic()
    {
        Check(scheduler_pem,perimetrale,perimetrale_enable,0);
        Check(scheduler_erba,erba,erba_enable,1);

    }

    Check(Var_SCHEDULING *scheduler,SolenoidValve *valve,Var_Bool *var_enable,int index)
    {
       if (var_enable->get())
      {
          DateTime now = currentDateTime();
          TimeSpan dayTime = TimeSpan(0,now.hour(), now.minute(),0);

          bool _isEnabled =  ( dayTime.totalseconds() >= scheduler->time_da.totalseconds ()
                        && dayTime.totalseconds() < scheduler->time_a.totalseconds ());

          if (_isEnabled!=isEnabled[index])
          {
             isEnabled[index]=_isEnabled;

              if (isEnabled[index])
             {
                Debug(F("ACTIVE"));
                valve->Open();
              }
              else
              {
                Debug(F("DISABLED"));
                valve->Close();
              }
          }

      }
      else
      {
          if (isEnabled[index])
          {
                isEnabled[index]=false;
                Debug(F("DISABLED"));
                valve->Close();
          }
      }
    }
    
};

/*
 * Created by marco cecchini
 *
 */

#include <BlynkSimpleStream.h>
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

  public:
    Giardino(VirtualElementManager &manager){
      
        perimetrale =  manager.addSolenoidValve(PERIMETRALE_SWITCH_VPIN,  PERIMETRALE_SOLENOID_PIN);
      
        perimetrale_enable = manager.addVarBool(PERIMETRALE_ENABLE_VPIN,true,EPROM_GIARDINO_PERIMETRALE_ENABLE) ;
        scheduler= manager.Add(new Var_PERIMETRALE_SCHEDULING()) ;
    }
    
  
    void Logic()
    {
 
      if (perimetrale_enable->get())
      {
          DateTime now = currentDateTime();
        
          TimeSpan dayTime = TimeSpan(0,now.hour(), now.minute(),0);

          if ( dayTime.totalseconds() >= scheduler->time_da.totalseconds ()
          && dayTime.totalseconds() < scheduler->time_a.totalseconds ())
          {
            Debug("ACTIVE");
            perimetrale->Open();
          }
          else
          {
            Debug("DISABLED");
            perimetrale->Close();
          }
       
      }
    }
    
};

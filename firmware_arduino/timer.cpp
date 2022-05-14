/*
 * Created by marco cecchini
 *
 */
#include <EEPROM.h>
#include "config.h"

#include "Timer.h"

char* Switch::sw_names[] = {"DISABLED","FORCED","TIMER"};

int getSeconds(DateTime dt)
{ 
  int ss= dt.hour() * (60*60) + dt.minute () * 60 +   dt.second ();
 // Serial.println(mm);
  return ss;
}


int getMinutes(DateTime dt)
{ 
  int mm= dt.hour() * 60 + dt.minute ();
 // Serial.println(mm);
  return mm;
}

bool Timer::isMinutesInside(const char *name,const DateTime &now,const DateTime &from, const  DateTime &to)
{
   // DateTime now = giardino_rtc->now();
    bool ok = getMinutes(now) >= getMinutes(from)   &&   getMinutes(now) <= getMinutes(to) ;
/*
 #ifdef DEBUG_MODE
    Serial.print(name);

    
    Serial.print(" F: ");
    Serial.print(from.hour(), DEC);
    Serial.print(':');
    Serial.print(from.minute(), DEC);
    Serial.print(':');
    Serial.print(from.second(), DEC);

    Serial.print(" T: ");
    Serial.print(to.hour(), DEC);
    Serial.print(':');
    Serial.print(to.minute(), DEC);
    Serial.print(':');
    Serial.print(to.second(), DEC);
    
    Serial.print(" =");
    Serial.println(ok ? "ON":"OFF");
 #endif
 */
    return ok;
}

  void Timer::startup()
  {
    /*
      if (false)
      {
        String last = read_String(epromAddress,16);
        String openTick = read_String(epromAddress+50,10);
       
        Serial.print(name);
        Serial.print(" Last.. ");
        Serial.println(last.c_str());
        Serial.print(" Tickes .. ");
        Serial.println(openTick.c_str());
 
      }
      */
  }
  
  
 bool Timer::isOn(const DateTime &now){
        bool on=false;
        if (mode == TimerMode::ON)
        {
          on = isMinutesInside(name.c_str(),now,dt_start,dt_end);
        }
         if (mode == TimerMode::STEP_INTERVAL)
        {
           on = isMinutesInside(name.c_str(),now,dt_start,dt_end);
           if (on)
           {
              if (period_time_secs <  period_time_secs)
              {
                  
              }
              period_time_secs = getSeconds(now) - getSeconds(dt_start);
              int q = (period_time_secs) / (period_on_secs+period_off_secs);
              int period_relative = period_time_secs - q * (period_on_secs+period_off_secs);
              if (period_relative > period_on_secs)
                on=false;
              /*
              Serial.print("PERIOD, TOTAL= ");
              Serial.print(period_time_secs);
              Serial.print(" Q:" );
              Serial.print(q);
               Serial.print(" Relative:" );
              Serial.print(period_relative);
             Serial.print(" ON:" );
              Serial.print(on);
              Serial.println("");
              */
              
           }
           else
              period_time_secs=0;
        }

        if (on)
        {
            /*String myString; 
            myString = name ;
            myString.concat(" ");
            myString.concat(str_DateTime(now));
      */
            openTick++;
          //  writeString(epromAddress,str_DateTime(now));
          //  writeString(epromAddress+50,String(openTick));
        }
        
        //bool on = isMinutesInside("PIANTE",now,piante_from,piante_to);
        return on;
     }


     

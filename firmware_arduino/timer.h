
enum TimerMode
{
  ON,
  STEP_INTERVAL
};

class Timer
{
 public:
  int epromAddress;
  DateTime lastOpen;
  int openTick=0;
  String name;

  DateTime dt_start;
  DateTime dt_end;
  TimerMode mode;
  int period_on_secs;
  int period_off_secs;

  int period_time_secs;
  
  
 public:
     Timer(const char*name,int epromAddress)
     {
        this->name=name;
        this->epromAddress=epromAddress;
        mode = TimerMode::ON;
        period_on_secs=100;
        period_off_secs=100;
        period_time_secs=0;
        startup();
     }

     void startup();

    bool isMinutesInside(const char *name,const DateTime &now,const DateTime &from, const  DateTime &to);

     void setInterval(const DateTime &dt_start, const  DateTime &dt_end)
     {
        this->dt_start=dt_start;
        this->dt_end=dt_end;
     }
     
     void setPeriod(int on_secs,int off_secs)
     {
       this->period_on_secs=on_secs;
       this->period_off_secs=off_secs;
     }
     
     void setMode(TimerMode mode)
     {
        this->mode=mode;
     }
     

     bool isOn(const DateTime &now);
     
};

enum SwitchMode
{
    OFF=0,
    OPEN=1,
    TIMER=2
};


class Switch
{
  int pin;
  int vpin;
 // bool force;
  int lastValue;
  int value;
  Timer *timer;
  SwitchMode mode;

  static char* sw_names[];
  
  public:
    Switch(int pin,int vpin,Timer* timer){
      this->pin=pin;this->vpin=vpin;this->timer=timer;lastValue=-1;value=-1;
      mode = TIMER;
    }
    void setMode(SwitchMode mode){
      this->mode=mode;
    }
    void tick(const DateTime &now)
    {
      // Serial.println(str_DateTime(now).c_str());

       if (mode == SwitchMode::OFF)
          value=0;
       else value =  ( mode == SwitchMode::OPEN || timer->isOn(now) )?  1 : 0;

       virtualWrite(vpin, (value==1) ?  F("ON"):F("OFF")," ( ", sw_names[mode], ")");
       
       if (value != lastValue)
       {
            lastValue=value;
            digitalWrite(pin, (value==1)  ? RELE_ON : RELE_OFF);

            VirtualLog("[",str_DateTime(now).c_str(),"] ", timer->name,":",  (value==1)  ?F("OK"):F("OFF")," ( ", sw_names[mode], ")" );
       }
    }
};

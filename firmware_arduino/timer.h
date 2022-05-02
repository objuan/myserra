
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

class Switch
{
  int pin;
  int vpin;
  bool force;
  int lastValue;
  int value;
  Timer *timer;
  public:
    Switch(int pin,int vpin,Timer* timer){
      this->pin=pin;this->vpin=vpin;force=false;this->timer=timer;lastValue=-1;value=-1;
    }
    void forceOn(bool on){
      this->force=on;
    }
    void tick(const DateTime &now)
    {
      // Serial.println(str_DateTime(now).c_str());
       
       value =  ( force || timer->isOn(now) )?  1 : 0;

       virtualWrite(vpin, (value==1) ?  F("ON"):F("OFF"));
       
       if (value != lastValue)
       {
            lastValue=value;
            digitalWrite(pin, (value==1)  ? RELE_ON : RELE_OFF);

            VirtualLog("[",str_DateTime(now).c_str(),"] ", timer->name,":",  (value==1)  ?F("OK"):F("OFF")," " );
       }
    }
};

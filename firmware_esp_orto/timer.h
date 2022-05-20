

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

String str_DateTime(const DateTime &now);

enum TimerMode
{
  ON,
  STEP_INTERVAL
};

class Timer
{
 public:
 // int epromAddress;
  DateTime lastOpen;
  int openTick=0;
  String name;

  long dt_start;
  long dt_end;
 // DateTime dt_start;
  //DateTime dt_end;
  TimerMode mode;
  int period_on_secs;
  int period_off_secs;

  int period_time_secs;
  
  
 public:
     Timer(const char*name)
     {
        this->name=name;
        //this->epromAddress=epromAddress;
        mode = TimerMode::ON;
        period_on_secs=100;
        period_off_secs=100;
        period_time_secs=0;
        startup();
     }

     void startup();

    bool isMinutesInside(const char *name,const DateTime &now,long from, long to);
/*
     void setInterval(const DateTime &dt_start, const  DateTime &dt_end)
     {
        this->dt_start=dt_start;
        this->dt_end=dt_end;
     }
     */
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

     String toString(){
         int hh = dt_start / 3600;
         int mm = (dt_start-hh*3600)  / 60;
         int ss = (dt_start - hh*3600 - mm*60) ;
         
        DateTime s (0,0,0,hh,mm,ss);

         hh = dt_end / 3600;
          mm = (dt_end-hh*3600)  / 60;
          ss = (dt_end - hh*3600 - mm*60) ;
         
        DateTime e (0,0,0,hh,mm,ss);
        //Serial.println(dt_start);
        return "S:"+ String(s.hour())+":"+String(s.minute())+":"+String(s.second())+" E:"+ String(e.hour())+":"+String(e.minute())+":"+String(e.second());
     }
};

enum SwitchMode : int
{
    OFF=0,
    OPEN=1,
    TIMER=2
};


class Switch
{
  bool localTimer;
  int pin;
  int vpin;
 // bool force;
  int lastValue;
  int value;
  Timer *timer;
  SwitchMode mode;
  SwitchMode oldMode;

  static char* sw_names[];
  
  public:
    Switch(const char *name,int pin,int vpin){
      timer = new Timer(name);
      localTimer=true;
      this->pin=pin;this->vpin=vpin;lastValue=-1;value=-1;oldMode= OFF;
      mode = TIMER;

      pinMode(pin, OUTPUT);
      digitalWrite(pin, RELE_OFF);
    }
    
    Switch(int pin,int vpin,Timer* timer){
      localTimer=false;
      this->pin=pin;this->vpin=vpin;this->timer=timer;lastValue=-1;value=-1;oldMode= OFF;
      mode = TIMER;
    }
    ~Switch(){
        if (localTimer) delete timer;
    }

    Timer *getTimer(){ return timer; }
    
    void setMode(int mode){
    
      this->mode=(SwitchMode)mode;
    }
    void tick(const DateTime &now);
};

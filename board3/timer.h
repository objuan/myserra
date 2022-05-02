
enum TimerMode
{
  ON,
  STEP_INTERVAL
};

class Timer
{
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

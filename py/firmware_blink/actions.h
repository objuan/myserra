
#include "common.h"
#include "sensors.h"

class ActionManager;

class Action
{
  public:
    String name;
    ActionManager *manager;
    Action(const String &name) : name(name){}

    void Destroy();
    
    virtual void tick(){
    }
};

class Action_GetWater : public Action
{
  public:
    WaterFlowSensor *flowSensor;
    SolenoidValve *out_switch;
    float liters;
    
    Action_GetWater(SolenoidValve *out_switch,WaterFlowSensor *flowSensor,int liters):Action("GET WATER")
          ,flowSensor(flowSensor), out_switch(out_switch),liters(liters) 
    {
      flowSensor->Begin();
      out_switch->Open();
    }

    void tick(){
      Debug("FILLING: ", flowSensor->totalLiters()," Liters" );
      if (flowSensor->totalLiters() >= liters)
      {
          out_switch->Close();
          Destroy();
      }
      
    }
};


class Action_FillTank : public Action
{
  public:
    Vasca *tank;
    SolenoidValve *in_switch;
    float liters;
    
    Action_FillTank(Vasca *tank,SolenoidValve *in_switch,int liters):Action("FILL TANK"){}

    void Execute(){
      
    }
};

#define ACTION_COUNT 20
class ActionManager 
{
    Action* list[ACTION_COUNT];
    int count=0;
    
  public:
    ActionManager(){
         for(int i=0;i<ACTION_COUNT;i++) list[i]=NULL;
    }

    int IndexOf(Action *a){
        for(int i=0;i<ACTION_COUNT;i++)
          if (list[i] == a) return i;
         return -1;
   }
   
    void Add(Action *a){
        list[count++] = a;
        a->manager=this;
        Log("ACTION ADD " , a->name);
   }
    
    void Remove(Action *a){
        int i = IndexOf(a);
        if (i!=-1)
        {
             for(int i=i;i<ACTION_COUNT;i++)
                  list[i] == list[i+1] ;
              count--;
              list[count]=NULL;
              Log("ACTION REMOVE " , a->name);
              delete a;
        }
   }

   void  tick()
  {
     for(int i=0;i<count;i++)
      list[i]->tick();
  }
  
  
};

void Action::Destroy(){
      manager->Remove(this);
    }

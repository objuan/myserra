/*
 * Created by marco cecchini
 *
 */

#include "config.h"


// constants 

// SWITCHS
#ifdef MEGA
  #define DISTANCE_TRIG  53  //
  #define DISTANCE_ECHO  51  // 
#else
  #define DISTANCE_TRIG  12  //
  #define DISTANCE_ECHO  13  // 
#endif

#define DISTANCE_VIRTUAL_PIN  112  //
#define WATER_VOLUME_LITERS_PIN 114   // litri contenuti
#define DISTANCE_RESET_PIN 115   // litri contenuti
#define SENSOR_HEIGHT 116   // litri contenuti
    
class Vasca
{
  DistanceSensor *water_distance;
  Var_Real *water_liters;
  Var_Real *sensor_height;
  
  Var_Bool *distance_reset;

  movingAvg distanceAvg;
    
  float widht;
  float height;
  //float sensorHeight;
  int EPROM_sensorHeight_address=0;
  
  public:
    // misure in centimetri
    Vasca(VirtualElementManager &manager,float widht,float height, int EPROM_sensorHeight_address)
    :widht(widht),height(height),EPROM_sensorHeight_address(EPROM_sensorHeight_address),distanceAvg(3)  {
      
        water_distance=  manager.addDistance(DISTANCE_VIRTUAL_PIN,DISTANCE_TRIG,DISTANCE_ECHO);
        water_liters = manager.addVarReal(WATER_VOLUME_LITERS_PIN,0) ;
        sensor_height = manager.addVarReal(SENSOR_HEIGHT,0) ;         
        distance_reset = manager.addVarBool(DISTANCE_RESET_PIN,false) ;

        Init();
    }

    void Init()
    {
        float s=0;
        EEPROM.get(EPROM_sensorHeight_address,s);
        sensor_height->set(s);
        Log("Distance sensor load " , sensor_height->get());
    }
    
    
    void Logic()
    {
      if (distance_reset->get() )
      {
          sensor_height->set(water_distance->get());
          Log("Distance sensor reset at " , sensor_height->get());
          distance_reset->set(false);
          // save ti EPROM
          EEPROM.put(this->EPROM_sensorHeight_address, sensor_height->get());
      }
      float dist = distanceAvg.Add(water_distance->get());
      
      // clacolo il volume in litri dell'acqua
      float waterHeight = sensor_height->get() - dist;
        
      float cc = (widht * height * waterHeight) / 1000.0;

      water_liters->set(cc);
}
    
};


#ifndef Config_
#define Config_

#define MEGA
#define DEBUG_MODE
#define MAX_RECEIVE_BUFFER 128

// ARDUINO UNO 


#ifdef MEGA

#define LAB_SERIAL_RX 10 // RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53,
#define LAB_SERIAL_TX 11


  #define LAB_PH_SENSOR_PIN A15
  #define LAB_EC_SENSOR_PIN A14
  #define LAB_TEMPERATURE_PIN 6
  #define LAB_RANGE_TRIGGER_PIN 4
  #define LAB_RANGE_ECHO_PIN 5
  
  
  #define LAB_SWITCH_TANK_1_IN_PIN  27
  #define LAB_SWITCH_TANK_1_OUT_PIN  28
  
  #define LAB_SWITCH_EC_IN_1_PIN  22
  #define LAB_SWITCH_EC_IN_2_PIN  29
  #define LAB_SWITCH_PH_IN_PIN  24
  #define LAB_SWITCH_MIX_UP_PIN  25
  #define LAB_SWITCH_WATER_IN_PIN  26

  // MEMORY
#define EPROM_LAB_EC_K 0 // 4
#define EPROM_LAB_PH_REF_4 4 // 4
#define EPROM_LAB_PH_REF_6 8 // 4

#else
  // MINI PRO PINS

  #define LAB_SERIAL_RX 3 
#define LAB_SERIAL_TX 4
  

  #define LAB_PH_SENSOR_PIN A0
  #define LAB_EC_SENSOR_PIN A1
  #define LAB_TEMPERATURE_PIN 6
  #define LAB_RANGE_TRIGGER_PIN 2
  #define LAB_RANGE_ECHO_PIN 5
  
  
  #define LAB_SWITCH_TANK_1_IN_PIN  7
  #define LAB_SWITCH_TANK_1_OUT_PIN  8
  
  #define LAB_SWITCH_EC_IN_1_PIN  9
  #define LAB_SWITCH_EC_IN_2_PIN  10
  #define LAB_SWITCH_PH_IN_PIN  11
  #define LAB_SWITCH_MIX_UP_PIN  12
  #define LAB_SWITCH_WATER_IN_PIN  13 

  // MEMORY
#define EPROM_LAB_EC_K 0 // 4
#define EPROM_LAB_PH_REF_4 4 // 4
#define EPROM_LAB_PH_REF_6 8 // 4
#endif





#endif

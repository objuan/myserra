
#ifndef Config_
#define Config_

#define DEBUG_MODE
#ifdef MEGA
#define MAX_RECEIVE_BUFFER 128
#else
#define MAX_RECEIVE_BUFFER 64
#endif

// SWITCHS
#ifdef MEGA
  // OSMOTICA
  #define OSMOTICA_TOP_SWITCH_PIN  53  // interruttore acqua piena
  #define OSMOTICA_FILL_SWITCH_PIN  51  // interruttore inizzio acqua piena
  #define OSMOTICA_DANGER_SWITCH_PIN  49  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define OSMOTICA_WATER_IN_SOLENOID_PIN 47   // eletrovalvola acqua in ingresso 
  #define OSMOTICA_WATER_OUT_RELE_PIN 44    //   rele pompa di uscita

  //POZZO
  #define POZZO_SOLENOID_PIN 45

 // LEDS
  #define LEDS_SOLENOID_PIN 31
 
  // GIARDINO
  #define GIARDINO_PERIMETRALE_SOLENOID_PIN 23
  #define GIARDINO_ERBA_SOLENOID_PIN 22

  // LAB 

  #define LAB_EC_SENSOR_PIN A1
  #define LAB_TEMPERATURE_PIN 2
    #define LAB_PH_SENSOR_PIN A0

#else // UNO
  #define OSMOTICA_TOP_SWITCH_PIN  5  // interruttore acqua piena
  #define OSMOTICA_FILL_SWITCH_PIN  6  // interruttore inizzio acqua piena
  #define OSMOTICA_DANGER_SWITCH_PIN  7  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define OSMOTICA_WATER_IN_SOLENOID_PIN 8   // eletrovalvola acqua in ingresso 
  #define OSMOTICA_WATER_OUT_RELE_PIN 9   //   rele pompa di uscita

  // LEDS
  #define LEDS_SOLENOID_PIN 10
 
   // GIARDINO
  #define PERIMETRALE_SOLENOID_PIN 11

  //POZZO
  #define POZZO_SOLENOID_PIN 12
  
  // lab 

  #define LAB_EC_SENSOR_PIN A1
   #define LAB_TEMPERATURE_PIN 5
   #define LAB_PH_SENSOR_PIN A0

#endif

// EPROM

#define EPROM_VASCA1_LEVEL 0 // 1 byte

#define EPROM_GIARDINO_SCHEDULING_DA 2 // 4 byte
#define EPROM_GIARDINO_SCHEDULING_A 6 // 4 byte
#define EPROM_GIARDINO_PERIMETRALE_ENABLE 10 // 1 byte

#define EPROM_ERBA_SCHEDULING_DA 12 // 4 byte
#define EPROM_ERBA_SCHEDULING_A 16 // 4 byte
#define EPROM_ERBA_ENABLE 20 // 1 byte

#define EPROM_LED_SCHEDULING_DA 22 // 4 byte
#define EPROM_LED_SCHEDULING_A 26 // 4 byte
#define EPROM_LED_ENABLE 30 // 1 byte

#define EPROM_LAB_EC_K 32 // 4
#define EPROM_LAB_PH_REF_4 36 // 4
#define EPROM_LAB_PH_REF_6 40 // 4
#endif

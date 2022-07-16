
#ifndef Config_
#define Config_

#define DEBUG_MODE

#ifdef MEGA
#define MAX_RECEIVE_BUFFER 128
#else
#define MAX_RECEIVE_BUFFER 64
#endif

#define VPIN_LOG V0
#define VPIN_CLOCK_DISPLAY V1
#define VPIN_CLOCK_ETA 126

#define VPIN_ERBA_DESC V2
#define VPIN_SW_ERBA 102
#define VPIN_ERBA_DA 105
#define VPIN_ERBA_A 106

#define VPIN_IRRIGAZIONE_DESC V3
#define VPIN_SW_IRRIGAZIONE 103
#define VPIN_IRRIGAZIONE_DA 109
#define VPIN_IRRIGAZIONE_A 110

#define VPIN_SW_PERIMETRO 104
#define VPIN_PERIMETRO_DESC V4
#define VPIN_PERIMETRO_DA 107
#define VPIN_PERIMETRO_A 108

#define VPIN_TIMER_SETUP 40
#define VPIN_TIMER_SETUP_DESC 41
/*
PIn WeMos D1 mini  Pin Arduino IDE
config : "Wemos D1 R1" RICORDARE !!!!!!!!
non tutti vanno ... 
PIN D8 non va programmare !!!!!
PIN D10 non va programmare !!!!!
HO MESSO IN INPUT 2,3,4 che mi sembrano + stabili 

*/
// SWITCHS
#ifdef MEGA
 // #define PERIMETRALE_SWITCH_PIN  24  
  #define ERBA_SWITCH_PIN  22 
  #define POZZO_SWITCH_PIN  42 
  #define PERIMETRALE_SWITCH_PIN  24  
#else // WeMos
 // #define ERBA_SWITCH_PIN  D2  // ARDUINO 2
 // #define PERIMETRALE_SWITCH_PIN  D3 // ARDUINO 3   
 // #define POZZO_SWITCH_PIN  D4 // ARDUINO 4  

  #define ERBA_SWITCH_PIN  D5  // ARDUINO 2
  #define PERIMETRALE_SWITCH_PIN  D6 // ARDUINO 3   
  #define POZZO_SWITCH_PIN  D7 // ARDUINO 4  
  
#endif

// OSMOTICA

#define VPIN_WATER_STATE 20  // 
#define VPIN_WATER_ENABLE 21  // 

#ifdef MEGA
  #define TOP_SWITCH_PIN  53  // interruttore acqua piena
  #define FILL_SWITCH_PIN  51  // interruttore inizzio acqua piena
  #define DANGER_SWITCH_PIN  49  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define WATER_IN_SOLENOID_PIN 105   // eletrovalvola acqua in ingresso 
  #define WATER_OUT_RELE_PIN 106    //   rele pompa di uscita
#else
 // #define TOP_SWITCH_PIN  D2  // interruttore acqua piena
  //#define FILL_SWITCH_PIN  D3  // interruttore inizzio acqua piena
  //#define DANGER_SWITCH_PIN  D4  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define WATER_IN_SOLENOID_PIN D8   // eletrovalvola acqua in ingresso 
  //#define WATER_OUT_RELE_PIN D12    //   rele pompa di uscita
#endif


// LETTO

#define VPIN_LETTO_ENABLE 21  // 

#define VPIN_LETTO_POMPA_STATE 32  // 
#define VPIN_LETTO_POMPA_CMD 33  // 

#define VPIN_LETTO_1_OUT_STATE 31  // 
#define VPIN_LETTO_1_OUT_CMD 34  // 

#ifdef MEGA
 
#else
 // #define TOP_SWITCH_PIN  D2  // interruttore acqua piena
  //#define FILL_SWITCH_PIN  D3  // interruttore inizzio acqua piena
  //#define DANGER_SWITCH_PIN  D4  // interruttore acqua bassa per pompa
  
  // eletrovalvola ingresso acqua
  #define LETTO_POMPA_PIN D4   // eletrovalvola acqua in ingresso 
 // #define LETTO_1_OUT_PIN D3   // eletrovalvola acqua in ingresso 
  //#define WATER_OUT_RELE_PIN D12    //   rele pompa di uscita
#endif

#endif

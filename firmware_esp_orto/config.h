
#ifndef Config_
#define Config_

#define DEBUG_MODE

#ifdef MEGA
#define MAX_RECEIVE_BUFFER 128
#else
#define MAX_RECEIVE_BUFFER 64
#endif

#define VPIN_LOG V0
#define VPIN_CLOCK_DISPLAY 152
#define VPIN_CLOCK_ETA 150

#define VPIN_ORTO_DESC 153
#define VPIN_SW_ORTO 113
#define VPIN_ORTO_DA 111
#define VPIN_ORTO_A 112


/*
PIn WeMos D1 mini  Pin Arduino IDE
config : "Wemos D1 R1" RICORDARE !!!!!!!!

*/
// SWITCHS
#ifdef MEGA
 // #define PERIMETRALE_SWITCH_PIN  24  
  #define ERBA_SWITCH_PIN  22 
  #define POZZO_SWITCH_PIN  42 
  #define PERIMETRALE_SWITCH_PIN  24  
#else // WeMos
  
  #define ORTO_SWITCH_PIN  D2 // ARDUINO 4  
 
#endif



#endif

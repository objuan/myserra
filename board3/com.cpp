/**
 * @file       BlynkHandlers.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Virtual pin utilities
 */
/*
#include <Blynk/BlynkConfig.h>
//#include "VHandlers.h"
#include "config.h"
//#include <Blynk/BlynkDebug.h>

char mem[BLYNK_MAX_SENDBYTES];

void Com_Tick()
{
    //readSerialPort();
  while (Serial.available() > 0 ) {
      //char comando = toLowerCase(Serial.read());
      //String str = Serial.readString();
      String str = Serial.readStringUntil('\n');

      Debug("<<" , str);
    
      if (str.startsWith("_vw ")) {
       
         int idx = str.indexOf(" ",4);
         int pin = str.substring(4,idx).toInt();
         String _s=str.substring(idx+1);

       // Debug("W" , pin , _s );

      //  BlynkParamAllocated pars(_s.length());
      //  pars.add(_s);

    
        BlynkParam pars(mem, 0, sizeof(mem));
      
          pars.add(_s);

         //Debug("PIN2" , pin , pars.asInt());

     // pars.
        VirtualReq req;
        req.pin = pin;
        GetVWriteHandler(pin)(req,pars);
        
      }
      if (str.startsWith("_vr ")) {
       
         int pin = str.substring(4).toInt();
      
        // Debug("R" , pin );
         
        VirtualReq req;
        req.pin = pin;
        GetVReadHandler(pin)(req);
        
      }
  }
   
}
*/

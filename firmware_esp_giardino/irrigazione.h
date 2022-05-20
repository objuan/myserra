
Switch sw_irrigazione("IRRIGAZIONE",POZZO_SWITCH_PIN,VPIN_IRRIGAZIONE_DESC);

BLYNK_WRITE(VPIN_SW_IRRIGAZIONE) { 
  sw_irrigazione.setMode(param[0].asInt() );

}

BLYNK_WRITE(VPIN_IRRIGAZIONE_DA) { 
   Serial.print("IRRIGAZIONE da :");
   Serial.println(param[0].asLong());
   sw_irrigazione.getTimer()->dt_start = param[0].asLong();
}

BLYNK_WRITE(VPIN_IRRIGAZIONE_A) { 
   Serial.print("IRRIGAZIONE a :");
   Serial.println(param[0].asLong());
   sw_irrigazione.getTimer()->dt_end = param[0].asLong();
}

void irrigazione_setup() {
  
  //pinMode(POZZO_SWITCH_PIN, OUTPUT);
 // digitalWrite(POZZO_SWITCH_PIN, RELE_OFF);
  
}

// the loop function runs over and over again forever
void irrigazione_loop(const DateTime &now) 
{ 
  sw_irrigazione.tick(now);
  
}


Switch sw_perimetro("PERIMETRO",PERIMETRALE_SWITCH_PIN,VPIN_PERIMETRO_DESC);

BLYNK_WRITE(VPIN_SW_PERIMETRO) { 
  sw_perimetro.setMode(param[0].asInt() );

}

BLYNK_WRITE(VPIN_PERIMETRO_DA) { 
   Serial.print("PERIMETROIONE da :");
   Serial.println(param[0].asLong());
   sw_perimetro.getTimer()->dt_start = param[0].asLong();
}

BLYNK_WRITE(VPIN_PERIMETRO_A) { 
   Serial.print("PERIMETRO a :");
   Serial.println(param[0].asLong());
   sw_perimetro.getTimer()->dt_end = param[0].asLong();
}


// the loop function runs over and over again forever
void perimetro_loop(const DateTime &now) 
{ 
  sw_perimetro.tick(now);
  
}

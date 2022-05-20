/*
 * Created by marco cecchini
 *
 */

Switch sw_orto("ERBA",ORTO_SWITCH_PIN,VPIN_ORTO_DESC);

BLYNK_WRITE(VPIN_SW_ORTO) { 
  sw_orto.setMode(param[0].asInt() );

}

BLYNK_WRITE(VPIN_ORTO_DA) { 
   Serial.print("orto da :");
   Serial.println(param[0].asLong());
   sw_orto.getTimer()->dt_start = param[0].asLong();
}

BLYNK_WRITE(VPIN_ORTO_A) { 
   Serial.print("orto a :");
   Serial.println(param[0].asLong());
   sw_orto.getTimer()->dt_end = param[0].asLong();
}

void orto_setup() {
}

// the loop function runs over and over again forever
void orto_loop(const DateTime &now) 
{ 
  sw_orto.tick(now);

  // digitalWrite(D2,  RELE_ON);


}

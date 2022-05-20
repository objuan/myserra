/*
 * Created by marco cecchini
 *
 */

Switch sw_erba("ERBA",ERBA_SWITCH_PIN,VPIN_ERBA_DESC);

BLYNK_WRITE(VPIN_SW_ERBA) { 
  sw_erba.setMode(param[0].asInt() );

}

BLYNK_WRITE(VPIN_ERBA_DA) { 
   Serial.print("erba da :");
   Serial.println(param[0].asLong());
   sw_erba.getTimer()->dt_start = param[0].asLong();
}

BLYNK_WRITE(VPIN_ERBA_A) { 
   Serial.print("erba a :");
   Serial.println(param[0].asLong());
   sw_erba.getTimer()->dt_end = param[0].asLong();
}

void giardino_setup() {
}

// the loop function runs over and over again forever
void giardino_loop(const DateTime &now) 
{ 
  sw_erba.tick(now);

  // digitalWrite(D2,  RELE_ON);


}

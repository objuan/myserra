/*
 * Created by marco cecchini
 *
 */

Switch sw_pompa("POMPA",LETTO_POMPA_PIN,VPIN_LETTO_POMPA_STATE);
//Switch sw_letto1_out("LETTO1_OUT",LETTO_1_OUT_PIN,VPIN_LETTO_1_OUT_STATE);

bool lettoEnable = false;

BLYNK_WRITE(VPIN_LETTO_ENABLE) { 
  lettoEnable = param[0].asInt() ==1;
}
BLYNK_WRITE(VPIN_LETTO_POMPA_CMD) { 
   sw_pompa.setMode(param[0].asInt() );

}
BLYNK_WRITE(VPIN_LETTO_1_OUT_CMD) { 
 //  sw_letto1_out.setMode(param[0].asInt() );

}

void letto_setup() {
  /* prova 1, pompa pieno regiime , scarico tutto vuoto
   *  IN 3 minuti , OUT 
  */
  Serial.println("letto_setup");
  DateTime s(0,0,0,8,0,0);
  DateTime e(0,0,0,20,0,0);
  sw_pompa.getTimer()->dt_start = sw_pompa.getTimer()->getTime(s);
  sw_pompa.getTimer()->dt_end =   sw_pompa.getTimer()->getTime(e);
  sw_pompa.getTimer()->setMode(TimerMode::STEP_INTERVAL);
  // 3 min ON , svuota in 14 minuti ,  periodo uno ogni ora 
  // 3 min ON , svuota in 14 minuti ,  periodo uno ogni 2 ore
  int durata = 15*60;
  int periodo = 30 * 60;
  sw_pompa.getTimer()->setPeriod(durata ,periodo);
}
  
  // the loop function runs over and over again forever
void letto_loop(const DateTime &now) 
{ 
    sw_pompa.tick(now);
   // sw_letto1_out.tick(now);
  
 //  String state = "EN:" +String(lettoEnable)+"|"+String(sw_pompa.mode)+"|"+String(sw_letto1_out.mode);
  //  Blynk.virtualWrite(VPIN_LETTO_POMPA_STATE,state.c_str());
        
}

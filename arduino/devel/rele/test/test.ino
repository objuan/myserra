/*
  Rele - Messa Roberto
  Eccita il rel� per un secondo e poi lo rilascia in continuazione.
 
 */
bool releAttivo=false;
 
void setup() {
  // inizializza i pin digitali come output.
  // il rel� sar� collegato sul pin 12:
  pinMode(7, OUTPUT);     
 
  // inizializza la porta seriale a 9600 bps:
  Serial.begin(9600);

  Serial.println("Inizio");
}
 
void loop() {
 Serial.println(releAttivo);
 
  if (releAttivo == true){
    digitalWrite(7, LOW);   // eccita il rel�.
    Serial.println("Chiudo il contatto");
   }
  else{
    digitalWrite(7, HIGH);  // apre il rel�.
     Serial.println("Apro il contatto");
     }
 
  releAttivo = !releAttivo;
 
  delay(5000);              // attende per un secondo.
}

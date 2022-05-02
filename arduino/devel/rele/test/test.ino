/*
  Rele - Messa Roberto
  Eccita il rel� per un secondo e poi lo rilascia in continuazione.
 
 */

 #include <ESP8266WiFi.h>
 
bool releAttivo=false;

#define PORT D3
 
void setup() {
  // inizializza i pin digitali come output.
  // il rel� sar� collegato sul pin 12:
  pinMode(PORT, OUTPUT);     
 
  // inizializza la porta seriale a 9600 bps:
  Serial.begin(9600);

  Serial.println("Inizio");
}
 
void loop() {
 Serial.println(releAttivo);
 
  if (releAttivo == true){
    digitalWrite(PORT, LOW);   // eccita il rel�.
    Serial.println("Chiudo il contatto");
   }
  else{
    digitalWrite(PORT, HIGH);  // apre il rel�.
     Serial.println("Apro il contatto");
     }
 
  releAttivo = !releAttivo;
 
  delay(2000);              // attende per un secondo.
}

    /*Sketch per rilevare l'umidita' del terreno (valore analogico)*/
    void setup()
    {
      Serial.begin(9600);

      Serial.println("STart"); //Stampa a schermo il valore
    }
    void loop()
    {
      int sensorValue1 = analogRead(A1); //Legge il valore analogico
      int sensorValue2 = analogRead(A2); //Legge il valore analogico
      Serial.println(sensorValue1); //Stampa a schermo il valore
      Serial.println(sensorValue2); //Stampa a schermo il valore
      
      delay(2000); //Attende due secondi
    }

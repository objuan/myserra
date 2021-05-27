#include <Arduino.h>

float calibration = 0.00; //change this value to calibrate
int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0;

int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("cimpleo pH Sense");
}

float ph (float voltage) {
    return 7 + ((2.5 - voltage));// / 0.18);
}

void loop()
{
    // taratura

  int valore = analogRead(A0);
    float tensione = valore * (5.0 / 1023.0);
    Serial.println(tensione);

    return;
    
    
    /*
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(30);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH= ");
    //Serial.println(ph(voltage));
    Serial.println(ph(5 / adc_resolution * analogRead(pHSense)));
    delay(3000);
    

    return;
    */
  for(int i=0;i<10;i++)
  {
      buf[i]=analogRead(pHSense);
      delay(30);
  }
  // ordino
  for(int i=0;i<9;i++)
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];buf[i]=buf[j];buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)avgValue+=buf[i];
  
  float pHVol=(float)avgValue*5.0/1024/6;
 // float phValue = -5.70 * pHVol + calibration;
  float phValue =  ph(pHVol + calibration);
  
  Serial.print("sensor = ");
  Serial.print(pHVol);
   Serial.print("   = ");
  Serial.println(phValue);delay(500);
}

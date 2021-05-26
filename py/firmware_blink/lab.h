/*
 * Created by marco cecchini
 *
 */
#include <BlynkSimpleStream.h>
#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
#include "GravityTDS.h"
#include <OneWire.h>

#define LAB_EC_SENSOR_PIN A1
#define LAB_TEMPERATURE_SENSOR_PIN 2

 int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(LAB_TEMPERATURE_SENSOR_PIN);  // on digital pin 2


class Lab
{
  float temperature = 25;
  float tdsValue = 0;
  float ecValue = 0;
  GravityTDS* _gravityTds;

  #define VREF 5.0      // analog reference voltage(Volt) of the ADC
  #define SCOUNT  30           // sum of sample point
  int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
  int analogBufferTemp[SCOUNT];
  int analogBufferIndex = 0,copyIndex = 0;
  float averageVoltage = 0;


  public:
    Lab(VirtualElementManager &manager){

      _gravityTds = new  GravityTDS();
      GravityTDS &gravityTds = *_gravityTds;
        gravityTds.setPin(LAB_EC_SENSOR_PIN);
        gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
        gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
        gravityTds.begin();  //initialization
        

        // pinMode(LAB_EC_SENSOR_PIN,INPUT);
    }

    void Logic(){
    }
    
  
    void LogicFast(){
     
/*
       static unsigned long analogSampleTimepoint = millis();
     if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
     {
       analogSampleTimepoint = millis();
       analogBuffer[analogBufferIndex] = analogRead(LAB_EC_SENSOR_PIN);    //read the analog value and store into the buffer
       analogBufferIndex++;
       if(analogBufferIndex == SCOUNT) 
           analogBufferIndex = 0;
     }   
     static unsigned long printTimepoint = millis();
     if(millis()-printTimepoint > 800U)
     { temperature= getTemp();

        printTimepoint = millis();
        for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
          analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
        averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
        float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
        float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
        tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
        //Serial.print("voltage:");
        //Serial.print(averageVoltage,2);
        //Serial.print("V   ");
       // Serial.print("TDS Value:");
        //Serial.print(tdsValue,0);
       // Serial.println("ppm");
     }
     */
       GravityTDS &gravityTds = *_gravityTds;
      gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
      gravityTds.update();  //sample and calculate
      
      tdsValue = gravityTds.getTdsValue();  // then get the value
      ecValue = gravityTds.getEcValue();
      
      Debug("EC ", ecValue, " tds ", tdsValue);

     // float temperature = getTemp();
      Debug("temp",temperature);


     // Serial.print(tdsValue,0);
     // Serial.println("ppm");
      //delay(1000);
    }


      int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}

  float getTemp(){
    //returns the temperature from one DS18S20 in DEG Celsius
  
    byte data[12];
    byte addr[8];
  
    if ( !ds.search(addr)) {
        //no more sensors on chain, reset search
        ds.reset_search();
        return -1000;
    }
  
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Error("CRC is not valid!");
        return -1000;
    }
  
    if ( addr[0] != 0x10 && addr[0] != 0x28) {
        Error("Device is not recognized");
        return -1000;
    }
  
    ds.reset();
    ds.select(addr);
    ds.write(0x44,1); // start conversion, with parasite power on at the end
  
    byte present = ds.reset();
    ds.select(addr);
    ds.write(0xBE); // Read Scratchpad
  
  
    for (int i = 0; i < 9; i++) { // we need 9 bytes
      data[i] = ds.read();
    }
  
    ds.reset_search();
  
    byte MSB = data[1];
    byte LSB = data[0];
  
    float tempRead = ((MSB << 8) | LSB); //using two's compliment
    float TemperatureSum = tempRead / 16;
  
    return TemperatureSum;
  
  }
  
};

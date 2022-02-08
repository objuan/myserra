/*
   Created by marco cecchini

*/

#include "config.h"
#include "common.h"
#include <ArduinoJson.h>
//#include "GravityTDS.h"

#include <OneWire.h>
#include <DallasTemperature.h>


#define LAB_EC_SENSOR_VPIN 140
#define LAB_EC_K_VPIN 141
#define LAB_EC_TEMPERATURE_VPIN 142

#define LAB_PH_SENSOR_VPIN 143
#define LAB_PH_VOLTAGE_VPIN 144
#define LAB_PH_REF_4_VPIN 145
#define LAB_PH_REF_6_VPIN 146
#define LAB_DISTANCE_VPIN 147

#define LAB_WEIGHT_1_VPIN 149

//Temperature chip i/o
OneWire ds(LAB_TEMPERATURE_PIN);  // on digital pin 2
//DallasTemperature sensors(&ds);// Pass our oneWire reference to Dallas Temperature.


class Var_PH: public Var_Real
{
  public:
   Var_Real *var_ph_voltage;
  Var_Real *var_ph_ref_4;
  Var_Real *var_ph_ref_6;
    
  #define samplingInterval 30
  #define ArrayLenth  10    //times of collection
  int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
  int pHArrayIndex=0;    
  float voltage;
  
   Var_PH(int vpin, Var_Real *var_ph_voltage,Var_Real *var_ph_ref_4,Var_Real *var_ph_ref_6) : Var_Real(vpin), var_ph_voltage(var_ph_voltage),var_ph_ref_4(var_ph_ref_4),var_ph_ref_6(var_ph_ref_6) {
   }

   void tickFast()
   {
       int adcValue = analogRead(LAB_PH_SENSOR_PIN);

      static unsigned long samplingTime = millis();
      static unsigned long printTime = millis();
 
      if(millis()-samplingTime > samplingInterval)
      {
          pHArray[pHArrayIndex++]=analogRead(LAB_PH_SENSOR_PIN);
          if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
          voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
          voltage = ((float)adcValue * 5.0 / 1024);

          //Debug(voltage);
          samplingTime=millis();
      }
      
   }
   void tick()
   {
      var_ph_voltage->set(voltage);
    // m = (pH7 - pH4) / (Vph7 - Vph4)
      float m = (6.86  - 4.01 ) / ( var_ph_ref_6->get() - var_ph_ref_4->get());

      float phValue = 6.86  - (2.5 - voltage) * m;
      set(phValue);
   }
   
   double avergearray(int* arr, int number)
   {
    int i;
    int max,min;
    double avg;
    long amount=0;
    if(number<=0){
      Serial.println("Error number for the array to avraging!/n");
      return 0;
    }
    if(number<5){   //less than 5, calculated directly statistics
      for(i=0;i<number;i++){
        amount+=arr[i];
      }
      avg = amount/number;
      return avg;
    }else{
      if(arr[0]<arr[1]){
        min = arr[0];max=arr[1];
      }
      else{
        min=arr[1];max=arr[0];
      }
      for(i=2;i<number;i++){
        if(arr[i]<min){
          amount+=min;        //arr<min
          min=arr[i];
        }else {
          if(arr[i]>max){
            amount+=max;    //arr>max
            max=arr[i];
          }else{
            amount+=arr[i]; //min<=arr<=max
          }
        }//if
      }//for
      avg = (double)amount/(number-2);
    }//if
    return avg;
  }
};


class Var_EC: public Var_Real
{
  public:

    Var_Real *var_k;
    Var_Real *var_temperature;
 
   // GravityTDS* gravityTds;

      // float temperature = 25;
    float tdsValue = 0;
   // float ecValue = 0;

#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
    int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
    int analogBufferTemp[SCOUNT];
    int analogBufferIndex = 0, copyIndex = 0;
    float averageVoltage = 0;


    Var_EC(int vpin, Var_Real *var_k,Var_Real *var_temperature) : Var_Real(vpin), var_k(var_k),var_temperature(var_temperature) {
/*
        gravityTds = new  GravityTDS( );
        gravityTds->setPin(LAB_EC_SENSOR_PIN);
        gravityTds->setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
        gravityTds->setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
        gravityTds->setKValue(var_k->get());
        gravityTds->begin();  //initialization

        Log(F("VAR EC K :") ,var_k->get());
        */
      
    }

    void tickFast()
    {
    
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
           { 
              //temperature= getTemp();

              printTimepoint = millis();
              for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
                analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
              averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
             
              float compensationCoefficient=1.0+0.02*(var_temperature->get()-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
              float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
              tdsValue=var_k->get()*(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
           
              set(tdsValue*2);
              /*
              this->analogValue = analogRead(this->pin);
              this->voltage = this->analogValue/this->adcRange*this->aref;
              this->ecValue=(133.42*this->voltage*this->voltage*this->voltage - 255.86*this->voltage*this->voltage + 857.39*this->voltage)*this->kValue;
              this->ecValue25  =  this->ecValue / (1.0+0.02*(this->temperature-25.0));  //temperature compensation
              this->tdsValue = ecValue25 * TdsFactor;
              */
            //  Serial.print("voltage:");
             // Serial.println(averageVoltage,2);
              //Serial.print("V   ");
             // Serial.print("TDS Value:");
              //Serial.print(tdsValue,0);
             // Serial.println("ppm");
           }
            //  sensors.requestTemperatures();// Send the command to get temperatures
           //  temperature = sensors.getTempCByIndex(0);
           /* 
          gravityTds->setTemperature(var_temperature->get());  // set the temperature and execute temperature compensation
          gravityTds->setKValue(var_k->get());
          gravityTds->update();  //sample and calculate

          //  tdsValue = gravityTds.getTdsValue();  // then get the value
          value = gravityTds->getEcValue();
          cloudWrite(this->pin, this->value );
          */
    }
    int getMedianNum(int bArray[], int iFilterLen)
    {
      int bTab[iFilterLen];
      for (byte i = 0; i < iFilterLen; i++)
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


};

// ==========================================================

class Lab
{

    Var_Real *var_temperature;

    //ec
     Var_Real *var_k;
    Var_EC *var_ec;

  // ph
    Var_PH *var_ph;
    Var_Real *var_ph_voltage;
    Var_Real *var_ph_ref_4;
    Var_Real *var_ph_ref_6;

    DistanceSensor *distance;

    WeightSensor* weight;
  
     
  public:
    Lab(VirtualElementManager &manager)
    {
     // return;
      
      var_k = manager.addVarReal(LAB_EC_K_VPIN, 1,EPROM_LAB_EC_K);
    //  var_k->set(1.1);
      var_temperature = manager.addVarReal(LAB_EC_TEMPERATURE_VPIN);
      var_ec = (Var_EC*)manager.Add(new Var_EC(LAB_EC_SENSOR_VPIN, var_k,var_temperature));

      var_ph_ref_4 = manager.addVarReal(LAB_PH_REF_4_VPIN,0,EPROM_LAB_PH_REF_4);
      var_ph_ref_6 = manager.addVarReal(LAB_PH_REF_6_VPIN,0,EPROM_LAB_PH_REF_6);
      var_ph_voltage = manager.addVarReal(LAB_PH_VOLTAGE_VPIN);
      var_ph = (Var_PH*)manager.Add(new Var_PH(LAB_PH_SENSOR_VPIN, var_ph_voltage,var_ph_ref_4,var_ph_ref_6));

      distance = (DistanceSensor*)manager.Add(new DistanceSensor(LAB_DISTANCE_VPIN,LAB_RANGE_TRIGGER_PIN,LAB_RANGE_ECHO_PIN));

      weight =  (WeightSensor*)manager.Add(new WeightSensor(LAB_WEIGHT_1_VPIN,LAB_CARICO_1_DT_PIN,LAB_CARICO_1_SCK_PIN));

    }

    void LogicFast() {
      //return;
        var_ec->tickFast();
        var_ph->tickFast();
    }

  int i=0;
    void Logic() {

      // return;
      // GravityTDS &gravityTds = *_gravityTds;
      //  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
      //  gravityTds.update();  //sample and calculate

      //  tdsValue = gravityTds.getTdsValue();  // then get the value
      //  ecValue = gravityTds.getEcValue();

    //  sensors.requestTemperatures();// Send the command to get temperatures
           
      //var_temperature->set(sensors.getTempCByIndex(0));

    //  var_temperature->set(i++);
      var_temperature->set(getTemp());

     // ecValue = var_ec->get();
    
      Debug(F("EC "), var_ec->get(), " k:",var_k->get(),F(" temp:"), var_temperature->get(),F(" phv:"), var_ph_voltage->get(),F(" 4:") ,var_ph_ref_4->get(),F(" 6:"),var_ph_ref_6->get(),F(" ph:"), var_ph->get()," d:" , distance->get());

      // Serial.print(tdsValue,0);
      // Serial.println("ppm");
      //delay(1000);
    }


    
    float getTemp() {
      //returns the temperature from one DS18S20 in DEG Celsius

      byte data[12];
      byte addr[8];

      if ( !ds.search(addr)) {
        //no more sensors on chain, reset search
         Error("Device is not find");
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
      ds.write(0x44, 1); // start conversion, with parasite power on at the end

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

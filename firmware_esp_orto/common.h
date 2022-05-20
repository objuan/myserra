#ifndef _COMMON
#define _COMMON

#include "RTClib.h"

unsigned long long atoll(String s)
{
   char arr[12];
   s.toCharArray(arr, sizeof(arr));
   return atoll(arr);
}

#include <EEPROM.h>

//#include <Wire.h>

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

//extern char mem_send[BLYNK_MAX_SENDBYTES];
        
template <typename... Args>
void Log(Args... values) {
        
        Blynk.virtualWrite(VPIN_LOG, values...);
 }


class movingAvg
{
    private:
        int _size;     // number of data points for the moving average
        int count;  // number of readings
        float sum;         // sum of the m_readings array
        int index;         // index to the next reading
        float *data;    // pointer to the dynamically allocated interval array
        
    public:
        movingAvg(int _size)
            : _size(_size), count(0), sum(0), index(0) {
              data = new float[_size];
           }

        float Add(float value){
            // Serial.println(value);
            if (count < _size)
            {
                ++count;
                sum = sum + value;
            }
            else
            {
                sum = sum - data[index] + value;
              
            }
             data[index]=value;
             if (++index >= _size) index = 0;
                
            // Serial.println(count);
            //  Serial.println(_size);
             //  Serial.println(index);
           // Serial.println(sum);
            return sum / count;
            
            //m_readings[m_next] = newReading;
           // if (++m_next >= m_interval) m_next = 0;
          //  return m_sum / m_nbrReadings;
           // return (m_sum + m_nbrReadings / 2) / m_nbrReadings;
        }
   

        void reset(){
            count = 0;
            sum = 0;
            index = 0;
        }


  
};

// DATETIME


byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

/*
void setDateTime(const DateTime &dt){
    resetTime = dt;
    systemTime = dt;
    resetMills = millis();
}
// YYYY-DD-MM-HH-mm-SS
DateTime ParseDateTime(const String& str){
    int y = str.substring(0,4).toInt();
    int m = str.substring(5,7).toInt();
    int d = str.substring(8,10).toInt();
    int hh= str.substring(11,13).toInt();
    int mm = str.substring(14,16).toInt();
    int ss = str.substring(17,19).toInt();
    return DateTime(y,m,d,hh,mm,ss);
}
*/
// =======================================

byte EEPROM_ReadByte(int address) {
  byte val = EEPROM.read(address);
  Log(F("Load ROM "), address,"=",val);
  return val ;
}

void EEPROM_Write(int address,byte value) {
  EEPROM.write(address,value);
}


long EEPROM_ReadLong(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  long val =  ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
   Log(F("Load ROM "), address,"=",val);
   return val;
}

void EEPROM_Write(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

void EEPROM_Write(int address, int number)
{ 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int EEPROM_ReadInt(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  int val =  (byte1 << 8) + byte2;
    Log(F("Load ROM "), address,"=",val);
  return val;
}


void EEPROM_Write(int p_address, float value)
{
  Log(F("Write ROM "), p_address,"=",value);
  
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
        EEPROM.write(p_address++, *p++);
}

float EEPROM_ReadFloat(int p_address)
{
    float  value = 0.0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(p_address++);
    if (value>= -99999 && value < 99999)
    {
      Log(F("Load ROM "), p_address,"=",value);
    }
    else
      value=0;
    return value;
}
#endif

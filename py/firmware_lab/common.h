#ifndef _COMMON
#define _COMMON

// Limit the incoming command length.
#ifndef BLYNK_MAX_READBYTES
#define BLYNK_MAX_READBYTES  256
#endif

// Limit the outgoing command length.
#ifndef BLYNK_MAX_SENDBYTES
#define BLYNK_MAX_SENDBYTES  128
#endif

unsigned long long atoll(String s)
{
   char arr[12];
   s.toCharArray(arr, sizeof(arr));
   return atoll(arr);
}

//#include <Blynk/BlynkConfig.h>
#include "BlynkParam.h"
#include <EEPROM.h>

#include <Wire.h>
#define DS1307_ADDRESS 0x68
byte zero = 0x00; //workaround for issue #527
#include "RTClib.h"

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

void Com_Tick();

extern DateTime lastTime;

template <typename... Args>
void Log(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(F("[LOG] "));
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
template <typename... Args>
void Debug(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(F("[DEBUG] "));
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
    template <typename... Args>
 void Warn(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(F("[WARN] "));
        cmd.add_multi(values...);
         cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
    template <typename... Args>
 void Error(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(F("[ERROR] "));
        cmd.add_multi(values...);
         cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
    
  template <typename... Args>
 void COMMAND(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
         cmd.add(F("CMD"));
        cmd.add_multi(values...);
         cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
        
//#define CLOUD_ON_WRITE(pin)      VIRTUAL_WRITE_2(pin)
//#define CLOUD_ASK_VALUE(pin)       VIRTUAL_READ_2(pin)

template <typename... Args>
void cloudWrite(int pin, Args... values) {
       // Debug("writew",pin);
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(F("vw"));
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
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

DateTime currentDateTime(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = 2000+ bcdToDec(Wire.read());
  if (year > 2020 && year < 2025)
  {
    //print the date EG   3/1/11 23:59:59
    lastTime = DateTime(year,month,monthDay,hour,minute,second);
  }
  return lastTime;
  /*
  Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
  */

}
void setDateTime(const DateTime &dt){

  byte second =      dt.second(); //0-59
  byte minute =      dt.minute(); //0-59
  byte hour =        dt.hour(); //0-23
  byte weekDay =     dt.dayOfTheWeek () ;//dt.weekDay(); //1-7
  byte monthDay =    dt.day(); //1-31
  byte month =       dt.month(); //1-12
  int y =  dt.year();
  if (y > 100) y = y- 2000;
  byte year  =      y; //0-99

 /* Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
  */
  
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //stop Oscillator

  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));

  Wire.write(zero); //start 

  Wire.endTransmission();

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
    Log(F("Load ROM "), p_address,"=",value);
    return value;
}
#endif

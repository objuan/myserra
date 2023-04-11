#include <BlynkSimpleStream.h>

#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>


#ifndef Config_
#define Config_

#define DEBUG_MODE
#ifdef MEGA
#define MAX_RECEIVE_BUFFER 128
#else
#define MAX_RECEIVE_BUFFER 64
#endif

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

//#define USE_RTC
//#define MEGA

//#ifdef USE_RTC
//#include <Wire.h>
#include "RTClib.h"

//#endif

// disattiva i releas
//#define SYM_MODE
#define DEBUG_MODE

extern char mem_send[BLYNK_MAX_SENDBYTES]; 

// =================================

//extern bool isMinutesInside(const char *name, DateTime now,DateTime from, DateTime to);
extern void printDateTime(DateTime now);
extern void printDateTimeln(DateTime now);
extern String str_DateTime(const DateTime &now);

void writeString(int add,String data);
String read_String(int add);
String read_String(int add,int n);

void mydigitalWrite(int pin, int value);

void Com_Tick();

extern  Stream *manager_serial;
        
template <typename... Args>
void virtualWrite(int pin, Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("vw");
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add("\n");
         manager_serial->write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
        //Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }

template <typename... Args>
void virtualWrite_serial(Stream &serial,int pin, Args... values) {
      //  Serial.println("_cloudWrite2");
       
        BlynkParam cmd(mem_send, 0, sizeof(mem_send));
        cmd.add(F("vw"));
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }

  template <typename... Args>
void virtualWrite_serial(Stream &serial,char*pin, Args... values) {
      //  Serial.println("_cloudWrite2");
       
        BlynkParam cmd(mem_send, 0, sizeof(mem_send));
        cmd.add(F("vw"));
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add(F("\n"));
        serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }

    
template <typename... Args>
void VirtualLog(Args... values) {
        virtualWrite(0, values...);
        //Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
}

template <typename... Args>
void Log(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[LOG] ");
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
template <typename... Args>
void Debug(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[DEBUG] ");
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
    template <typename... Args>
 void Warn(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[WARN] ");
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
    template <typename... Args>
 void Error(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[ERROR] ");
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
#define CLOUD_ON_WRITE(pin)      VIRTUAL_WRITE_2(pin)
#define CLOUD_ASK_VALUE(pin)       VIRTUAL_READ_2(pin)

template <typename... Args>
void cloudWrite_old(int pin, Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("vw");
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }
    
#endif

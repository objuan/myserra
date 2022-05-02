#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>
//#include "vhandlers.h"
//#include <BlynkSimpleEsp8266.h>

#ifndef Config_
#define Config_

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

#define USE_RTC

//#define MEGA

#ifdef USE_RTC
//#include <Wire.h>
#include "RTClib.h"

#endif

// disattiva i releas
//#define SYM_MODE
#define DEBUG_MODE

// =========== PINS ====================== 


// =================================

//extern bool isMinutesInside(const char *name, DateTime now,DateTime from, DateTime to);
extern void printDateTime(const DateTime& now);
extern void printDateTimeln(const DateTime& now);
extern String str_DateTime(const DateTime& now);

void writeString(int add,String data);
String read_String(int add);
String read_String(int add,int n);

void mydigitalWrite(int pin, int value);

#define BLYNK_MAX_SENDBYTES 128

void Com_Tick();

/*
template <typename... Args>
void virtualWrite(int pin, Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("vw");
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }
*/
template <typename... Args>
void Log(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[LOG] ");
        cmd.add_multi(values...);
       // Blynk.virtualWrite(V0, (unsigned char*)cmd.getBuffer());
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
template <typename... Args>
void Logln(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("[LOG] ");
        cmd.add_multi(values...);
        cmd.add("\n");
        //Blynk.virtualWrite(V0, (unsigned char*)cmd.getBuffer());
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
/*    
#define CLOUD_ON_WRITE(pin)      BLYNK_WRITE(pin)
#define CLOUD_ASK_VALUE(pin)       BLYNK_WRITE(pin)

template <typename... Args>
void cloudWrite(int pin, Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("vw");
        cmd.add(pin);
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
       // static_cast<Proto*>(this)->sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength()-1);
    }

    */
#endif

#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>
#include "vhandlers.h"

#ifndef Config_
#define Config_

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

void Com_Tick();


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
    
  template <typename... Args>
 void COMMAND(Args... values) {
        char mem[BLYNK_MAX_SENDBYTES];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("CMD");
        cmd.add_multi(values...);
        cmd.add("\n");
        Serial.write((unsigned char*)cmd.getBuffer(), cmd.getLength()-1);
    }
        
//#define CLOUD_ON_WRITE(pin)      VIRTUAL_WRITE_2(pin)
//#define CLOUD_ASK_VALUE(pin)       VIRTUAL_READ_2(pin)

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
    
#endif

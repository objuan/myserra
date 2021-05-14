#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>

#ifndef Config_
#define Config_

#define SOLENOID_ON LOW
#define SOLENOID_OFF HIGH

#define RELE_ON LOW
#define RELE_OFF HIGH

void Com_Tick();


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
#endif

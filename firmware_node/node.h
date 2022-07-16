#include <Blynk/BlynkConfig.h>
#include <Blynk/BlynkParam.h>
#include <SoftwareSerial.h>
#include "config.h"
//#include "virtual_elements_manager.h"

#ifndef _Node
#define _Node

#define NODE_MATER 1
#define NODE_SLAVE 2

#define NODE_CMD_MODE_D 0
#define NODE_CMD_MODE_A 1

#define NODE_CMD_SET 0
#define NODE_CMD_READ 1
#define NODE_CMD_WRITE 2

/* LINGUAGGIO  MESSAGGI
 *  ACK ID MODE
 *  READ prefisso = ID 
 *   -> S D IN | S D OUT
   *  ->R D 1 -> read digital 1 
   *  ->R A 2 -> read analog 2
   *  <-V D 1 <valore>
   *  <-V A 2 <valore>
   * es ESP R D 1
   * WRITE
   *  -> W D 1 <valore>
   *  -> W A 1 <valore>
 *  */

class NearNode
{
  public:
  
  String id;
  int mode;
  int time;

  void SendAck(Stream *serial)
  {
    serial->print("A ");
    serial->print(id);
    serial->print(" ");
    serial->print(mode);
    serial->print(" ");
    serial->println(time);
  }
  
};

class Node
{
   int count=0;
  int mode;
  const char* id;
  Stream *serial1;
  Stream *serial2;
private:
    char in_buffer[MAX_RECEIVE_BUFFER]; 
    int mem_len=0;
    int  in_buffer_len=0;
    bool fromWeb;
    int incomingByte = 0;


    NearNode nearNode;
    
  private:
    void Process( char *buffer,int len);
     void tick(Stream *serial);
  public:
    Node(const char *id, Stream* serial1,Stream* serial2,int mode);

    void tick();
   //void fast_tick();

   void sendACK(int time,Stream *serial){
    serial->print("A ");
    serial->print(id);
    serial->print(" ");
    serial->print(mode);
    serial->print(" ");
    serial->println(time);
    }
   
};
   
#endif

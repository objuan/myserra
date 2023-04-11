#include "config.h"
#include "eprom.h"

#include "BlynkParam.h"
 #include "Common.h"
 
char in_buffer[250]; 
int  in_buffer_len=0;
int incomingByte = 0;

#define NODE_CMD_MODE_D 0
#define NODE_CMD_MODE_A 1
#define NODE_CMD_MODE_IN 2
#define NODE_CMD_MODE_OUT 3

#define NODE_CMD_SET 0
#define NODE_CMD_READ 1
#define NODE_CMD_WRITE 2

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  Log("INIT");
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
}

 void Process( char *buffer,int len)
 {  
    BlynkParam pp(buffer,len);
    Debug("<<",pp.asString());
      
    String in =pp.asString();

    char *p = in.c_str();
    char *str;
    int index = 0;
    int cmd=0;
    int mode;
    int pin;
    int value=99;
    
      while ((str = strtok_r(p, " ", &p)) != NULL) 
       {
          // Debug(".",index, " " ,str);

          if (index == 0) { // PIN
           
            pin = atoi(str);
          }
          if (index == 1) { // COMMAND
            if (strcmp(str ,"A")==0)
            {
              // ACK
              
            }
            if (strcmp(str ,"S")==0) cmd = NODE_CMD_SET;
            if (strcmp(str ,"R")==0) cmd = NODE_CMD_READ;
            if (strcmp(str ,"W")==0) cmd = NODE_CMD_WRITE;
          }  
          if (index == 2) { // COMMAND
            if (strcmp(str ,"D")==0) mode = NODE_CMD_MODE_D;
            if (strcmp(str ,"A")==0) mode = NODE_CMD_MODE_A;
            
            if (strcmp(str ,"I")==0) mode = NODE_CMD_MODE_IN;
            if (strcmp(str ,"O")==0) mode = NODE_CMD_MODE_OUT;
          } 
          
           if (index == 3) { // VALUE
           
            value = atoi(str);
          }

         
          index++;
       }
      
       //Debug(pin," ", cmd," " ,mode," " ,value);

       if (cmd == NODE_CMD_SET)
       {
          if (mode == NODE_CMD_MODE_IN)
          {
              pinMode(pin, INPUT);
              Log("<<pinMode(" , pin ,",", INPUT,")");
          }
           else if (mode == NODE_CMD_MODE_OUT)
           {
              pinMode(pin, OUTPUT);
              Log("<<pinMode(" , pin ,",", OUTPUT,")");
           }
       }
       
       if (cmd == NODE_CMD_READ)
       {
          int val=0;
          if (mode == NODE_CMD_MODE_D)
          {
              val = digitalRead(pin);
              Log("<<digitalRead(" , pin ,",", value,")=",val);
          }
           else if (mode == NODE_CMD_MODE_A)
           {
              val = analogRead(pin);
              Log("<<analogRead(" , pin ,",", value,")=",val);
           }
          // char buff[100];buff[0]=0;
          // sprintf(buff, "%s %d",id,pin);
           //virtualWrite_serial(*serial1,buff, val);            
       }
       if (cmd == NODE_CMD_WRITE)
       {
         
          if (mode == NODE_CMD_MODE_D)
          {
             Log("<<digitalWrite(" , pin ,",", value,")");
              digitalWrite(pin,value);
          }
           else if (mode == NODE_CMD_MODE_A)
           {
              Log("<<analogWrite(" , pin ,",", value,")");
               analogWrite(pin,value);
           }
       }
       
    //Serial.println();
 }
 

void loop() {
   Stream *serial = &Serial;
  
    while (serial->available() > 0 ) 
    {
        incomingByte = serial->read();

        //Debug(incomingByte);
        if (incomingByte == '\n')
        {
           //Debug("in");
           in_buffer[in_buffer_len] = '\0';
          
           Process(in_buffer,in_buffer_len);
            
          in_buffer_len=0;
        }
        else
        {
            in_buffer[in_buffer_len++] = (char )incomingByte;
        }
     //
    }
}

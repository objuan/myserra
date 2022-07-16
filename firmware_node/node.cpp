#include "NODE.H"


Node::Node(const char *id, Stream* serial1,Stream* serial2,int mode):id(id), mode(mode)
,serial1(serial1),serial2(serial2)
{
      fromWeb=true;
    //  nearListCount=0;
}

char mem_send[BLYNK_MAX_SENDBYTES];

void Node::tick()
{
  if (serial1!=NULL)  tick(serial1);
  if (serial2!=NULL)  tick(serial2);
}
void Node::tick(Stream *serial)
{
    // Debug(id,"..");

    while (serial->available() > 0 ) 
    {
      incomingByte = serial->read();
     // Serial.flush();
      //String c = String((char)incomingByte);

     // if (incomingByte == '\0') incomingByte= '|';

      //Serial.println("..");
     // if (id =="MA")
     // Debug (id, " ", incomingByte," l:",in_buffer_len," m:",freeMemory(),fromWeb ? "w":"n");

      if (incomingByte == 1) // end block
      {
         if (fromWeb)
        {
          serial->println(F("ACK"));
          serial->flush();
        }
      }
      else 
      {
        if (incomingByte == '\n')
        {
           //Debug("in");
           in_buffer[in_buffer_len] = '\0';
          
           Process(in_buffer,in_buffer_len);
            
          in_buffer_len=0;
          /*if (fromWeb)
          {
            serial->println(F("ACK"));
            serial->flush();
          }
  */
        }
        else
        {
          #ifdef DEBUG_MODE
     //     if (in_buffer_len >= MAX_RECEIVE_BUFFER)
       ///       Error(F("MRB"));
          #endif
            in_buffer[in_buffer_len++] = (char )incomingByte;
          //  Debug(in_buffer);
        }
      }
     //
    }
  
}

 void Node::Process( char *buffer,int len)
 { 
  BlynkParam pp(buffer,len);
  Debug(id,"<<",pp.asString());
      
  String in =pp.asString();
  if (in.startsWith(id))
  {
      // messaggio destinato a me 
      in = in.substring(strlen(id)+1);

       Debug(id,"1", in.c_str());

    char *p = in.c_str();
    char *str;
    int index = 0;
    int cmd=0;
    int mode;
    int pin;
    int value=99;
      while ((str = strtok_r(p, " ", &p)) != NULL) 
       {
         // values[index] = str;

          Debug("R",index, str);

          if (index == 0) { // COMMAND
            if (strcmp(str ,"A")==0)
            {
              // ACK
              
            }
            if (strcmp(str ,"S")==0) cmd = NODE_CMD_SET;
            if (strcmp(str ,"R")==0) cmd = NODE_CMD_READ;
            if (strcmp(str ,"W")==0) cmd = NODE_CMD_WRITE;
          }  if (index == 1) { // COMMAND
            if (strcmp(str ,"D")==0) mode = NODE_CMD_MODE_D;
            if (strcmp(str ,"A")==0) mode = NODE_CMD_MODE_A;
          } 
          else  if (index == 2) { // COMMAND
           
            pin = atoi(str);
          }
      else  if (index == 3) { // COMMAND
           
            value = atoi(str);
          }

         
          index++;
       }
  Debug("CMD",cmd,mode, pin,value);

          

      
  }
 }
/*
CLOUD_ON_WRITE(127) { 

  web_time = param[0].asLong();
  Log("TIME ",web_time);
}
*/

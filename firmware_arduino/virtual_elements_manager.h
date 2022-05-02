/*
 * Created by marco cecchini
 *
 */

#include "config.h"
//#include "virtual_elements.h"

#include <MemoryFree.h>

#define MAX_VARS 36

//extern char in_buffer[MAX_RECEIVE_BUFFER]; 
class VirtualElementManager
{
 //   VirtualElement* list[MAX_VARS];
    int count=0;
    String id;
    Stream* serial;
  //  char mem[MAX_RECEIVE_BUFFER]; 
    char in_buffer[MAX_RECEIVE_BUFFER]; 
    int mem_len=0;
  
    int  in_buffer_len=0;
    
    bool fromWeb;

    int incomingByte = 0;
  
    //String in_buffer="123456789123456789123456789";

  
public:
  VirtualElementManager(const char* id,Stream* serial,bool fromWeb):serial(serial),id(id),fromWeb(fromWeb){
    /// full_str="";
     
   }
 
  // ===============================
  /*

  Var_Bool *addVarBool(int pin,bool startValue=false,int eprom_address=-1) {
       Var_Bool *sw = new Var_Bool(pin,eprom_address);
       Add(sw);
       if (eprom_address==-1)
          sw->set(startValue);
      return sw;
  }

 Var_String *addVarString(int pin,const String& startValue="") {
      Var_String *sw = new Var_String(pin);
       Add(sw);
       if (startValue!="")
         sw->set(startValue);
      return sw;
  }

  Var_Real *addVarReal(int pin,float startValue=0,int eprom_address=-1) {
      Var_Real *sw = new Var_Real(pin,eprom_address);
       Add(sw);
       if (eprom_address==-1)
          sw->set(startValue);

      return sw;
  }
  
  VirtualElement* Add(VirtualElement *ele){
    if (count == MAX_VARS)
      Serial.println("TOO VARS");
     ele->serial=serial; 
     ele->fromWeb=fromWeb;
    list[count++] = ele;
    ele->start();
    return ele;
  }
  VirtualElement *Find(int pin)
  {
      for(int i=0;i<this->count;i++)
        if (this->list[i]->pin == pin) return list[i];
      return NULL;
  }
  */

 void Process(char *buffer,int len)
 { 
        //Debug(id,"<" ,len);


       // if ( str.endsWith("\n"))
       //       str = str.substring(0,str.length()-1); // tolgo \n e |
        
      //   if ( str.endsWith("|"))
       //      str = str.substring(0,str.length()-1);
        
        // if (str.startsWith(F("CMD PING_REQ"))) {
          //  COMMAND(F("PING_ACQ"));
        // }
    
         // if (str.startsWith("vw")) {
         if (buffer[0] == 'v' && buffer[1] == 'w')
         {
              char num[4];
              int num_len;
              
            // Debug("<<" , str);
             
             int i = -1;
             for( i=3;i<len;i++)
             {
                if (buffer[i] == 32 || buffer[i] == 0 ) break;
                else num[num_len++] = buffer[i] ;
                
             }
             // Debug("idx" , i );
             
            
              num[num_len] = '\0';
              int  pin;
              pin = atoi(num);

             BlynkParam pars(buffer+i+1, len-i);
          
             
             Debug(id, " << " ,pin ,"=",  pars.asString());
                 
           //  int idx = str.indexOf(" ",3);
           //  int pin = str.substring(3,idx).toInt();
           //  String _s=str.substring(idx+1);
    
         //    Debug("W" , pin , _s );
    
          //  BlynkParamAllocated pars(_s.length());
          //  pars.add(_s);
    
        
          //   BlynkParam pars(mem, 0, sizeof(mem));
          
           //   pars.add(_s);
              
          //   Debug("PIN2" , pin , pars.asInt());
           //  Debug("WD" , pin , pars.asString());

          //  Blynk.virtualWriteBinary(pin,buffer+i+1,len-i-1);
    /*
              VirtualElement *ele = Find(pin);
              if (ele!=NULL)
              {
              //  Debug("WD" , pin , pars.asString(),ele->pin);
                 ele->OnCloudWrite(pars);
              }
              else
                 Warn(id,F("pin not found ") , pin);
                 */
                
             //   Debug("..");
         // pars.
            BlynkParam pars1(buffer+i+1,len-i);
            
            VirtualReq req;
            req.pin = pin;

          // BlynkParam pars1("pppp",4);
          
            GetVWriteHandler(pin)(req, pars);
            
          }
          if (buffer[0] == 'v' && buffer[1] == 'r')
          {
            
              char num[4];
              int num_len;
              
             //Debug("<<" , str);
             int i = -1;
             for( i=3;i<len;i++)
             {
                if (buffer[i] == 32) break;
                else num[num_len++] = buffer[i] ;
                
             }
              num[num_len] = '\0';
              int  pin;
              pin = atoi(num);
              
           
           //  int pin = str.substring(3).toInt();
          
           //  Debug("vr " , pin );
    
           // VirtualElement *ele = Find(pin);
          //    if (ele!=NULL)
            //      ele->OnCloudAskValue();
                
            //VirtualReq req;
           // req.pin = pin;
          //  GetVReadHandler(pin)(req);
          
            
          }
      
   
  
  }


  void fast_tick()
  {

    // Debug(id,"..");

    while (serial->available() > 0 ) 
    {
      incomingByte = serial->read();
     // Serial.flush();
      //String c = String((char)incomingByte);

     // if (incomingByte == '\0') incomingByte= '|';

     // if (id =="MA")
      ///Debug (id, " ", incomingByte," l:",in_buffer_len," m:",freeMemory(),fromWeb ? "w":"n");

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
    
void tick()
  {
    fast_tick();

  /*
     for(int i=0;i<this->count;i++)
    {
        list[i]->tick();
    }
    */
  }
} ;

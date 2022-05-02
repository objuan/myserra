/*
 * Circuits4you.com
 * Reading and Writing String to EEPROM Example Code
 * Oct 2018
 */

// 4 KB (4096 bytes) on the ATmega1280 and ATmega2560

#include <EEPROM.h>

void writeString(int add,String data);
String read_String(int add);
String read_String(int add,int max);

void setup11() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 // EEPROM.begin(512);
  String data = "Hello World";

  Serial.print("Writing Data:");
  Serial.println(data);

  writeString(10, data);  //Address 10 and String type data
  delay(10);
}

void loop11() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(10);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(1000);
}

void writeString(int add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
 // EEPROM.commit();
}


String read_String(int add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

String read_String(int add,int max)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500 && len<max)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

// Basic serial communication with ESP8266
// Uses serial monitor for communication with ESP8266
//
//  Pins
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266
//

#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2, 3); // RX | TX

/* 
 *  MODO
 *  AT+CWMODE=1      Network Device (client)
 *            2    Access Point (AP)
 *            3 BOTH 
 *            
 *            ex: AT+CWSAP="IGARDEN","alicepi1",2,3    access point aperto
 *            
 *    AT+CWJAP – Connect to AP         AT+CWJAP="VIOFILIALI","alicepi1" 

 *  LIST IN AREA
 *  AT+CWLAP , quello attuale AT+CWSAP?
 *  
 *  SETTO IP LOCALTE AP
 *  
 *  AT+CIPAP="192.168.1.1" 

 IP LOACALE 
    AT+CIPAP?

DHCP per AP
  AT+CWDHCP=0,1

 *  CONNEXT
 *  AT+CWJAP="VIOFILIALI","alicepi1"
 *     WIFI CONNECTED
      WIFI GOT IP
      OK  
    IP
    AT+CIFSR

    AT+CIPSTO

    SERVER
    AT+CIPMUX=1
    AT+CIPSERVER=1,80
*/
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }

    // Start the software serial for communication with the ESP8266
    ESPserial.begin(9600);  

    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
}

void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( ESPserial.available() )   {  
      Serial.write( ESPserial.read() );
      }
    
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  
      char ch = Serial.read();
       Serial.print(ch);
      ESPserial.write( ch );
      }
}

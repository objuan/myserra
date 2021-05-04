//Time stamped datalogger onto SD Card 
//@vmfoo - 7/19/2014

//
//#define DEBUG
#define SOFT_SERIAL

//#define USE_HUMIDITY
//#define USE_RTC
//#define USE_SD
#define USE_WIFI
#define _DEBUG
// ---------- CONFIG -----------

//DS, change this to match your SD shield or module;

#define sd_chipSelect  4 

// RTC pin
#define DHT11_PIN 4

//WI-FI
#ifdef USE_WIFI
#include <SoftwareSerial.h>

#define BUFFER_SIZE 512
//#define BUFFER_SIZE 256

#define SSID  "VIOFILIALI"      // change this to match your WiFi SSID
#define PASS  "alicepi1"  // change this to match your WiFi password
#define PORT  "8080"           // using port 8080 by default

char buffer[BUFFER_SIZE];
char cmd[64];

SoftwareSerial sserial(2,3);  // use pins 7, 8 for software serial 

#ifdef SOFT_SERIAL
#define dbg Serial
#define esp sserial    // use Serial for debug
#else
#define esp Serial
#define dbg sserial    // use Serial for debug
#endif

#endif

// ---------------------
 
//The RTC Library needs Wire
#ifdef USE_RTC
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
#endif

#ifdef USE_SD
//The SDlibrary needs SPI
#include <SPI.h>
#include "SD.h"
//Some SD Card code borrowed from Adafruit library examples
// set up variables using the SD utility library functions:

File dataFile;
#define LOGFILE "datalog.txt"
#endif

#ifdef USE_HUMIDITY
//library to read the temp/humid sensor
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
#include "dht11.h"
dht11 DHT;
#endif

//---------

#ifdef USE_WIFI

char *getString(int id){
  return cmd;
}


// By default we are looking for OK\r\n
char OKrn[] = "OK\r\n";
byte wait_for_esp_response(int timeout, char* term=OKrn) {
  unsigned long t=millis();
  bool found=false;
  int i=0;
  int len=strlen(term);
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while(millis()<t+timeout) {
    if(esp.available()) {
      buffer[i++]=esp.read();
      if(i>=len) {
        if(strncmp(buffer+i-len, term, len)==0) {
          found=true;
          break;
        }
      }
    }
  }
  buffer[i]=0;
  #ifdef _DEBUG
  if (found)
  {    dbg.print("<- OK:");
      dbg.print(buffer);
       dbg.print("->");
  }
  else
  {
    dbg.print("<- NO:");
      dbg.print(buffer);
       dbg.print("->");
  }
  #endif
  return found;
}

bool read_till_eol() {
  static int i=0;
  if(esp.available()) {
    buffer[i++]=esp.read();
    if(i==BUFFER_SIZE)  i=0;
    if(i>1 && buffer[i-2]==13 && buffer[i-1]==10) {
      buffer[i]=0;
      i=0;
      #ifdef _DEBUG
      dbg.print(buffer);
      #endif
      return true;
    }
  }
  return false;
}

bool read_dbg_till_eol() {
  static int i=0;
  if(dbg.available()) {
    buffer[i++]=dbg.read();
    if(i==BUFFER_SIZE)  i=0;
    if(i>1 && buffer[i-2]==13 && buffer[i-1]==10) {
      buffer[i]=0;
      i=0;
      dbg.print(buffer);
      return true;
    }
  }
  return false;
}


void serve_homepage(int ch_id) {
  String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\nRefresh: 5\r\n";

  String content="";
  // output the value of each analog input pin
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    content += "analog input ";
    content += analogChannel;
    content += " is ";
    content += sensorReading;
    content += "<br />\n";       
  }

  header += "Content-Length:";
  header += (int)(content.length());
  header += "\r\n\r\n";
  esp.print("AT+CIPSEND=");
  esp.print(ch_id);
  esp.print(",");
  esp.println(header.length()+content.length());
  if(wait_for_esp_response(2000, "> ")) {
    esp.print(header);
    esp.print(content);
  } else {
    esp.print("AT+CIPCLOSE=");
    esp.println(ch_id);
  }
}

#define AT 0
#define AT_CWMODE 1
#define AT_RST 2

void setupWiFi() {
  // try empty AT command

  // ciclo sui comandi
  /*for(int i=0;i<100;i++)
  {
     esp.println(getString(0));
     wait_for_esp_response(2000);
  }
  */
  
  esp.println("AT");
  wait_for_esp_response(2000);

  // set mode 1 (client)
  esp.println("AT+CWMODE=1");
  wait_for_esp_response(2000);  

  // reset WiFi module
  esp.print("AT+RST\r\n");
  wait_for_esp_response(1500);
  delay(3000);

 dbg.println("connect .. ");
 
  // join AP
  esp.print("AT+CWJAP=\"");
  esp.print(SSID);
  esp.print("\",\"");
  esp.print(PASS);
  esp.println("\"");

  
  // this may take a while, so wait for 5 seconds
  wait_for_esp_response(10000);

  dbg.println("done .. ");
  
  esp.println("AT+CIPSTO=30");  
  wait_for_esp_response(2000);

  // start server
  esp.println("AT+CIPMUX=1");
  wait_for_esp_response(2000);
  
  esp.print("AT+CIPSERVER=1,"); // turn on TCP service
  esp.println(PORT);
  wait_for_esp_response(4000);
  
    
}

#endif

// =================================================

void setup() {
   Serial.begin(9600); 

#ifdef USE_WIFI
   esp.begin(9600);
 #endif

  Serial.println("Initializing igarder");

#ifdef USE_WIFI
  // wi-fi
  setupWiFi();

  // print device IP address
  #ifdef _DEBUG
  dbg.print("device ip addr:");
  #endif
  esp.println("AT+CIFSR");
  wait_for_esp_response(1000);

#endif

 #ifdef USE_HUMIDITY
  //Initialize the Sensor
  
  Serial.println("Starting Temp and Humidity Sensor");
 // dht.begin();
#endif

#ifdef  USE_SD
  Serial.println("Starting SDCard reader and card");

  pinMode(sd_chipSelect, OUTPUT);
  digitalWrite(sd_chipSelect, HIGH);
   
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(sd_chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card OK");

  Serial.println("Opening logfile for write.");
  // Open up the file we're going to log to!
  dataFile = SD.open(LOGFILE, FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening log file");
    // Wait forever since we cant write data
    while (1) ;
  }
  
 #endif 

#ifdef USE_RTC
  Serial.println("Starting Real Time Clock");
  Wire.begin();
  RTC.begin();
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  //uncomment this once and upload. Then comment it out and upload again
  //This will set the time the first time you upload it and if you don't upload again with it commented out it will 
  //reset the clock to the time the code was compliled each time.
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date &amp; time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  DateTime now = RTC.now();
  Serial.print("Unixtime: ");
  Serial.println(now.unixtime());
  
 #endif 
}

void loop(){
#ifdef USE_RTC
  DateTime now = RTC.now();
  /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */
#endif
  
  /*char temp[6]; //2 int, 2 dec, 1 point, and \0
  char hum[6];  
  char msg[13];
  
  //get the temp/humid into chars to format
  ftoa(temp,readTemp());
  ftoa(hum,readHumidity());
  
  //Compile a comma delimited string to send to the log
  sprintf(msg,"%s,%s",temp, hum);
  logThis(msg);  
  delay(3000); 
  */

/*
  dbg.print("Time: ");
  unsigned long time = millis();
  //prints time since program started
  dbg.println(time);
  // wait a second so as not to send massive amounts of data
  delay(1000);
  
   return;
   */

#ifdef USE_WIFI
  int ch_id, packet_len;
  char *pb;  
  if(read_till_eol()) {
      dbg.println(buffer);
      
    if(strncmp(buffer, "+IPD,", 5)==0) {
      // request: +IPD,ch,len:data
      sscanf(buffer+5, "%d,%d", &ch_id, &packet_len);
      if (packet_len > 0) {
        // read serial until packet_len character received
        // start from :
        pb = buffer+5;
        while(*pb!=':') pb++;
        pb++;
        if (strncmp(pb, "GET /", 5) == 0) {
          wait_for_esp_response(1000);
          #ifdef _DEBUG
            dbg.println("-> serve homepage");
          #endif
          serve_homepage(ch_id);
        }
      }
    }
  }
#endif
// -------------
#ifdef USE_HUMIDITY
  readTempHumidity();
  
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);

  
 #endif
 
 delay(1000);
}


void logThis(char* logmessage){
 /* char message[120];
  DateTime now = rtc.now();
  long epoch = now.unixtime();
  int Year = now.year();
  int Month = now.month();
  int Day = now.day();
  int Hour = now.hour();
  int Minute = now.minute();
  int Second = now.second();
  sprintf(message, "%ld,%d/%d/%d %02d:%02d:%02d,%s",epoch,Year,Month,Day,Hour,Minute,Second,logmessage );
  //Write the entry to the log file and console
  dataFile.println(message);
  dataFile.flush();
  // print to the serial port too:
  Serial.println(message);
  */
}


#ifdef USE_HUMIDITY
void readTempHumidity(){
 /// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
#ifdef DEBUG
    long time1 = mills();
#endif
  /*
   int chk;
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  } 
*/
#ifdef DEBUG
    long time2 = mills();
    Serial.print("Call Time:\t"); 
    Serial.println(time2-time1); 
#endif
}
#endif

/*
int ftoa(char *a, float f)  //translates floating point readings into strings
{
  int left=int(f);
  float decimal = f-left;
  int right = decimal *100; //2 decimal points
  if (right > 10) {  //if the decimal has two places already. Otherwise
    sprintf(a, "%d.%d",left,right);
  } else { 
    sprintf(a, "%d.0%d",left,right); //pad with a leading 0
  }
}
*/


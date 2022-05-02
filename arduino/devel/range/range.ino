/*
 * HY-SRF05 Test
 *
 * Exercises the ultrasonic range finder module and prints out the current measured distance
 * VCC - connect to 5V
 * GND - connect to ground
 * TRIG - connect to digital pin 12.  Can be any digital pin
 * ECHO - connect to digital pin 13.  Can be any digital pin
 * OUT - Not connected
 */
const int TRIG_PIN = A1;
const int ECHO_PIN = A0;
float temp_In_C = 20.0;  // Can enter actual air temp here for maximum accuracy or read with sensor
float speed_Of_Sound;          // Calculated speed of sound based on air temp
float distance_Per_uSec;      // Distance sound travels in one microsecond at that temp

//===============================================================================
//  Initialization
//=============================================================================== 
void setup() {
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  // Formula to calculate speed of sound in meters/sec based on temp
  speed_Of_Sound = 331.1 +(0.606 * temp_In_C);  
  // Calculate the distance that sound travels in one microsecond in Centimeters
  distance_Per_uSec = speed_Of_Sound / 10000.0;
  Serial.begin(9600);
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  float duration, distanceCm, distanceIn, distanceFt;
 
  digitalWrite(TRIG_PIN, HIGH);       // Set trigger pin HIGH 
  delayMicroseconds(10);              // Hold pin HIGH for 10 uSec
  digitalWrite(TRIG_PIN, LOW);        // Return trigger pin back to LOW again.
  duration = pulseIn(ECHO_PIN,HIGH);  // Measure time in uSec for echo to come back.
 
  // convert the time data into a distance in centimeters, inches and feet
  duration = duration / 2.0;  // Divide echo time by 2 to get the time for the sound to travel in one direction
  distanceCm = duration * distance_Per_uSec;
  //istanceIn = distanceCm / 2.54;
  //distanceFt = distanceIn / 12.0;
   
  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(duration, 0);
    Serial.print("uSec, ");
    Serial.print(distanceCm);
    Serial.print("cm,  ");
    //S/erial.print(distanceIn,0);
    //Serial.print("in, ");
    //Serial.print(distanceFt,1);
    //Serial.print("ft, ");
    Serial.println();
  }
  delay(1000);  // Delay between readings
}

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-relay
 */

// constants won't change
const int RELAY_PIN = 2;  // the Arduino pin, which connects to the IN pin of relay

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  
  // initialize digital pin 9 as an output.
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  
  Serial.println("ok");
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(RELAY_PIN, HIGH);
  //delay(200);
  //digitalWrite(RELAY_PIN, LOW);
  //delay(500);
}

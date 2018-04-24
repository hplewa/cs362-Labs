/*
 * Hubert Plewa - 658280400
 * Lab 1 - Get started with Arduino
 * Description - 
 * Written for the UNO.
 * Expecting LEDs on pins 13(optional), 12, and 8.
 * This code sets pins 13, 12, 8 as output.
 * It activates, waits, deactivates, waits the 3 pins in descending order.
 * References - https://www.arduino.cc/en/Tutorial/Blink
 *              https://www.arduino.cc/en/Tutorial/AnalogWriteMega
 *              
 */

void setup() {
  //Using onboard LED, and 2 digital pins in descending order
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  //Onboard LED turns on then off
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
  
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(1000);
  
}

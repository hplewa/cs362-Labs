/*
 * Hubert Plewa - 658280400
 * Lab 5 - Multiple inputs and outputs
 * Description - 
 * Written for the UNO.
 * Requirements, 10k pot, photoresistor, passive buzzer, 4 LEDs
 * Using pins 13, 12, 8, 7 for the LEDs
 * Using pin 2 for the passive buzzer
 * Using Analog pin 0 for photoresistor input
 * Using Analog pin 1 for the 10k pot input
 * 
 *         --- 3.3V 
 * 10k pot --- A1
 *         --- Ground
 * 
 * References - https://www.youtube.com/watch?v=PLRkk5dYxcs
 *            - http://playground.arduino.cc/Learning/PhotoResistor
 *            - http://learn.adafruit.com/photocells
 *               
 */
/*

/* Simple test of the functionality of the photo resistor

Connect the photoresistor one leg to pin 0, and pin to +5V
Connect a resistor (around 10k is a good value, higher
values gives higher readings) from pin 0 to GND. (see appendix of arduino notebook page 37 for schematics).

----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/

const int lightPin = A0;  //define a pin for Photo resistor
const int numLEDs = 4;
const int ledPins[numLEDs] = {13, 12, 8, 7};
const int photoResistorDivisor = 1024/(numLEDs+1);
const int potentiometerPin = A1;
const int buzzerPin = 2;

void setup()
{
    pinMode(lightPin, INPUT);
    int i;
    for(i = 0; i < numLEDs; i++){
      pinMode(ledPins[i], OUTPUT);
    }
    pinMode(potentiometerPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);  //Begin serial communcation
    //delay(1000);
}


int getLightLevel(int lightPin){
  int prval = analogRead(lightPin);
  int i = prval/photoResistorDivisor; //Reduce the photoresistor value 0-1023 to 0-4
  Serial.println(prval); //Write the value of the photoresistor to the serial monitor.
  Serial.println(i); //Write the value of the photoresistor to the serial monitor.
  //Serial.println();
  return i;
}

void activateLEDs(int lightLevel){
  int i;
  for(i = 0; i < numLEDs; i++){
    digitalWrite(ledPins[i], LOW);
  }
  for(i = numLEDs-1; i >= lightLevel; i--){
    digitalWrite(ledPins[i], HIGH);
  }
}

void activateBuzzer(){
  double pot = analogRead(potentiometerPin);
  pot = pot * 1.5; //adjust levels for the 3.3v potentiometer input
  Serial.println(pot);
  Serial.println();
  tone(buzzerPin, pot);
//  delay(100);
//  noTone(buzzerPin);
//  delay(100);
}
void loop()
{
  int lightLevel = getLightLevel(lightPin);
  activateLEDs(lightLevel);
  activateBuzzer();
  
  delay(100);

}

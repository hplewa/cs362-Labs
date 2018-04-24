/*
 * Hubert Plewa - 658280400
 * Lab 4 - More complicated input
 * Description - 
 * Written for the UNO.
 * Requirements, 10k pot, and an LCD screen, photoresistor
 * Using pins 12, 11, 5, 4, 3, 2 for the LCD display see LiquidCrystal Library below for more information
 * in setting up the LCD screen
 * Using Analog pin 0 for photoresistor input
 * 
 * The LCD screen will print the lighting conditions as read by a photoresistor
 * 
 * 
 * References - http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
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
#include <LiquidCrystal.h>
#include <stdio.h>

int lightPin = A0;  //define a pin for Photo resistor

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
    pinMode(lightPin, INPUT);
    Serial.begin(9600);  //Begin serial communcation
    lcd.begin(16, 2);
    delay(1000);
}

char* level[5] = { "dark", "partially dark", "medium", "partially light", "fully lit" };

int getLightLevel(int lightPin){
  int prval = analogRead(lightPin);
  int i = prval/205; //Reduce the photoresistor value 0-1023 to 0-4
  Serial.println(prval); //Write the value of the photoresistor to the serial monitor.
  Serial.println(i); //Write the value of the photoresistor to the serial monitor.
  Serial.println(level[i]);
  Serial.println();

  return i;
}

void loop()
{
  int i = getLightLevel(lightPin);
  lcd.clear();    
  lcd.write(level[i]); 

  delay(1000);

}

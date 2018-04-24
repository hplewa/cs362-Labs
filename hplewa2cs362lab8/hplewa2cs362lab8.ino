//
/*
 * Hubert Plewa - 658280400
 * Lab 6 - Communication
 * Description - 
 * Written for the UNO.
 * Requirements, 10k pot, and an LCD screen
 * Using pins 12, 11, 5, 4, 3, 2 for the LCD display see LiquidCrystal Library below for more information
 * in setting up the LCD screen
 * 
 * Using the Serial Monitor for input.
 * 
 * Upon starting, the user is prompted for a date "mm/dd/yyyy".
 * 
 * After a valid date is provided, the user is asked to input a time "hh/mm/ss".
 * 
 * The hours range from 0-23 rather than using AM/PM for simplicity.
 * 
 * After both the date and time are entered, that information is given
 * to the TimeLib.h library which will set the time on the arduino to
 * reflect the user's choice.
 * 
 * The date and time will be displayed on the LCD screen and updated every second.
 * 
 * The TimeLib library handles the logic for counting up.
 * 
 * 
 * References - http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
 *              https://www.arduino.cc/en/Serial/ReadBytesUntil#.UwYy6_ldV8E
 *              https://www.arduino.cc/en/Guide/Libraries#toc4
 *              http://playground.arduino.cc/Code/Time#.UwYyQPldV8E
 *              
 *              Add this library
 *              **https://github.com/PaulStoffregen/Time** 
  */
/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll

*/

// include the library code:
#include <LiquidCrystal.h>
#include <TimeLib.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int b1 = 2;
const int b2 = 3;
time_t start;
time_t eSecs;
int buttonState = 2;

//Returns the time since t
time_t elapsed(){
  time_t e = now()-start;
  Serial.print("We have been waiting for ");
  Serial.print(e);
  Serial.println(" seconds");
  return e;
}

//Sets the time to now
void updateTime(){
  start = now();
}

boolean isButtonPressed(int b){
  boolean pressed = false;
  if(digitalRead(b)){
    while(digitalRead(b)){} //Wait for release
    pressed = true;
  }
  return pressed;
}

void doButton2(){
  buttonState = 2;
  time_t e = elapsed();
  if(e != eSecs){ //Update LCD if seconds changed
    eSecs = e;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Waiting for");
    lcd.setCursor(0,1); 
    lcd.print(e);
    lcd.print(" sec");
  }
}

void doButton1(){
  buttonState = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Interrupt received!");
  lcd.setCursor(0,1);
  lcd.print("Press button 2 to continue");

  Serial.println("Interrupt received! Press button 2 to continue");
}

void waitMode(){
  if(buttonState == 2){
    while(!digitalRead(b1)){
      doButton2();
    }
    doButton1();
  }
}

void interruptMode(){
  if(buttonState == 1){
    while(!isButtonPressed(b2)){} //Wait for Button2
    updateTime();
    doButton2();
  }
}

void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  
  updateTime();
  delay(1000);
}

void loop() {
  //If we are in waiting mode
  waitMode();

  //If we are in interrupt mode
  interruptMode();
}

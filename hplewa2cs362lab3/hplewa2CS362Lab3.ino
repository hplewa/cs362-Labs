//
/*
 * Hubert Plewa - 658280400
 * Lab 3 - LCD scroll
 * Description - 
 * Written for the UNO.
 * Requirements, 10k pot, and an LCD screen
 * Using pins 12, 11, 5, 4, 3, 2 for the LCD display see LiquidCrystal Library below for more information
 * in setting up the LCD screen
 * 
 * The LCD screen will output my name on the first row and
 * a favorite quote on the second row. The quote on the second row
 * will be scrolling across the row from right to left so its 
 * entirety can be displayed.
 * 
 * 
 * References - http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
 *               
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

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  delay(1000);
}


void loop() {
  //First row entry with padding spaces added to offset the quote
  char* name = "Hubert Plewa                            ";

  const int nameLength = strlen(name);
  
  char* quote = "If you can't beat them, arrange to have them beaten. ";
  const int quoteLength = strlen(quote);
    
  //Current position to start copying the quote from
  int pos = 0;
  while(1){
    lcd.clear();
    lcd.print(name);
    char* quoteToCat = (char*)malloc(quoteLength * sizeof(char));
    for(int i = 0; i < quoteLength; i++){
      quoteToCat[i] = '\0';
    }

    //Copy the quote starting from each starting position 0 - length
    for(int i = 0; i < 16; i++){
      int position = (pos + i) % quoteLength;
      quoteToCat[i] = quote[position];
    }
    quoteToCat[quoteLength] = '\0';
    pos = (pos + 1) % quoteLength;
    lcd.print(quoteToCat);

    free(quoteToCat);
    delay(200);
  }
}


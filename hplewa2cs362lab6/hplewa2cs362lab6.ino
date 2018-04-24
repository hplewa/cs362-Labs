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
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define TIME_MSG_LEN 11 // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER 'T' // Header tag for serial time sync message
#define TIME_REQUEST 7 // ASCII bell character requests a time sync message 

const int dateLength = 10;
const int timeLength = 8;

int isValidDate(char* date){
  if(strlen(date) != dateLength){
    return 0; 
  }

  //Return flag
  int valid = 1;
  int i;
  const int numDigits = 8;
  const int digitPositions[numDigits] = {0,1,3,4,6,7,8,9};
  //Check if there are digits in the right places
  for (i = 0; i < numDigits; i++) {
    int pos = digitPositions[i];
    //Valid characters in date {0-9}
    if (date[pos] < '0' || date[pos] >'9') {
      valid = 0;
      break; 
    }
  }

  const int numBreaks = 2;
  const int breakPositions[2] = {2,5};
  //Check if there are breaks in the right places
  for (i = 0; i < numBreaks; i++) {
    int pos = breakPositions[i];
    //Valid breaks
    if (date[pos] != '/') {
      valid = 0;
      break; 
    }
  }
  
  char month[2];
  strncpy(month, date, 2);
  month[2] = '\0';
  int m = atoi(month);
  if(m > 12 || m < 1){
    Serial.println("mm: 01-12");
    valid = 0;
  }
  
  char day[2];
  strncpy(day, date+3, 2);
  day[2] = '\0';
  int d = atoi(day);
  if(d > 31 || d < 1){
    Serial.println("dd: 01-31");
    valid = 0;
  }
  
  char year[4];
  strncpy(year, date+6, 4);
  year[4] = '\0';
  int y = atoi(year);
  if(y < 1970){
    Serial.println("yyyy: 1970-9999");
    valid = 0;
  }

  //February checking
  if(m == 2){
    if(d > 29){
      Serial.println("02/1-29/yyyy");
      valid = 0;
    }
    if(d == 29){
      if(y % 4 != 0 ){
        Serial.println("02/1-29/(yyyy % 4 == 0)");
        valid = 0;
      }
    }
  }
  
  return valid;
}




void buildDate(char* date){
  int i = 0;

  int incomingByte = 0;   // for incoming serial data

  while(!isValidDate(date)){
    Serial.flush();
    i = 0;
    // send data only when you receive data:
    int avail;
    Serial.println("Enter a date: mm/dd/yyyy");
    while(!(avail=Serial.available())) {}

    Serial.readBytesUntil("\n", date, dateLength);

    date[dateLength] = '\0';
  }
  date[dateLength] = '\0';

}


/*
 *
 */
int isValidTime(char* myTime){
  if(strlen(myTime) != timeLength){
    return 0;
  }

  //Return flag
  int valid = 1;
  int i;
  const int numDigits = 6;
  const int digitPositions[numDigits] = {0,1,3,4,6,7};
  //Check if there are digits in the right places
  for (i = 0; i < numDigits; i++) {
    int pos = digitPositions[i];
    //Valid characters in date {0-9}
    if (myTime[pos] < '0' || myTime[pos] >'9') {
      valid = 0;
      break; 
    }
  }

  const int numBreaks = 2;
  const int breakPositions[2] = {2,5};
  //Check if there are breaks in the right places
  for (i = 0; i < numBreaks; i++) {
    int pos = breakPositions[i];
    //Valid breaks
    if (myTime[pos] != '/') {
      valid = 0;
      break; 
    }
  }
  
  char hour[2];
  strncpy(hour, myTime, 2);
  hour[2] = '\0';
  int h = atoi(hour);
  if(h > 23 || h < 0){
    Serial.println("hh: 00-23");
    valid = 0;
  }
  
  char minute[2];
  strncpy(minute, myTime+3, 2);
  minute[2] = '\0';
  int m = atoi(minute);

  if(m > 59 || m < 0){
    Serial.println("mm: 00-59");
    valid = 0;
  }

  char second[2];
  strncpy(second, myTime+6, 2);
  second[2] = '\0';
  int s = atoi(second);
  if(s > 59 || s < 0){
    Serial.println("ss: 00-59");
    valid = 0;
  }
  
  return valid;
}


void buildTime(char* myTime){

  int i = 0;
  int incomingByte = 0;   // for incoming serial data

  while(!isValidTime(myTime)){
    Serial.flush();
    i = 0;
    // send data only when you receive data:
    int avail;
    Serial.println("Enter a time: hh/mm/ss");
    while(!(avail = Serial.available())){}
    Serial.readBytesUntil("\n", myTime, timeLength);

    myTime[timeLength] = '\0';
  }
  myTime[timeLength] = '\0';
}

void printNow(){
  time_t t = now();
  int hr = hour(t);          // returns the hour for the given time t
  int min = minute(t);        // returns the minute for the given time t
  int sec = second(t);        // returns the second for the given time t
  int dy = day(t);           // the day for the given time t
  int mnth = month(t);         // the month for the given time t
  int yr = year(t);          // the year for the given time t  Serial.print("Date: ");

  Serial.println();
  Serial.print("Date: ");
  Serial.print(mnth);
  Serial.print("/");  
  Serial.print(dy);  
  Serial.print("/");  
  Serial.print(yr);  

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Date: ");
  lcd.print(mnth);
  lcd.print("/");
  lcd.print(dy);
  lcd.print("/");
  lcd.print(yr);

  Serial.println();
  Serial.print("Time: ");
  Serial.print(hr);
  Serial.print("/");  
  Serial.print(min);  
  Serial.print("/");  
  Serial.print(sec);
  Serial.println();

  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(hr);
  lcd.print("/");  
  lcd.print(min);  
  lcd.print("/");  
  lcd.print(sec); 
}


void buildSetTime(char* date,char* myTime){
  char buf[dateLength];
  strncpy(buf, myTime, 2);
  int hr = atoi(buf);
  strncpy(buf, myTime+3, 2);
  int min = atoi(buf);
  strncpy(buf, myTime+6, 2);
  int sec = atoi(buf);
  strncpy(buf, date+3, 2);
  int day = atoi(buf);
  strncpy(buf, date, 2);
  int mnth = atoi(buf);
  strncpy(buf, date+6, 4);
  int yr = atoi(buf);
  setTime(hr,min,sec,day,mnth,yr);
}

void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Refer to");
  lcd.setCursor(0,1);
  lcd.print("Serial Monitor");
  Serial.begin(9600);
  
  char date[dateLength];
  date[dateLength] = '\0';
  
  char myTime[timeLength];
  myTime[timeLength] = '\0';
  buildDate(date);
  buildTime(myTime);

  buildSetTime(date, myTime);


  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  printNow();
  delay(1000);

}

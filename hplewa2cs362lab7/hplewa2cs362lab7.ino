/*
 * Hubert Plewa - 658280400
 * Partner: Robert Hickok
 * Lab 7 - Arduino to Arduino Communication
 * Description - 
 * Written for the UNO.
 * Requirements - 2 LEDs, 2 buttons, 2 arduino UNO boards
 * For each board, button on pin 2, LED on pin 4
 * Connect pin 0 from board A to pin 1 from board B
 * Connect pin 1 from board A to pin 0 from board B
 * 
 * References - https://www.arduino.cc/en/Serial/ReadBytesUntil#.UwYy6_ldV8E
 *              https://www.arduino.cc/en/Guide/Libraries#toc4
 *              https://forum.arduino.cc/index.php?topic=99731.0
 *              http://www.arduino.cc/en/Tutorial/Button
 */


const int buttonPin = 2;
const int ledPin = 4;

const int bufSize = 2;
char buf[bufSize];

int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

//Writing a message to Serial based on button status
//Message will be read up by the other board
void writeSerial(){
  if(digitalRead(buttonPin) == HIGH){
    Serial.write("1");
  }
  else{
    Serial.write("0");
  }
}

//Reading a message from the other board through Serial
//Sets the LED on if button on the other board is pressed
void readSerial(){
  buf[0] = Serial.read();
  buf[1] = '\0';
  //Serial.println(buf[0]);
  
  if(buf[0] == '1'){
    state = (state + 1) % 2;
  }

  digitalWrite(ledPin, state);
}

void loop() {
  writeSerial();
  readSerial();
  
  //delay(100);

}

//
/*
 * Hubert Plewa - 658280400
 * Lab 2 - Input and Output
 * Description - 
 * Written for the UNO.
 * Using 2 switches as buttons on pins 2 for decrement, and 4 for increment
 * Using 3 LEDs to represent a 3-bit binary number
 * Bit 0 for LED on pin 7, bit 1 on pin 8, bit 2 on pin 12
 * 
 * This code sets pins 13, 12, 8 as output.
 * Pins 2, and 4 as input.
 * 
 * The LEDs are arranged in an array to represent a binary number where
 * absence light means 0, and presence of light means 1.
 * 
 * When a  button is pressed, an internal counter is incremented or decremented accordingly,
 * and modulo'd by 8 to keep the value between 0 and 7.
 * 
 * Decrementing from 0 wraps the value around to 7.
 * 
 * Incrementing from 7 wraps the value around to 0.
 * 
 * 
 * References - https://forum.arduino.cc/index.php?topic=99731.0
 *              http://www.arduino.cc/en/Tutorial/Button
 *               
 */
const int decButtonPin = 2;
const int incButtonPin = 4;

const int bits = 3;
int ledPins[bits] = {7, 8, 12};

int incButtonState = 0;
int decButtonState = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(incButtonPin, INPUT);
  pinMode(decButtonPin, INPUT);

  pinMode(13, OUTPUT);

  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Read the increment button
  incButtonState = digitalRead(incButtonPin);
  if(incButtonState == HIGH){
    digitalWrite(13, HIGH);

    //Increment the counter
    counter = (counter + 1) % 8;
    
    //Wait for the button to be released
    while(digitalRead(incButtonPin) == HIGH) { }
  }
  else{    
    digitalWrite(13, LOW);
  }
  
  //Read the decrement button
  decButtonState = digitalRead(decButtonPin);
  if(decButtonState == HIGH){
    digitalWrite(13, HIGH);
    
    //Decrement the counter
    counter = (counter - 1) % 8;
    
    //Wait for the button to be released
    while(digitalRead(decButtonPin) == HIGH) { }
  }
  else{    
    digitalWrite(13, LOW);
  }
  
  //Convert the counter to LED binary
  int i = 0; //LED index
  int pos = 1; //Bit position to read
  for(i = 0; i < bits; i++){
     if(counter & pos){ //Checking the bit of counter with pos
        digitalWrite(ledPins[i], HIGH);
     }
     else{
        digitalWrite(ledPins[i], LOW);
     }
     //Shift the masking bit to the left to read the next bit
     pos = pos << 1;
  }
  
  //Pause to eliminate jittery presses
  delay(100);
}

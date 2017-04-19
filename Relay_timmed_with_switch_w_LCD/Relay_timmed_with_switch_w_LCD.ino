
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // initialize the library with the numbers of the interface pins

const int buttonPin = 12;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
const int relayDelay= 2000; // time to delay between relay startup and shutdown
int relay1 = 8; //relay1 is power-on, Trigger signal-high level is valuable;
int relay2 = 9; // relay2 is power-on, Trigger signal-high level is valuable;
int relay3 = 10;
int relay4 = 11;


// Variables will change:
int ledState = digitalRead(ledPin);         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = digitalRead(buttonPin);   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  pinMode(relay1,OUTPUT); // Define port attributes as output； 
  pinMode(relay2,OUTPUT); 
  pinMode(relay3,OUTPUT); 
  pinMode(relay4,OUTPUT); 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Powering up...");
  // set initial LED state
  
  digitalWrite(ledPin, ledState);
  
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
    
  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

     if (buttonState == HIGH) {
        ledState = !ledState;
         digitalWrite(ledPin, ledState);
         lcd.setCursor(0, 1);
       
        digitalWrite(relay4,LOW);
        if(digitalRead(relay4) == LOW){
           lcd.write("OFF");
           lcd.setCursor(4, 1);
         }
         delay(relayDelay);   
         
        digitalWrite(relay3,LOW);  
        if(digitalRead(relay3) == LOW){
           lcd.write("OFF");
           lcd.setCursor(8, 1);
         }
         delay(relayDelay); 
        
       digitalWrite(relay2,LOW);
       if(digitalRead(relay2) == LOW){
           lcd.write("OFF");
           lcd.setCursor(12, 1);
         }
         delay(relayDelay); 
         
        digitalWrite(relay1,LOW);
        if(digitalRead(relay1) == LOW){
           lcd.write("OFF"); 
         }
         
       } else if (buttonState == LOW) {
        ledState = !ledState;
         digitalWrite(ledPin, ledState);
        lcd.setCursor(0, 0);
         lcd.write("SW1 SW2 SW3 SW4");
        lcd.setCursor(0, 1);
        digitalWrite(relay1,HIGH);
         if(digitalRead(relay1) == HIGH){
           lcd.write("ON ");
           lcd.setCursor(4, 1);
         }
         delay(relayDelay);   
         
        digitalWrite(relay2,HIGH);  
         if(digitalRead(relay2) == HIGH){
           lcd.write("ON ");
           lcd.setCursor(8, 1);
         }         
         delay(relayDelay);   
         
        digitalWrite(relay3,HIGH);
           if(digitalRead(relay3) == HIGH){
           lcd.write("ON ");
           lcd.setCursor(12, 1);
         }
         delay(relayDelay);   
         
        digitalWrite(relay4,HIGH);
        if(digitalRead(relay4) == HIGH){
           lcd.write("ON ");
         }
       } //end of if
      
    }
  }
  

       
       
  lcd.setCursor(0, 0);
  lcd.write("SW1 SW2 SW3 SW4");

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}


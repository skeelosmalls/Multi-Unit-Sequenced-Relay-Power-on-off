/*
Issues to work through
- how do I get the secondary to remote shutdown in reverse order.
- maybe send value identifying a number to the relay box (example  1, 2, 3, 3 - Can have 1 start then trigger 2 then
- switch for identifying if there is a remote secondary to the box. and If there is then send signal for remote secondary to shutdown first.


*/


int s = 0; // another space for trigger. 
int masterRelay = 1;  //switch for main or secondary. (secondary looks to receive on input 3 before triggering) k

int relaySend = 2; // This is signal TO another Relay Device in Chain.
int relayReceive = 3; // This is signal from another Relay in Chain.

int relay1 = 4;  // relays in Unit
int relay2 = 5; 
int relay3 = 6;
int relay4 = 7;

int relay5 = 8; 
int relay6 = 9; 
int relay7 = 10;
int relay8 = 11;

int switchPin = 12;    // the number of the power switch

int sensorPin = A0;    // potentiometer for Delay Time
int sensorValue = 0;

// Variables will change:
int switchState;             // the current reading from the input pin
int lastswitchState = digitalRead(switchPin);   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(switchPin, INPUT); 
  pinMode(relay1,OUTPUT); // Define port attributes as output； 
  pinMode(relay2,OUTPUT); 
  pinMode(relay3,OUTPUT); 
  pinMode(relay4,OUTPUT); 
  pinMode(relay5,OUTPUT); 
  pinMode(relay6,OUTPUT); 
  pinMode(relay7,OUTPUT); 
  pinMode(relay8,OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(switchPin);
  sensorValue = analogRead(sensorPin) * 10;  
 //  int delayValue =  relayDelay; 
  int delayValue =  sensorValue; 
  Serial.println(sensorValue);

  // If the switch changed, due to noise or pressing:
  if (reading != lastswitchState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != switchState) {
      switchState = reading;
      
     if (switchState == LOW) {
        digitalWrite(relay8,LOW);
            delay(delayValue);
        digitalWrite(relay7,LOW);
            delay(delayValue);
        digitalWrite(relay6,LOW);
            delay(delayValue);
        digitalWrite(relay5,LOW);
            delay(delayValue);
        digitalWrite(relay4,LOW);
            delay(delayValue);
        digitalWrite(relay3,LOW);  
            delay(delayValue);  
        digitalWrite(relay2,LOW);
         delay(delayValue); 
        digitalWrite(relay1,LOW);  
     } else if (switchState == HIGH) {
        digitalWrite(relay1,HIGH);
            delay(delayValue);    
        digitalWrite(relay2,HIGH);  
            delay(delayValue);    
        digitalWrite(relay3,HIGH);
            delay(delayValue);    
        digitalWrite(relay4,HIGH);
            delay(delayValue);    
        digitalWrite(relay5,HIGH);
            delay(delayValue);    
        digitalWrite(relay6,HIGH);
            delay(delayValue);    
        digitalWrite(relay7,HIGH);
            delay(delayValue);    
        digitalWrite(relay8,HIGH);
       } //end of if
      
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastswitchState:
  lastswitchState = reading;
}

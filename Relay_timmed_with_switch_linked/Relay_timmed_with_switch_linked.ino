/*
Issues to work through
 - how do I get the secondary to remote shutdown in reverse order.
 - maybe send value identifying a number to the relay box (example  1, 2, 3, 3 - Can have 1 start then trigger 2 then
 - switch for identifying if there is a remote secondary to the box. and If there is then send signal for remote secondary to shutdown first.
 
 
 */
int relayReceive = 0; // This is signal from another Relay in Chain.
int relaySend = 1; // This is signal TO another Relay Device in Chain.

int relay1 = 2;  // relays in Unit
int relay2 = 3; 
int relay3 = 4;
int relay4 = 5;

int relay5 = 6; 
int relay6 = 7; 
int relay7 = 8;
int relay8 = 9;

int switchPin = 10;   // the number of the power switch

int masterRelayUnit = 11;  // If OFF Unit looks to receive on input 3 before starting  otherwise start.
int lastRelayUnit = 12; // Last Unit = If true this unit starts the shutdown process and then preceeds reversed shutdown through the other units. 


int sensorPin = A0;    // potentiometer for Delay Time
int sensorValue = 0;

// Variables will change:
int changeLastRelay;
int changeSecondaryRelay;

int switchState;             // the current reading from the input pin
int lastswitchState = digitalRead(switchPin);   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // the debounce time; increase if the output flickers

int masterCounter = 0;
int masterRelayPrev = digitalRead(masterRelayUnit);
int stopSecondary = 0;
int incomingByte = 0;   // for incoming serial data

void setup() {
  pinMode(switchPin, INPUT); 

  pinMode(lastRelayUnit,INPUT); 
  pinMode(masterRelayUnit,INPUT); 

  pinMode(relaySend,OUTPUT); 
  pinMode(relayReceive,OUTPUT); 

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
  //int reading1 = digitalRead(lastRelayUnit);
  int masterRelay = digitalRead(masterRelayUnit);


  sensorValue = analogRead(sensorPin) * 10;  
  int delayValue =  sensorValue; 

  // If the switch changed, due to noise or pressing:
  if (reading != lastswitchState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if(masterRelay != masterRelayPrev){
      Serial.write("Master = ");
      if(masterRelay == HIGH){
        Serial.write("H");
      } 
      else { 
        Serial.write("L");
      }
      Serial.print(" | Counter=");
      Serial.println(masterCounter);

      masterRelayPrev = masterRelay;
      masterCounter++;

    }


    if (Serial.available() > 0) {
      int incomingByte = Serial.read();
      // do something different depending on the character received.  
      // The switch statement expects single number values for each case;
      // in this exmaple, though, you're using single quotes to tell
      // the controller to get the ASCII value for the character.  For
      // example 'a' = 97, 'b' = 98, and so forth:
      Serial.print("reading = ");
      Serial.println(incomingByte);
/*
      switch (incomingByte) {
      case 1:
        // statements
        
        break;
      case 2:
        // statements
        
        break;
      default: 
        // statements
        
        break;
      }
 */
    }




    if (reading != switchState) {
      switchState = reading;

      if (masterRelay == HIGH || stopSecondary == true){
        // Serial.print("Master unit ");
        if (switchState == LOW) {
          //Serial.println("Stopping");


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

          if(masterRelay == HIGH){
            //now trigger secondary unit to go
            Serial.println("Shutdown Secondary");
          } 
          else {
            Serial.println("Shutdown Master");
          }
        } 
        else if (switchState == HIGH) {
          //Serial.println("Starting");


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

          if(masterRelay == HIGH){
            //now trigger secondary unit to go
            Serial.println("Master = Started");
          } 
          else {
            Serial.println("Secondary = Started");
          }

        } //end of if
      } 
      else {
        //if( relayReceive == ""){
        //shutdown main unit
        Serial.println("not master unit");
        //}

      }

    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastswitchState:
  lastswitchState = reading;
}






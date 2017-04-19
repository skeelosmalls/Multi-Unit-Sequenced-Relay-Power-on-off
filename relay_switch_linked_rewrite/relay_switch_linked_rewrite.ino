/*
Issues to work through
 - MAKE A SOLO SWITCH TO DISABLE ALL THIS

 */
int debug = 0; // If "0" debug is off, if set to "1" then all debug info is displayed in serial window.

int relayPins[] = { 
  2, 3, 4, 5, 6, 7, 8, 9 };
int relayPinCount = 8;

int switchPin = 10;   // the number of the power switch

int masterSwitch = 11;  // If OFF Unit looks to receive on input 3 before starting  otherwise start.
int lastRelayUnit = 12; // Last Unit = If true this unit starts the shutdown process and then preceeds reversed shutdown through the other units. 


int sensorPin = A0;    // potentiometer for Delay Time
int sensorValue = 0;

// Variables will change:
int changeLastRelay;
int master;

int switchState;             // the current reading from the input pin
int lastswitchState = digitalRead(switchPin);   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // the debounce time; increase if the output flickers

int masterCounter = 0;
int masterRelayPrev = digitalRead(masterSwitch);

int incomingByte = 0;   // for incoming serial data
int thisPin;
void setup() {  // ---------------------------- Setup Pins

  Serial.begin(9600);
  for (int thisPin = 0; thisPin < relayPinCount; thisPin++)  {
    pinMode(relayPins[thisPin], OUTPUT);  
  } 

  pinMode(switchPin, INPUT); 
  pinMode(lastRelayUnit,INPUT); 
  pinMode(masterSwitch,INPUT); 
  Serial.begin(9600);
  if(debug == 1){       // DEBUG ----------------------
    Serial.print("masterSW: ");
    if(digitalRead(masterSwitch) == HIGH){ 
      Serial.println("ON");
    } 
    else {
      Serial.println("OFF");
    }
  }
}


char Read() {

  // String content = "";
  char ch = Serial.read();
  // content.concat(character);
  delay (10);
  //if (ch == 0) {
  return ch;
  //}

}

void relaystart(int *relayPins, int thisPin, int relayPinCount, int delayValue, int debug){

  for (int thisPin = 0; thisPin < relayPinCount; thisPin++) { 
    // turn the pin on:
    digitalWrite(relayPins[thisPin], HIGH);  
    //Serial.print("Relay #");
    //Serial.print(thisPin+1);
    //Serial.println(" started"); 
    delay(delayValue); 

  }
  if(debug == 1){       // DEBUG ----------------------
    Serial.println("Unit Started --------");
  }

}

void relaystop(int *relayPins, int thisPin, int relayPinCount, int delayValue, int debug){

  for (int thisPin = relayPinCount - 1; thisPin >= 0; thisPin--) { 
    // turn the pin on:
    digitalWrite(relayPins[thisPin], LOW);
    //Serial.print("Relay #");
    //Serial.print(thisPin+1);
    //Serial.println(" Stopped"); 
    delay(delayValue);
  }
  if(debug == 1){       // DEBUG ----------------------
    Serial.println("Unit Stopped -------");
  }

}

void loop(){

  int reading = digitalRead(switchPin);
  //int reading1 = digitalRead(lastRelayUnit);
  int masterRelay = digitalRead(masterSwitch);
  if (masterRelay == HIGH){ 
    master = 1; 
  } 
  else { 
    master = 0;
  }
  sensorValue = analogRead(sensorPin) * 10;  
  int delayValue =  sensorValue; 
  char* Show;


  while (Serial.available() > 0) // Don't read unless
    // there you know there is data
  {
    char serialIN = Read();
    if(serialIN >= '0' && serialIN <= '9') // is this an ascii digit between 0 and 9?
    {
      if(debug == 1){       // DEBUG ----------------------
        Serial.print("masterSW = ");
        if (master == 1){
          Show = "on";
        } 
        else { 
          Show = "off";
        }
        Serial.println(Show);
      }
      //Serial.print("ch = ");
      //Serial.println(ch);
      switch (serialIN) {
      case '1': // slave start
        if (master == 0){
          relaystart(relayPins, thisPin, relayPinCount, delayValue, debug);
          if(debug == 1){       // DEBUG ----------------------
            Serial.println("SLAVE: Serial In Case num one - Slave started");
          }
        }
        break;
      case '8': // master shutdown
        if (master == 1){
          relaystop(relayPins, thisPin, relayPinCount, delayValue, debug);
          if(debug == 1){       // DEBUG ----------------------
            Serial.println("MASTER: Serial In Case num eight - Master Shutdown");
          }
        } 
        break;
      case '9': // slave shutdown then initiate master shutdown
        if (master == 0){
          relaystop(relayPins, thisPin, relayPinCount, delayValue, debug);
          if(debug == 1){       // DEBUG ----------------------
            Serial.println("SLAVE: Serial In Case num nine - Slave stopped and initiate master shutdown");
          }
          Serial.println(8);
        } 
        break;
      default: 
        break;
        if(debug == 1){       // DEBUG ----------------------
          Serial.println("NOT Valid Case number");
        }
      }
      delay(1);
    }

  }


  // If the switch changed, due to noise or pressing:
  if (reading != lastswitchState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Serial.println("In debounced loop");

    if (reading != switchState) {
      switchState = reading;

      if(debug == 1){       // DEBUG ----------------------
        if (master == 1){
          Serial.print("MASTER: ");
        }
        else {
          Serial.print("SLAVE: ");
        }
        Serial.print("switch changed to ");
        if (digitalRead(switchPin) == HIGH) {
          Serial.println("on");
        } 
        else{ 
          Serial.println("off");
        }

      }


      if (switchState == LOW) {
        if(debug == 1){       // DEBUG ----------------------
          Serial.println("Initiate Stop Sequence");
        }
        if (master == 1){    // DEBUG ----------------------
          if(debug == 1){
            Serial.println("MASTER: initiate slave shutdown");
          }
          Serial.println(9);
        } 

      } 
      else if (switchState == HIGH) {
        if(debug == 1){       // DEBUG ----------------------
          Serial.println("Initiate Start Sequence");
        }
        if (master == 1){
          relaystart(relayPins, thisPin, relayPinCount, delayValue, debug);
          Serial.println(1);
        } 
      }

    }
  }
  lastswitchState = reading;
  delay(1);
}




















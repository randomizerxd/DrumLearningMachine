//Set variables for BluetoothSettings  
int Received=0;
int ModeReceived = 0;
int TempoReceived = 0;
int BeatReceived = 0;
int Back = 0;
int count = 3;

//Sequence Mode variables
/***Piezo Vibration Sensor Pin Numbers***/ 
const int hihatSensorPin = A5;
const int snareSensorPin = A4;
const int kickSensorPin  = A3;
const int crashSensorPin = A2;
const int tomSensorPin   = A1;

/***LED Strip Pin Numbers***/
//Use PWM and analog pins//
//From left to right on the breadboard

const int hihatGREENPin = 10;
const int hihatREDPin   = 9;
const int hihatBLUEPin  = 6;

const int snareGREENPin = 5;
const int snareREDPin   = 3;
const int snareBLUEPin  = A6;

const int kickGREENPin  = A7;
const int kickREDPin    = A8;
const int kickBLUEPin   = A9;

const int crashGREENPin = A10;
const int crashREDPin   = A11;
const int crashBLUEPin  = A12;

const int tomGREENPin   = A13;
const int tomREDPin     = A14;
const int tomBLUEPin    = A15;


/***Variables to store the value read from the sensor pin***/
int hihatSensorReading = LOW;
int snareSensorReading = LOW;
int kickSensorReading  = LOW;
int crashSensorReading = LOW;
int tomSensorReading   = LOW;

const int threshold = 200;


void setup() {
  Serial.begin(9600);

  ////Sequence Mode setup pins 
  pinMode(hihatGREENPin, OUTPUT);
  pinMode(hihatREDPin, OUTPUT);
  pinMode(hihatBLUEPin, OUTPUT);
  
  pinMode(snareGREENPin, OUTPUT);
  pinMode(snareREDPin, OUTPUT);
  pinMode(snareBLUEPin, OUTPUT);
  
  pinMode(kickGREENPin, OUTPUT);
  pinMode(kickREDPin, OUTPUT);
  pinMode(kickBLUEPin, OUTPUT);
  
  pinMode(crashGREENPin, OUTPUT);
  pinMode(crashREDPin, OUTPUT);
  pinMode(crashBLUEPin, OUTPUT);
  
  pinMode(tomGREENPin, OUTPUT);
  pinMode(tomREDPin, OUTPUT);
  pinMode(tomBLUEPin, OUTPUT);
  
  
  pinMode(hihatSensorPin, INPUT);
  pinMode(snareSensorPin, INPUT);
  pinMode(kickSensorPin, INPUT);
  pinMode(crashSensorPin, INPUT);
  pinMode(tomSensorPin, INPUT);

  //Initialize all LED strips to OFF
  analogWrite(hihatGREENPin, 0);
  analogWrite(hihatREDPin, 0);
  analogWrite(hihatBLUEPin, 0);
  
  analogWrite(snareGREENPin, 0);
  analogWrite(snareREDPin, 0);
  analogWrite(snareBLUEPin, 0);
  
  analogWrite(kickGREENPin, 0);
  analogWrite(kickREDPin, 0);
  analogWrite(kickBLUEPin, 0);
  
  analogWrite(crashGREENPin, 0);
  analogWrite(crashREDPin, 0);
  analogWrite(crashBLUEPin, 0);
  
  analogWrite(tomGREENPin, 0);
  analogWrite(tomREDPin, 0);
  analogWrite(tomBLUEPin, 0);
  ////Receive settings from App thru Bluetooth
  BluetoothSettings(); 
}

void loop() {

  if (Back == 33)
  {
    ////Receive settings from App thru Bluetooth
    BluetoothSettings(); 
  }
  else
  {
    ////Choose mode (Demo = 7, Sequence = 8, PlayAlong = 9)
    if (ModeReceived == 7) //Demo
    {
       
    }
    else 
    if (ModeReceived == 8) //Sequence
    {
      if (BeatReceived == 1)
      {
        snare();
      }
      else
      if (BeatReceived == 2)
      {
        
      }
      else
      if (BeatReceived == 3)
      {
        
      }
    }
    else 
    if (ModeReceived == 9) // PlayAlong
    {
      
    }
    Bluetooth_CheckBackButton();
  }  
}

/*********************************************************************/
/**************************Demo Functions*****************************/
/*********************************************************************/


/*********************************************************************/
/************************Sequence Functions***************************/
/*********************************************************************/
void hihat() {
  analogWrite(hihatREDPin, 255);
  while( analogRead(hihatSensorPin) < threshold) { } //Do nothing until hihat sensor passes threshold
  hitConfirmation(hihatGREENPin, hihatREDPin);
  delay(1000);
}

void snare() {
  analogWrite(snareREDPin, 255);
  while( analogRead(snareSensorPin) < threshold) 
  {
    /*if( Back == 33)
    {
      Bluetooth_CheckBackButton();
    }*/
  }//{Bluetooth_CheckBackButton();} //Do nothing until snare sensor passes threshold
  hitConfirmation(snareGREENPin, snareREDPin);
  delay(1000);
}

void kick() {
  analogWrite(kickREDPin, 255);
  while( analogRead(kickSensorPin) < threshold) { } //Do nothing until kick sensor passes threshold
  analogWrite(kickREDPin, 0);
  hitConfirmation(kickGREENPin, kickREDPin);
  delay(1000);
}

//This function turns on the lights on the hihat and kick and waits for the user to hit both of them
void hihat_kick() {
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold) && 
  ((kickSensorReading = analogRead(kickSensorPin)) < threshold) ) { 
  }                                         //While hihat && kick below threshold, do nothing
  if(((hihatSensorReading) > threshold) && ((kickSensorReading) > threshold)) {
    hitConfirmation(hihatGREENPin, hihatREDPin);
    hitConfirmation(kickGREENPin, kickREDPin);
  } else
  if( hihatSensorReading >= threshold ) {    //If the hihat hit
    hitConfirmation(hihatGREENPin, hihatREDPin);  
    while( analogRead(kickSensorPin) < threshold) { } //Do nothing until snare is hit
    hitConfirmation(kickGREENPin, kickREDPin);
  } else
  if ( kickSensorReading >= threshold ) { //If the snare sensor was pushed
    hitConfirmation(kickGREENPin, kickREDPin);
    while( analogRead(hihatSensorPin) < threshold) { } //Do nothing until hihat sensor is pushed
    hitConfirmation(hihatGREENPin, hihatREDPin);
  }
  delay(1000); 
}

//This function turns on the lights on the hihat and snare and waits for the user to hit both of them
void hihat_snare() {
  analogWrite(hihatREDPin, 255);
  analogWrite(snareREDPin, 255);
  while( ((hihatSensorReading = doubleAnalogRead(hihatSensorPin)) < threshold) && ((snareSensorReading = doubleAnalogRead(snareSensorPin)) < threshold) ) {  
    Serial.print(hihatSensorReading);
    Serial.print(" ");
    Serial.println(snareSensorReading);
  }
  Serial.print("hihatSensorReading : ");
  Serial.print(hihatSensorReading);
  Serial.print("...");
  Serial.print("snareSensorReading : ");
  Serial.print(snareSensorReading);
  Serial.println();
  if( ( (hihatSensorReading) > threshold) && ( (snareSensorReading) > threshold) ) {
    hitConfirmation(hihatGREENPin, hihatREDPin);
    hitConfirmation(snareGREENPin, snareREDPin);
  } else
  if( hihatSensorReading >= threshold ) {    //If the hihat hit
    hitConfirmation(hihatGREENPin, hihatREDPin); 
    while( (snareSensorReading = analogRead(snareSensorPin)) < threshold) { } //Do nothing until snare is hit
    hitConfirmation(snareGREENPin, snareREDPin);
  }
  else if ( snareSensorReading >= threshold ) { //If the snare sensor was pushed
    hitConfirmation(snareGREENPin, snareREDPin); 
    while( analogRead(hihatSensorPin) < threshold) { } //Do nothing until hihat sensor is pushed
    hitConfirmation(hihatGREENPin, hihatREDPin);
  }
  delay(1000); 
}

void hitConfirmation(int greenPin, int redPin) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    delay(125);
    analogWrite(greenPin, 0);
}

int doubleAnalogRead(int pin) {
  int reading = 0;
  reading = analogRead(pin);
  delayMicroseconds(6000);
  reading = analogRead(pin);
  delayMicroseconds(6000);

  return reading;  
}

/*********************************************************************/
/***********************PlayAlong Functions***************************/
/*********************************************************************/


//Receive settings from App thru Bluetooth
void BluetoothSettings()
{
  while (count > 0)
  {
    if(Serial.available()>0)
    {
      Back = 0;
      Received = Serial.read();
      
      if (count == 3)
      {
        BeatReceived = Received;
      }
      if (count == 2)
      {
        //needed so FX board doesn't loop sound
        TempoReceived = Received - 250;
      }
      if (count == 1)
      {
        ModeReceived = Received;
      }

      count = count - 1;
    }
  }
  count = 3;
  Serial.println("BluetoothSettings Done");
}

void Bluetooth_CheckBackButton()
{
  //Serial.println("Back Checked");
  if(Serial.available()>0)
    {
      Back = Serial.read();
      Serial.println("Back Pressed");

    }
}

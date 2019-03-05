// TopLevel
// Board: DUE

/*********************************************************************/
/*****************************Variables*******************************/
/*********************************************************************/
int Received=0;
int ModeReceived = 0;
int TempoReceived = 0; //tempo in bpm
int BeatReceived = 0;
int Back = 0;
/* 
 *  To understand the proprietary bluetooth protocol:
 *    See TopLevel/README.md
 */
int count = 3;

int tempo = 0; //tempo in ms ... 'tempo = 60000 / TempoReceived;'
int adj_tempo = 0; //tempo adjusted for 250ms delay ... 'adj_tempo = tempo - 250;'

/***Piezo Vibration Sensor Pin Numbers***/ 
const int hihatSensorPin = A5;
const int snareSensorPin = A4;
const int kickSensorPin  = A3;
const int crashSensorPin = A2;
const int tomSensorPin   = A1;

/***LED Strip Pin Numbers***/
//Use PWM and analog pins//
//From left to right on the breadboard

const int hihatGREENPin = 13;
const int hihatREDPin   = 12;
const int hihatBLUEPin  = 11;

const int snareGREENPin = 10;
const int snareREDPin   = 9;
const int snareBLUEPin  = 8;

const int kickGREENPin  = 7;
const int kickREDPin    = 6;
const int kickBLUEPin   = 5;

const int crashGREENPin = 4;
const int crashREDPin   = 3;
const int crashBLUEPin  = 2;

const int tomGREENPin   = A9;
const int tomREDPin     = A10;
const int tomBLUEPin    = A11;


/***Variables to store the value read from the sensor pin***/
int hihatSensorReading = LOW;
int snareSensorReading = LOW;
int kickSensorReading  = LOW;
int crashSensorReading = LOW;
int tomSensorReading   = LOW;

const int threshold = 200; 


void setup() {
  Serial.begin(9600);

  setupLEDpins();
  setupVibrationSensorPins();
  initializeLEDstrips();

  ////Receive settings from App thru Bluetooth
  BluetoothSettings(); 
}

void loop() {

  if (Back == 201)
  {
    ////Receive settings from App thru Bluetooth
    BluetoothSettings(); 
  }
  else
  {
    ////Choose mode (Demo = 101, Sequence = 102, PlayAlong = 103)
    if (ModeReceived == 101) //Demo
    {
       
    }
    else 
    if (ModeReceived == 102) //Sequence
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
    if (ModeReceived == 103) // PlayAlong
    {
      
    }
    Bluetooth_CheckBackButton();
  }  
}

/*********************************************************************/
/**************************Setup Functions****************************/
/*********************************************************************/
void setupLEDpins() {
  pinMode(hihatGREENPin, OUTPUT);
  pinMode(hihatREDPin,   OUTPUT);
  pinMode(hihatBLUEPin,  OUTPUT);
  
  pinMode(snareGREENPin, OUTPUT);
  pinMode(snareREDPin,   OUTPUT);
  pinMode(snareBLUEPin,  OUTPUT);
  
  pinMode(kickGREENPin, OUTPUT);
  pinMode(kickREDPin,   OUTPUT);
  pinMode(kickBLUEPin,  OUTPUT);
  
  pinMode(crashGREENPin, OUTPUT);
  pinMode(crashREDPin,   OUTPUT);
  pinMode(crashBLUEPin,  OUTPUT);
  
  pinMode(tomGREENPin, OUTPUT);
  pinMode(tomREDPin,   OUTPUT);
  pinMode(tomBLUEPin,  OUTPUT);
}

void setupVibrationSensorPins() {
  pinMode(hihatSensorPin, INPUT);
  pinMode(snareSensorPin, INPUT);
  pinMode(kickSensorPin,  INPUT);
  pinMode(crashSensorPin, INPUT);
  pinMode(tomSensorPin,   INPUT);
}

void initializeLEDstrips() {
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

/*********************************************************************/
/***********************Bluetooth Functions***************************/
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
        TempoReceived = Received;
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

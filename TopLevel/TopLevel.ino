// TopLevel
// Board: chipKIT Max32

/***Set variables for BluetoothSettings***/  
short Received=0;
short ModeReceived = 0;
short TempoReceived = 0; //tempo in bpm
short BeatReceived = 0;
short Back = 0;
/* 
 *  Bluetooth protocol:
 *  App sends data to Arduino via bluetooth
 *  We have rules in place for the information sent.
 *  The app sends one byte of data for each setting.
 *  The first screen contains settings to select the beat, tempo and mode
 *  The first screen sends data in the following order:
 *    1) Beat 2) Tempo 3) Mode
 *  i.   The Beat value received from the app will be:
 *    1, 2, 3, and so on..
 *  ii.  The Tempo value received from the app will be:
 *    40bpm -> 176 bpm
 *  iii. The Mode value received from the app will be:
 *    101 for Demo, 102 for Sequence, and 103 for PlayAlong
 *  
 *  The second screen currently contains a 'back' button and volume control buttons (up and down) for the Demo mode only
 *  The second screen sends data in the following manner:
 *    i.   Send a 201 when the Back button has been pushed
 *    ii.  Send a 211 when the Volume Down button has been pushed
 *    iii. Send a 212 when the Volume Up button has been pushed
 *  
 */
short count = 3;

int tempo = 0; //tempo in ms ... 'tempo = 60000 / TempoReceived;'
int adj_tempo = 0; //tempo adjusted for 250ms delay ... 'adj_tempo = tempo - 250;'

/***Piezo Vibration Sensor Pin Numbers***/ 
const short hihatSensorPin = A5;
const short snareSensorPin = A4;
const short kickSensorPin  = A3;
const short crashSensorPin = A2;
const short tomSensorPin   = A1;

/***LED Strip Pin Numbers***/
//Use PWM and analog pins//
//From left to right on the breadboard

const short hihatGREENPin = 10;
const short hihatREDPin   = 9;
const short hihatBLUEPin  = 6;

const short snareGREENPin = 5;
const short snareREDPin   = 3;
const short snareBLUEPin  = A6;

const short kickGREENPin  = A7;
const short kickREDPin    = A8;
const short kickBLUEPin   = A9;

const short crashGREENPin = A10;
const short crashREDPin   = A11;
const short crashBLUEPin  = A12;

const short tomGREENPin   = A13;
const short tomREDPin     = A14;
const short tomBLUEPin    = A15;


/***Variables to store the value read from the sensor pin***/
short hihatSensorReading = LOW;
short snareSensorReading = LOW;
short kickSensorReading  = LOW;
short crashSensorReading = LOW;
short tomSensorReading   = LOW;

const short threshold = 200;


void setup() {
  Serial.begin(115200);

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

void hitConfirmation(short greenPin, short redPin) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    delay(125);
    analogWrite(greenPin, 0);
}

short doubleAnalogRead(short pin) {
  short reading = 0;
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

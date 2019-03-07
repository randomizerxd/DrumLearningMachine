// Sequence Mode
// Board: chipKIT Max32

//This program will turn on the LED Strips for the hihat, kick and snare
// and use piezo vibration sensors to detect when the drum or cymbal
// has been struck. 

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

const short threshold = 100; 

void setup() {
  Serial.begin(115200);

  setupLEDpins();
  setupVibrationSensorPins();
  initializeLEDstrips(); 

  hihat_snare();
}

void loop() {
  //hihat_kick();
  //hihat();
  //hihat_snare();
  //hihat();
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

void hihat() {
  analogWrite(hihatREDPin, 255);
  while( analogRead(hihatSensorPin) < threshold) { } //Do nothing until hihat sensor passes threshold
  hitConfirmation(hihatGREENPin, hihatREDPin);
  delay(1000);
}

void snare() {
  analogWrite(snareREDPin, 255);
  while( analogRead(snareSensorPin) < threshold) { } //Do nothing until snare sensor passes threshold
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
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold) && ((snareSensorReading = analogRead(snareSensorPin)) < threshold) ) {  
    Serial.print(hihatSensorReading);
    Serial.print(" ");
    Serial.println(snareSensorReading);
  }
  
  averageAnalogRead();
  
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

// Function to "take place" of the while loops in the functions above
void waitFor(bool hihat, bool snare, bool kick) {
  while(hihat){
    
  }
  while(snare) {
    
  }
  while(kick) {
    
  }
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

short averageAnalogRead() {
  short n = 100;
  
  long t0, t;
  float hihatSensorReading_Average = 0;
  float snareSensorReading_Average = 0;
  
  Serial.println("hihatSensorReading | snareSensorReading");
  Serial.print(hihatSensorReading);
  Serial.print(" | ");
  Serial.println(snareSensorReading);

  t0 = micros();
  for (short i = 0; i < n; i++) {
    hihatSensorReading = analogRead(hihatSensorPin);
    snareSensorReading = analogRead(snareSensorPin);
   // if ( hihatSensorReading > 
    hihatSensorReading_Average = hihatSensorReading_Average + hihatSensorReading;
    snareSensorReading_Average = snareSensorReading_Average + snareSensorReading;
    /*
    Serial.print(hihatSensorReading);
    Serial.print(" | ");
    Serial.println(snareSensorReading);
    */
  }
  hihatSensorReading_Average = hihatSensorReading_Average / n;
  snareSensorReading_Average = snareSensorReading_Average / n;
  //time it takes to finish the for loop
  t = micros() - t0;
  Serial.print("hihat_Average: ");
  Serial.println(hihatSensorReading_Average);
  Serial.print("snare_Average: ");
  Serial.println(snareSensorReading_Average);
  Serial.print("t: ");
  Serial.println(t);

  
}



  
 

  
  

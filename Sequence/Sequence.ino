// Sequence Mode
// Board: chipKIT Max32

//This program will turn on the LED Strips for the hihat, kick and snare
// and use piezo vibration sensors to detect when the drum or cymbal
// has been struck. 

/***Piezo Vibration Sensor Pin Numbers***/ 
const short hihatSensorPin = A1;
const short snareSensorPin = A2;
const short kickSensorPin  = A3;
const short crashSensorPin = A4;
const short tomSensorPin   = A5;

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

/***Variables used in the 'averageAnalogRead()' function***/
float hihatSensorReading_Average = 0;
float snareSensorReading_Average = 0;
float kickSensorReading_Average  = 0;

const short threshold = 100; 

void setup() {
  Serial.begin(9600);

  setupLEDpins();
  setupVibrationSensorPins();
  initializeLEDstrips(); 
}

void loop() {

  hihat_snare();
  delay(3000);
  
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
  
  pinMode(kickGREENPin,  OUTPUT);
  pinMode(kickREDPin,    OUTPUT);
  pinMode(kickBLUEPin,   OUTPUT);
  
  pinMode(crashGREENPin, OUTPUT);
  pinMode(crashREDPin,   OUTPUT);
  pinMode(crashBLUEPin,  OUTPUT);
  
  pinMode(tomGREENPin,   OUTPUT);
  pinMode(tomREDPin,     OUTPUT);
  pinMode(tomBLUEPin,    OUTPUT);
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
  analogWrite(hihatREDPin,   0);
  analogWrite(hihatBLUEPin,  0);
  
  analogWrite(snareGREENPin, 0);
  analogWrite(snareREDPin,   0);
  analogWrite(snareBLUEPin,  0);
  
  analogWrite(kickGREENPin, 0);
  analogWrite(kickREDPin,   0);
  analogWrite(kickBLUEPin,  0);
  
  analogWrite(crashGREENPin, 0);
  analogWrite(crashREDPin,   0);
  analogWrite(crashBLUEPin,  0);
  
  analogWrite(tomGREENPin, 0);
  analogWrite(tomREDPin,   0);
  analogWrite(tomBLUEPin,  0);
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
  hitConfirmation(kickGREENPin, kickREDPin);
  delay(1000);
}

//This function turns on the lights on the hihat and kick and waits for the user to hit both of them
void hihat_kick() {
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  Serial.println("ready");
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold) && ((kickSensorReading = analogRead(kickSensorPin)) < threshold) ) { 
  }                                         //While hihat && kick below threshold, do nothing

  averageAnalogRead_hihatkick();
  
  if(((hihatSensorReading_Average) > threshold) && ((kickSensorReading_Average) > threshold)) {
    hitConfirmation_hihatkick(hihatGREENPin, hihatREDPin, kickGREENPin, kickREDPin);
  } else
  if( hihatSensorReading >= threshold ) {    //If the hihat sensor was triggered
    hitConfirmation(hihatGREENPin, hihatREDPin);  
    while( analogRead(kickSensorPin) < threshold) { } //Do nothing until snare is hit
    hitConfirmation(kickGREENPin, kickREDPin);
  } else
  if ( kickSensorReading >= threshold ) { //If the kick sensor was triggered
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
  Serial.println("ready");
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold) && ((snareSensorReading = analogRead(snareSensorPin)) < threshold) ) {  
  }
  
  averageAnalogRead_hihatsnare();
  
  if( ( (hihatSensorReading_Average) > threshold) && ( (snareSensorReading_Average) > threshold) ) {
    hitConfirmation_hihatsnare(hihatGREENPin, hihatREDPin, snareGREENPin, snareREDPin);
  } 
  else if( hihatSensorReading >= threshold ) {    //If the hihat sensor was triggered
    hitConfirmation(hihatGREENPin, hihatREDPin); 
    while( (snareSensorReading = analogRead(snareSensorPin)) < threshold) { } //Do nothing until snare is hit
    hitConfirmation(snareGREENPin, snareREDPin);
  }
  else if ( snareSensorReading >= threshold ) { //If the snare sensor was triggered
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

void hitConfirmation_hihatsnare(short hihatGREENPin, short hihatREDPin, short snareGREENPin, short snareREDPin) {
    analogWrite(hihatREDPin, 0);
    analogWrite(snareREDPin, 0);
    analogWrite(hihatGREENPin, 255);
    analogWrite(snareGREENPin, 255);
    delay(125);
    analogWrite(hihatGREENPin, 0);
    analogWrite(snareGREENPin, 0);
}

void hitConfirmation_hihatkick(short hihatGREENPin, short hihatREDPin, short kickGREENPin, short kickREDPin) {
    analogWrite(hihatREDPin, 0);
    analogWrite(kickREDPin, 0);
    analogWrite(hihatGREENPin, 255);
    analogWrite(kickGREENPin, 255);
    delay(125);
    analogWrite(hihatGREENPin, 0);
    analogWrite(kickGREENPin, 0);
}

//Changes 'hihatSensorReading_Average' and 'snareSensorReading_Average'
void averageAnalogRead_hihatsnare() {
  short n = 500;  //amount of times to read from both hihat and snare
  long t0;        //initial value of t
  long t;         //stores the amount of time it takes to finish the for loop
  short n_hihat = n;    //used to average. n_hihat <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  short n_snare = n;    //used to average. n_snare <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  hihatSensorReading_Average = 0;
  snareSensorReading_Average = 0;
  short hihatSensorReading_tmp = 0; //local variable. Don't change 'hihatSensorReading'
  short snareSensorReading_tmp = 0; //local variable. Don't change 'snareSensorReading'
/*
  Serial.println("Analog reading exceeded threshold");
  Serial.println("hihatSensorReading | snareSensorReading");
  Serial.print("Readings when triggered: ");
  Serial.print(hihatSensorReading);
  Serial.print(" | ");
  Serial.println(snareSensorReading);
*/
  t0 = micros();
  for (short i = 0; i < n; i++) {
     hihatSensorReading_tmp = analogRead(hihatSensorPin);
     snareSensorReading_tmp = analogRead(snareSensorPin);
     if ( hihatSensorReading_tmp > threshold ) {
      hihatSensorReading_Average += hihatSensorReading_tmp;
     }
     else {
      n_hihat--;
     }
     if ( snareSensorReading_tmp > threshold ) {
      snareSensorReading_Average += snareSensorReading_tmp;
     }
     else {
      n_snare--;
     }
    /* 
    Serial.print(hihatSensorReading);
    Serial.print(" | ");
    Serial.println(snareSensorReading);
    */
  }
  /*
  Serial.print(n_hihat);
  Serial.print(" / ");
  Serial.print(n);
  Serial.print(" readings over ");
  Serial.println(threshold);
  
  Serial.print(n_snare);
  Serial.print(" / ");
  Serial.print(n);
  Serial.print(" readings over ");
  Serial.println(threshold);*/
  hihatSensorReading_Average /= n_hihat;
  snareSensorReading_Average /= n_snare;
  
  //time it takes to finish the for loop
  t = micros() - t0;/*
  Serial.print("hihat_Average: ");
  Serial.println(hihatSensorReading_Average);
  Serial.print("snare_Average: ");
  Serial.println(snareSensorReading_Average);
  Serial.print("t: ");
  Serial.print(t);
  Serial.println(" microseconds");*/
}

//Changes 'hihatSensorReading_Average' and 'kickSensorReading_Average'
void averageAnalogRead_hihatkick() {
  short n = 500;  //amount of times to read from both hihat and snare
  long t0;        //initial value of t
  long t;         //stores the amount of time it takes to finish the for loop
  short n_hihat = n;    //used to average. n_hihat <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  short n_kick = n;    //used to average. n_kick <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  hihatSensorReading_Average = 0;
  kickSensorReading_Average = 0;
  short hihatSensorReading_tmp = 0; //local variable. Don't change 'hihatSensorReading'
  short kickSensorReading_tmp = 0; //local variable. Don't change 'kickSensorReading'
/*
  Serial.println("Analog reading exceeded threshold");
  Serial.println("hihatSensorReading | kickSensorReading");
  Serial.print("Readings when triggered: ");
  Serial.print(hihatSensorReading);
  Serial.print(" | ");
  Serial.println(kickSensorReading);
*/
  t0 = micros();
  for (short i = 0; i < n; i++) {
     hihatSensorReading_tmp = analogRead(hihatSensorPin);
     kickSensorReading_tmp = analogRead(kickSensorPin);
     if ( hihatSensorReading_tmp > threshold ) {
      hihatSensorReading_Average += hihatSensorReading_tmp;
     }
     else {
      n_hihat--;
     }
     if ( kickSensorReading_tmp > threshold ) {
      kickSensorReading_Average += kickSensorReading_tmp;
     }
     else {
      n_kick--;
     }
    /* 
    Serial.print(hihatSensorReading);
    Serial.print(" | ");
    Serial.println(kickSensorReading);
    */
  }
  /*
  Serial.print(n_hihat);
  Serial.print(" / ");
  Serial.print(n);
  Serial.print(" readings over ");
  Serial.println(threshold);
  
  Serial.print(n_kick);
  Serial.print(" / ");
  Serial.print(n);
  Serial.print(" readings over ");
  Serial.println(threshold);*/
  hihatSensorReading_Average /= n_hihat;
  kickSensorReading_Average /= n_kick;
  
  //time it takes to finish the for loop
  t = micros() - t0;/*
  Serial.print("hihat_Average: ");
  Serial.println(hihatSensorReading_Average);
  Serial.print("kick_Average: ");
  Serial.println(kickSensorReading_Average);
  Serial.print("t: ");
  Serial.print(t);
  Serial.println(" microseconds");*/
}

/******************************************************/
/*                     VARIABLES                      */
/******************************************************/

/***Piezo Vibration Sensor Pin Numbers***/ 
const int hihatSensorPin = A5;
const int snareSensorPin = A4;
const int kickSensorPin  = A3;
const int crashSensorPin = A2;
const int tomSensorPin   = A1;

/***LED Strip Pin Numbers***/
//PWM and analog pins. From left to right on the breadboard
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

void setup() {
  Serial.begin(9600);   //use serial port

  setupLEDpins();
  setupVibrationSensorPins();
  initializeLEDstrips();
}

void loop() {

  /* BLUETOOTH
   *  i.  receive tempo in bpm
   *  ii. convert to ms 
   *        one beat (delay) in ms = (60 / #bpm) * 1000
   *        bpm = (60 / #ms) * 1000
   *        range:  40bpm -> 176bpm
   *                341ms -> 1500ms
   */
   
  /*      i.  turn light red
   *          vibration sensor ready
   *          
   *      ii.  increment totalCount
   *          
   *      iii. if (part is hit at correct time)
   *            then  a. userCount += 1
   *                  b. turn light green
   *            
   *      iv. turn off light
   *      
   */
  
  //rockBeat();
  //discoBeat();
  //reggaetonBeat();
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

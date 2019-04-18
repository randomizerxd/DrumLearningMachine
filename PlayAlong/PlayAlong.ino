/******************************************************/
/*                     VARIABLES                      */
/******************************************************/
//additional comment
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
short hihatSensorReading = LOW;
short snareSensorReading = LOW;
short kickSensorReading  = LOW;
short crashSensorReading = LOW;
short tomSensorReading   = LOW;

const short threshold_hihat = 100; 
const short threshold_snare = 94; 
const short threshold_kick = 130; 

/***Variables used in the 'averageAnalogRead()' function***/
short n = 500;  //amount of times to read from both hihat and snare
long t0;        //initial value of t
long t;         //stores the amount of time it takes to finish the for loop
short n_hihat = n;    //used to average. n_hihat <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
short n_snare = n;    //used to average. n_snare <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
short n_kick = n;    //used to average. n_kick <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
float hihatSensorReading_Average = 0;
float snareSensorReading_Average = 0;
float kickSensorReading_Average  = 0;
short hihatSensorReading_tmp = 0; //local variable. Don't change 'hihatSensorReading'
short snareSensorReading_tmp = 0; //local variable. Don't change 'snareSensorReading'
short kickSensorReading_tmp = 0; //local variable. Don't change 'kickSensorReading'

const short threshold = 200;

/***Variables for the FINAL SCORE***/
int TIME = millis();
int COUNT = 0;
int tempo = 430;

void setup() {
  Serial.begin(9600);   //use serial port

  setupLEDpins();
  setupVibrationSensorPins();
  setupFXPins();
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

void setupFXPins(){
    //Files on Audio FX SoundBoard
  //T00 = hihat
  //T01 = snare
  //T02 = kick
  //T03 = kick and hihat
  pinMode(kickFXPin,    OUTPUT);
  pinMode(snareFXPin,   OUTPUT);
  pinMode(hihatFXPin,   OUTPUT);
  pinMode(hhkickFXPin,  OUTPUT);
  pinMode(hhsnareFXPin, OUTPUT);
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

//Play part of Drumset
void startCheck(int count){
  TIME = millis();  //start count for hits
  //check reading
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(adj_tempo);         //moves on to next file for the appropriate tempo
}

/******************************************************/
/*        FUNCTIONS FOR THE DIFFERENT BEATS           */
/******************************************************/


/******************************************************/
/*                     ROCK BEAT                      */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o-------v----                    */
/******************************************************/   

void rockBeat(){  //Setting LEDs to specific colors/pins
  hihat_kick();
  startCheck(COUNT);

  hihat();
  startCheck(COUNT);

  hihat_snare(); 
  startCheck(COUNT);

  hihat();  
  startCheck(COUNT);
}



/* SEQUENCE CODE */
/******************************************************/

void hihat() {
  analogWrite(hihatREDPin, 255);
  while( analogRead(hihatSensorPin) < threshold_hihat) { } //Do nothing until hihat sensor passes threshold
  hitConfirmation_hihat();
}

void snare() {
  analogWrite(snareBLUEPin, 255);
  while( analogRead(snareSensorPin) < threshold_snare) { } //Do nothing until snare sensor passes threshold
  hitConfirmation_snare();
}

void kick() {
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  while( analogRead(kickSensorPin) < threshold_kick) { } //Do nothing until kick sensor passes threshold
  hitConfirmation_kick();
}

//This function turns on the lights on the hihat and kick and waits for the user to hit both of them
void hihat_kick() {
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  TIME = millis();
  int diffTime = 0;
  int tmpCount = 0;
  while (diffTime < tempo){
    if (((hihatSensorReading = analogRead(hihatSensorPin)) < threshold_hihat) && ((kickSensorReading = analogRead(kickSensorPin)) < threshold_kick)){
      //do nothing if below threshold
    }
    averageAnalogRead_hihatkick(); 
       
    if(((hihatSensorReading_Average) > threshold_hihat) && ((kickSensorReading_Average) > threshold_kick)) {
      tmpCount++;
    } 
    diffTime = millis() - TIME;
  }
  if (tmpCount > 0){
    COUNT++;
  }
}


  

//This function turns on the lights on the hihat and snare and waits for the user to hit both of them
void hihat_snare() {
  analogWrite(hihatREDPin, 255);
  analogWrite(snareBLUEPin, 255);
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold_hihat) && ((snareSensorReading = analogRead(snareSensorPin)) < threshold_snare) ) {  
  }
  
  averageAnalogRead_hihatsnare();
  
  if( ( (hihatSensorReading_Average) > threshold_hihat) && ( (snareSensorReading_Average) > threshold_snare) ) {
    hitConfirmation_hihatsnare();
  } 
  else if( hihatSensorReading >= threshold_hihat ) {    //If the hihat sensor was triggered
    hitConfirmation_hihat(); 
    while( (snareSensorReading = analogRead(snareSensorPin)) < threshold_snare) { } //Do nothing until snare is hit
    hitConfirmation_snare();
  }
  else if ( snareSensorReading >= threshold_snare ) { //If the snare sensor was triggered
    hitConfirmation_snare(); 
    while( analogRead(hihatSensorPin) < threshold_hihat) { } //Do nothing until hihat sensor is pushed
    hitConfirmation_hihat();
  } 
}





/**********************************************************/
/*           Check if Proper Hit Function                 */
/**********************************************************/

int checkCountHit(int startTime, int CountHit){ //should pass in TIME
  int endTime = millis();
  int difference = endTime - startTime;
  
  while(difference < ){
   if (reading > threshold)
      countHit++;
    difference = micros() - start_time;
  }
  Serial.print("Difference in time: ");
  Serial.print(difference);
  
  return CountHit;
}













// down here for now

/******************************************************/
/*                    ROCK V2 BEAT                    */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o--(o)--v----                    */
/******************************************************/

void rockV2Beat(){  
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);  
  playSound(hhkickFXPin);

  analogWrite(hihatREDPin, 255);
  playSound(hihatFXPin);

  analogWrite(hihatREDPin, 255);
  analogWrite(snareBLUEPin, 255);
  playSound(hhsnareFXPin);

  analogWrite(hihatREDPin, 255);
  playSound(hihatFXPin);
//Second loop
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  playSound(hhkickFXPin);

  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  playSound(hhkickFXPin);

  analogWrite(hihatREDPin, 255);
  analogWrite(snareBLUEPin, 255);
  playSound(hhsnareFXPin);

  analogWrite(hihatREDPin, 255);
  playSound(hihatFXPin);
}

/******************************************************/
/*                    DISCO BEAT                      */
/*                   1   2   3   4                    */
/*                   ----x-------x                    */
/*                   o-------v----                    */
/******************************************************/

void discoBeat(){
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 255);
  playSound(kickFXPin);

  analogWrite(hihatREDPin, 255);
  playSound(hihatFXPin);

  analogWrite(snareBLUEPin, 255);
  playSound(snareFXPin);

  analogWrite(hihatREDPin, 255);
  playSound(hihatFXPin);
}

/******************************************************/
/*                   ROCK-YOU BEAT                    */
/*                   1 a 2 a 3 a 4                    */
/*                   ----v-------v                    */
/*                   o-o-----o-o--                    */
/******************************************************/

void rockYou(){  
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 255);
  playSound(kickFXPin);

  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 255);
  playSound(kickFXPin);

  analogWrite(snareBLUEPin, 255);
  playSound(snareFXPin);

  playSound(0);
}

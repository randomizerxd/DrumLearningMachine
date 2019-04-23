/* DESCRIPTION of FUNCTION*/
/* This function will play the beat SET amount of times, 
 * the microcontroller will send the score (correct HITS - amount HITS/amount HITS)
 * to the app and the app will display the score.
 */

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
int count = 0;      //amount of time the part was properly played
int tempo = 60000;
int adj_tempo = tempo-250;
int SET = 4;        //amount of times beat is play before giving a score
int hit_amount = 0; //amount of hits
int score = 0;

void setup() {
  Serial.begin(9600);   //use serial port

  setupLEDpins();
  setupVibrationSensorPins();
  //setupFXPins();
  initializeLEDstrips();
}

void hihat();
void snare();
void kick();
void hihat_kick();
void hihat_snare();

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
  int BEAT = 1;
  for (int i = 0; i < SET; i++){
    if      (BEAT == 1) { rockBeat();   }
    //else if (BEAT == 2) { rockV2Beat(); }
    //else if (BEAT == 3) { discoBeat();  }
    //else if (BEAT == 4) { rockYou();    }
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

  //Initializing pins to 5V so they do NOT play sound
void RESET(){
  analogWrite(hihatREDPin,  0);
  analogWrite(kickREDPin,   0);
  analogWrite(kickGREENPin, 0);
  analogWrite(snareBLUEPin, 0);
}

void calcScore(int count){
  /*  This function calculates score, adjusts tempo
   *  so the beat is played at the proper rate, and 
   *  and resets the lights to turn OFF
   */
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(adj_tempo);         //moves on to next file for the appropriate tempo
  score = (count/hit_amount); //calculation
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
  hihat_kick_PA();
  calcScore(count);
  hit_amount++;

  hihat_PA();
  calcScore(count);
  hit_amount++;

  hihat_snare_PA(); 
  calcScore(count);
  hit_amount++;

  hihat_PA();  
  calcScore(count);
  hit_amount++;
}

/******************************************************/
/*                    ROCK V2 BEAT                    */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o--(o)--v----                    */
/******************************************************/

void rockV2Beat(){
  SET = SET/2;  //because the loop is already twice for this beat
    
  hihat_kick_PA();
  hit_amount++;
  calcScore(count);

  hihat_PA();
  hit_amount++;
  calcScore(count);

  hihat_snare_PA();
  hit_amount++;
  calcScore(count);

  hihat_PA();
  hit_amount++;
  calcScore(count);
//Second loop
  hihat_kick_PA();
  hit_amount++;
  calcScore(count);

  hihat_kick_PA();
  hit_amount++;
  calcScore(count);

  hihat_snare_PA();
  hit_amount++;
  calcScore(count);

  hihat_PA();
  hit_amount++;
  calcScore(count);
}

/******************************************************/
/*                    DISCO BEAT                      */
/*                   1   2   3   4                    */
/*                   ----x-------x                    */
/*                   o-------v----                    */
/******************************************************/

void discoBeat(){
  kick_PA();
  hit_amount++;
  calcScore(count);

  hihat_PA();
  hit_amount++;
  calcScore(count);

  snare_PA();
  hit_amount++;
  calcScore(count);

  hihat_PA();
  hit_amount++;
  calcScore(count);
}

/******************************************************/
/*                   ROCK-YOU BEAT                    */
/*                   1 a 2 a 3 a 4                    */
/*                   ----v-------v                    */
/*                   o-o-----o-o--                    */
/******************************************************/

void rockYou(){  
  kick_PA();
  hit_amount++;
  calcScore(count);

  kick_PA();
  hit_amount++;
  calcScore(count);

  snare_PA();
  hit_amount++;
  calcScore(count);

  calcScore(count);
}




/* SEQUENCE CODE */
/******************************************************/

void hihat_PA() { //done
  analogWrite(hihatREDPin, 255);
  TIME = millis();  //sets start time
  int diffTime = 0;
  int tmpCount = 0;
  while(diffTime < tempo){
    while( analogRead(hihatSensorPin) < threshold_hihat) { } //Do nothing until hihat sensor passes threshold
    if( analogRead(hihatSensorPin) > threshold_hihat) { tmpCount++; }
  }
  if( tmpCount > 0){
    count++;
  }
}

void snare_PA(){ //done
  analogWrite(snareBLUEPin, 255);
  TIME = millis();  //sets start time
  int diffTime = 0;
  int tmpCount = 0;
  while(diffTime < tempo){
    while( analogRead(snareSensorPin) < threshold_snare) { } //Do nothing until snare sensor passes threshold
    if(analogRead(snareSensorPin) > threshold_snare){ tmpCount++; } //if properly hit
  }
  if(tmpCount > 0){
    count++;
  }
}

void kick_PA() { //done
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  TIME = millis();  //dec of tmp variables
  int diffTime = 0;
  int tmpCount = 0;
  while(diffTime < tempo){
    while( analogRead(kickSensorPin) < threshold_kick) { } //Do nothing until kick sensor passes threshold
    if( analogRead(kickSensorPin) > threshold_kick){ tmpCount++; }
  }
  if(tmpCount > 0){
    count++;
  }
}

//This function turns on the lights on the hihat and kick and waits for the user to hit both of them
void hihat_kick_PA() { //done
  analogWrite(hihatREDPin, 255);
  analogWrite(kickREDPin, 255);
  analogWrite(kickGREENPin, 128);
  TIME = millis();
  int diffTime = 0;
  int tmpCount = 0;
  while (diffTime < tempo){ //before tempo (delay) is set to move to the next part
    while (((hihatSensorReading = analogRead(hihatSensorPin)) < threshold_hihat) && ((kickSensorReading = analogRead(kickSensorPin)) < threshold_kick)){
      //do nothing if below threshold
    }
    averageAnalogRead_hihatkick(); //receive average reading of hihat and kick (precision)
       
    if(((hihatSensorReading_Average) > threshold_hihat) && ((kickSensorReading_Average) > threshold_kick)) {
      tmpCount++; //if they're both hit correctly, add 1 to the score.
    } 
    diffTime = millis() - TIME;
  }
  if (tmpCount > 0){
    count++;
  }
}


  

//This function turns on the lights on the hihat and snare and waits for the user to hit both of them
void hihat_snare_PA() {
  analogWrite(hihatREDPin, 255);
  analogWrite(snareBLUEPin, 255);
  TIME = millis();
  int diffTime = 0;
  int tmpCount = 0;
  while (diffTime < tempo){ //before tempo (delay) is set to move to the next part
    while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold_hihat) && ((snareSensorReading = analogRead(snareSensorPin)) < threshold_snare) ) {  
    }
    averageAnalogRead_hihatsnare();
  
    if( ( (hihatSensorReading_Average) > threshold_hihat) && ( (snareSensorReading_Average) > threshold_snare) ) {
      tmpCount++;
    } 
  }
  if(tmpCount > 0){
    count++;
  }
}



/*
 * Changes:
 *    hihatSensorReading_Average
 *    snareSensorReading_Average
 */
void averageAnalogRead_hihatsnare() {
  n = 500;  //amount of times to read from both hihat and snare
  n_hihat = n;    //used to average. n_hihat <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  n_snare = n;    //used to average. n_snare <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  hihatSensorReading_Average = 0;
  snareSensorReading_Average = 0;
  hihatSensorReading_tmp = 0; //local variable. Don't change 'hihatSensorReading'
  snareSensorReading_tmp = 0; //local variable. Don't change 'snareSensorReading'

  t0 = micros();
  for (short i = 0; i < n; i++) {
     hihatSensorReading_tmp = analogRead(hihatSensorPin);
     snareSensorReading_tmp = analogRead(snareSensorPin);
     if ( hihatSensorReading_tmp > threshold_hihat ) {
      hihatSensorReading_Average += hihatSensorReading_tmp;
     }
     else {
      n_hihat--;
     }
     if ( snareSensorReading_tmp > threshold_snare ) {
      snareSensorReading_Average += snareSensorReading_tmp;
     }
     else {
      n_snare--;
     }
  }
  hihatSensorReading_Average /= n_hihat;
  snareSensorReading_Average /= n_snare;
  
  //time it takes to finish the for loop
  t = micros() - t0;
}

/*
 * Changes:
 *    hihatSensorReading_Average
 *    kickSensorReading_Average
 */
void averageAnalogRead_hihatkick() {
  n = 500;  //amount of times to read from both hihat and snare
  n_hihat = n;    //used to average. n_hihat <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  n_kick = n;    //used to average. n_kick <= n. It will be decremented by 1 when sensor readings don't exceed the threshold
  hihatSensorReading_Average = 0;
  kickSensorReading_Average = 0;
  hihatSensorReading_tmp = 0; //local variable. Don't change 'hihatSensorReading'
  kickSensorReading_tmp = 0; //local variable. Don't change 'kickSensorReading'

  t0 = micros();
  for (short i = 0; i < n; i++) {
     hihatSensorReading_tmp = analogRead(hihatSensorPin);
     kickSensorReading_tmp = analogRead(kickSensorPin);
     if ( hihatSensorReading_tmp > threshold_hihat ) {
      hihatSensorReading_Average += hihatSensorReading_tmp;
     }
     else {
      n_hihat--;
     }
     if ( kickSensorReading_tmp > threshold_kick ) {
      kickSensorReading_Average += kickSensorReading_tmp;
     }
     else {
      n_kick--;
     }
  }
  hihatSensorReading_Average /= n_hihat;
  kickSensorReading_Average /= n_kick;
  
  //time it takes to finish the for loop
  t = micros() - t0;
}







/**********************************************************/
/*           Check if Proper Hit Function                 */
/**********************************************************/
/*
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
*/

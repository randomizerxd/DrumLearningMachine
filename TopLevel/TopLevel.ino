// TopLevel
// Board: chipKIT Max32

/***Set variables for BluetoothSettings***/  
short Received      = 0;
short ModeReceived  = 0;
short TempoReceived = 0; //tempo in bpm
short BeatReceived  = 0;
short Back          = 0; //for storing the back code
short VolumeControl = 0; //for storing the volume up or down code
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

/***Piezo Vibration Sensor Pin Numbers***/ 
const short hihatSensorPin = A1;
const short snareSensorPin = A2;
const short kickSensorPin  = A3;
const short crashSensorPin = A4;
const short tomSensorPin   = A5;

/***LED Strip Pin Numbers***/
//Use PWM and analog pins
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

const short threshold_hihat = 140; 
const short threshold_snare = 110; 
const short threshold_kick = 150; 

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

const short BACK_CODE          = 201;
const short VOLUMEDOWN_CODE    = 211;
const short VOLUMEUP_CODE      = 212;
const short DEMOMODE_CODE      = 101;
const short SEQUENCEMODE_CODE  = 102;
const short PLAYALONGMODE_CODE = 103;
const short BEAT1_CODE         =   1;
const short BEAT2_CODE         =   2;
const short BEAT3_CODE         =   3;
const short BEAT4_CODE         =   4;

/******************************* VARIABLES *************************************/
//INITIALIZING PINS AND VARIABLES
short hihatFXPin     = 49;            //set pin 49 to 'hihat' sound
short kickFXPin      = 50;            //set pin 50 to 'kick' sound
short snareFXPin     = 51;            //set pin 51 to 'snare' sound
short hhkickFXPin    = 52;            //set pin 52 to 'hihat' and 'kick' sound
short hhsnareFXPin   = 53;            //set pin 53 to 'hihat' and 'snare' sound

short volUp         = 47;            //set pin 47 to volume-up
short volDown       = 48;            //set pin 48 to volume-down

//Set tempo equal to the tempo received by the app
short tempo     = 0; //Inc = slower & Dec = faster (LIMIT: 350ms to 1500ms)
short adj_tempo = 0; //adjusted tempo to account the file delay
//EXTRA
short eightTempo= 0;   //tempo used for beats with and
short sixTempo  = 0;    //tempo used for beats with sixteenth notes
/*****************************************************************************/



void setup() {
  Serial.begin(9600);

  setupLEDpins();
  setupVibrationSensorPins();
  setupFXPins();
  initializeLEDstrips();

  ////Receive settings from App thru Bluetooth
  BluetoothSettings();   
}

void loop() {
  if (Back == BACK_CODE)
  {
    ////Receive settings from App thru Bluetooth
    BluetoothSettings(); 
  }
  else
  {
    if (ModeReceived == DEMOMODE_CODE) //Demo
    {
      demo(BeatReceived);
      //Bluetooth_CheckVolumeButton(); //might have to move this somewhere else to have better response time
    }
    else 
    if (ModeReceived == SEQUENCEMODE_CODE) //Sequence
    {
      sequence(BeatReceived);
    }
    else 
    if (ModeReceived == PLAYALONGMODE_CODE) // PlayAlong
    {
      
    }
    Bluetooth_CheckBackButton();
  }  
}

/*********************************************************************/
/************************* Setup Functions ***************************/
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

/*********************************************************************/
/*                         DEMO MODE                                  /
/*********************************************************************/
/****************** Demo Start-Up Functions **************************/
/*********************************************************************/
void demo(short BEAT){
  DEMOsetup();
  DEMOplaybeat(BEAT);
}

void DEMOsetup() {
  //EXTRA
  eightTempo= adj_tempo/2;   //tempo used for beats with and
  sixTempo  = eightTempo/2;    //tempo used for beats with sixteenth notes

  RESET(); //clean start, all equal to Vdd so there is no sound
}

//MAIN LOOP
void DEMOplaybeat(short BEAT) {
  //Choose beat depending on what the user chooses
  if (BEAT == BEAT1_CODE){
    rockBeat();
  } else
  if (BEAT == BEAT2_CODE){
    rockV2Beat();
  } else
  if (BEAT == BEAT3_CODE){
    discoBeat();
  } else
  if (BEAT == BEAT4_CODE){
    rockYou();
  }
}

  //Initializing pins to 5V so they do NOT play sound
void RESET(){
  digitalWrite(kickFXPin,    HIGH);
  digitalWrite(snareFXPin,   HIGH);
  digitalWrite(hihatFXPin,   HIGH);
  digitalWrite(hhkickFXPin,  HIGH);
  digitalWrite(hhsnareFXPin, HIGH);
  analogWrite(hihatREDPin,  0);
  analogWrite(kickREDPin,   0);
  analogWrite(kickGREENPin, 0);
  analogWrite(snareBLUEPin, 0);
  
  //When values are set to 0, the sound will be played
}

//Play part of Drumset
void playSound(short part){
  digitalWrite(part, LOW);  //starts playback of file
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(adj_tempo);         //moves on to next file for the appropriate tempo
}
/***********************************EXTRA************************************/
  //Extra function for expanding amount of beats
void play8Sound(short part){
  digitalWrite(part, LOW);  //starts playback of file
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(eightTempo);        //moves on to next file for the appropriate tempo  
}
void play16Sound(short part){
  digitalWrite(part, LOW);  //starts playback of file
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(sixTempo);         //moves on to next file for the appropriate tempo  
}
/***************************************************************************/

//Volume Control
void VolumeCtr(short button){
  //Values that come through the app
  short downButton = 0; //(-)
  short upButton   = 1; //(+)

  if (button == downButton)
    volDown = LOW;
  if (button == upButton)
    volUp   = LOW;  
}

/******************************************************/
/*                     ROCK BEAT                      */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o-------v----                    */
/******************************************************/   
void rockBeat(){  //Setting LEDs to specific colors/pins
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
}

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

/******************************************************/
/*                  REGGAETON BEAT                    */
/******************************************************/
//Not working
/*void reggaetonBeat(){
  short hlftempo = tempo/2;
  short hlftempadd = hlftempo + tempo;
  
  digitalWrite(hhkick, LOW);
  delay(250);
  RESET();
  delay(hlftempadd);
  //delay(750);

  digitalWrite(snare, LOW);
  delay(250);
  RESET();
  delay(hlftempo);
  //delay(250);

  digitalWrite(hhkick, LOW);
  delay(250);
  RESET();
  delay(tempo);
  //delay(500);

  digitalWrite(snare, LOW);
  delay (250);
  RESET();
  delay(tempo);
  //delay(500);
}
*/

/*********************************************************************/
/*                         SEQUENCE MODE                             */             
/*********************************************************************/
void sequence(short BEAT){
  SEQUENCEsetup();
  SEQUENCEplaybeat(BEAT);
}

void SEQUENCEsetup() {
  //Call reset?
  tempo = tempo - 125;
}

//MAIN LOOP
void SEQUENCEplaybeat(short BEAT) {
  //Choose beat depending on what the user chooses
  if (BEAT == BEAT1_CODE){
    /*
    Serial.println("Beat is Beat 1");
    
    Serial.println("Playing snare");
    snare();
    delay(tempo);

    Serial.println("Playing hihat");
    hihat();
    delay(tempo); 
    */   
    SEQUENCErockBeat();
    
  } else
  if (BEAT == BEAT2_CODE){
    SEQUENCErockV2Beat();
  } else
  if (BEAT == BEAT3_CODE){
    SEQUENCEdiscoBeat();
  } else
  if (BEAT == BEAT4_CODE){
    SEQUENCErockYou();
  }
}

/******************************************************/
/*        FUNCTIONS FOR THE DIFFERENT BEATS           */
/******************************************************/
void SEQUENCErockBeat() {
  hihat_kick();
  delay(tempo);
  hihat();
  delay(tempo);
  hihat_snare();
  delay(tempo);
  hihat();
  delay(tempo);
}

void SEQUENCErockV2Beat() {
  hihat_kick();
  delay(tempo);
  hihat();
  delay(tempo);
  hihat_snare();
  delay(tempo);
  hihat();
  delay(tempo);

  hihat_kick();
  delay(tempo);
  hihat_kick();
  delay(tempo);
  hihat_snare();
  delay(tempo);
  hihat();
  delay(tempo);
}

void SEQUENCEdiscoBeat() {
  kick();
  delay(tempo);
  hihat();
  delay(tempo);
  snare();
  delay(tempo);
  hihat();
  delay(tempo);
}

void SEQUENCErockYou() {
  kick();
  delay(tempo);
  kick();
  delay(tempo);
  snare();
  delay(tempo);
  //none
  delay(tempo);
}

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
  while( ((hihatSensorReading = analogRead(hihatSensorPin)) < threshold_hihat) && ((kickSensorReading = analogRead(kickSensorPin)) < threshold_kick) ) { 
  }                                         //While hihat && kick below threshold, do nothing

  averageAnalogRead_hihatkick();
  
  if(((hihatSensorReading_Average) > threshold_hihat) && ((kickSensorReading_Average) > threshold_kick)) {
    hitConfirmation_hihatkick();
  } else
  if( hihatSensorReading >= threshold_hihat ) {    //If the hihat sensor was triggered
    hitConfirmation_hihat();  
    while( analogRead(kickSensorPin) < threshold_kick) { } //Do nothing until snare is hit
    hitConfirmation_kick();
  } else
  if ( kickSensorReading >= threshold_kick ) { //If the kick sensor was triggered
    hitConfirmation_kick();
    while( analogRead(hihatSensorPin) < threshold_hihat) { } //Do nothing until hihat sensor is pushed
    hitConfirmation_hihat();
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

/******************************************************/

void hitConfirmation_hihat() {
    analogWrite(hihatREDPin, 0);
    analogWrite(hihatGREENPin, 255);
    delay(125);
    analogWrite(hihatGREENPin, 0);
}

void hitConfirmation_snare() {
    analogWrite(snareBLUEPin, 0);
    analogWrite(snareGREENPin, 255);
    delay(125);
    analogWrite(snareGREENPin, 0);
}

void hitConfirmation_kick() {
    analogWrite(kickREDPin, 0);
    analogWrite(kickGREENPin, 0);
    
    analogWrite(kickGREENPin, 255);
    delay(125);
    analogWrite(kickGREENPin, 0);
}

void hitConfirmation_hihatsnare() {
    analogWrite(hihatREDPin, 0);
    analogWrite(snareBLUEPin, 0);
    
    analogWrite(hihatGREENPin, 255);
    analogWrite(snareGREENPin, 255);
    delay(125);
    analogWrite(hihatGREENPin, 0);
    analogWrite(snareGREENPin, 0);
}

void hitConfirmation_hihatkick() {
    analogWrite(hihatREDPin, 0);
    analogWrite(kickREDPin, 0);
    analogWrite(kickBLUEPin, 0);
    
    analogWrite(hihatGREENPin, 255);
    analogWrite(kickGREENPin, 255);
    delay(125);
    analogWrite(hihatGREENPin, 0);
    analogWrite(kickGREENPin, 0);
}

/******************************************************/

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


/*********************************************************************/
/*                        PLAYALONG MODE                             */
/*********************************************************************/
/********************** PlayAlong Functions **************************/
/*********************************************************************/










/*********************************************************************/
/********************** Bluetooth Functions **************************/
/*********************************************************************/
//Receive settings from App thru Bluetooth
/*
 * Changes:
 *    BeatReceived
 *    TempoReceived
 *    ModeReceived
 */
void BluetoothSettings()
{
  short count = 3;
  Serial.println("Entered BluetoothSettings");
  
  while ( count > 0 )
  {
    if(Serial.available()>0)
    {
      Back = 0;
      Received = Serial.read();
      
      if (count == 3)
      {
        BeatReceived = Received;
        Serial.print("BeatReceived: ");
        Serial.println(BeatReceived);
      }
      if (count == 2)
      {
        TempoReceived = Received;
        Serial.print("TempoReceived: ");
        Serial.println(TempoReceived);
      }
      if (count == 1)
      {
        ModeReceived = Received;
        Serial.print("ModeReceived: ");
        Serial.println(ModeReceived);
      }
      count--;
    }
  }
  tempo = 60000 / TempoReceived; 
  adj_tempo = tempo-250;  
  Serial.println("BluetoothSettings Done");
}

void Bluetooth_CheckBackButton()
{
  //Serial.println("Back Checked");
  if(Serial.available() > 0)
    {
      Back = Serial.read();
      Serial.println("Back pressed");
    }
}

void Bluetooth_CheckVolumeButton()
{
  if(Serial.available() > 0)
    {
      VolumeControl = Serial.read();
      if (VolumeControl == VOLUMEDOWN_CODE) 
      {
        Serial.println("Volume down pressed");
      }
      else if (VolumeControl == VOLUMEUP_CODE)
      {
        Serial.println("Volume up pressed");
      }
    }
}

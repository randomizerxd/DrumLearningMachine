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

//Pins for sound
int kick = 29;   //setting pin 29 to 'kick' sound
int snare = 30;  //setting pin 30 to 'snare' sound
int hihat = 28;  //setting pin 28 to 'hihat' sound
int hhkick = 31; //setting pin 31 to 'hihat' and 'kick' sound
int hhsnare = 32;//setting pin 32 to 'hihat' and 'snare' sound
int tempo = 200;  //316 = 190bpm; Inc = slower; Dec = faster (LIMIT: 83ms to 475ms)

void setup() {
  Serial.begin(9600);   //use serial port

    //Setup pins 
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



  
  //T00 = hihat
  //T01 = snare
  //T02 = kick
  //T03 = kick and hihat
  pinMode(kick, OUTPUT);
  pinMode(snare, OUTPUT);
  pinMode(hihat, OUTPUT);
  pinMode(hhkick, OUTPUT);
  pinMode(hhsnare, OUTPUT);

}

  //Initializing pins to 5V so they do NOT play sound
void RESET(){
  digitalWrite(kick, HIGH);
  digitalWrite(snare, HIGH);
  digitalWrite(hihat, HIGH);
  digitalWrite(hhkick, HIGH);
  digitalWrite(hhsnare, HIGH);
  //When values are set to 0, the sound will be played
}

void loop() {

  /* BLUETOOTH
   *  i.  receive tempo in bpm
   *  ii. convert to ms (60 / #bpm) * 1000
   * 
   * 
   */


  
  /*****ROCK BEAT*****/
  /*
   * 1) hhkick
   *      i.  turn light red
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
   *      
   * 
   * 2) hihat
   * 
   * 3) hhsnare
   * 
   * 4) hihat
   */


  
  //rockBeat();
  //discoBeat();
  //reggaetonBeat();

  

}

/******************************************************/
/*        FUNCTIONS FOR THE DIFFERENT BEATS           */
/******************************************************/

//               DEFAULT/TEST                         //

void demo(){  
  digitalWrite(hhkick, LOW);
  //doubleWrite(hhkick, hihat);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hhsnare, LOW);
  //doubleWrite(hhsnare, hihat);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay (250);
  RESET();
  delay(tempo);
}

/******************************************************/
/*                     ROCK BEAT                      */
/******************************************************/

void rockBeat(){  
  digitalWrite(hhkick, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hhsnare, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay (250);
  RESET();
  delay(tempo);
}

/******************************************************/
/*                    DISCO BEAT                      */
/******************************************************/

void discoBeat(){  
  digitalWrite(kick, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(snare, LOW);
  delay(250);
  RESET();
  delay(tempo);
  
  digitalWrite(hihat, LOW);
  delay (250);
  RESET();
  delay(tempo);
}

/******************************************************/
/*                  REGGAETON BEAT                    */
/******************************************************/

void reggaetonBeat(){
  int hlftempo = tempo/2;
  int hlftempadd = hlftempo + tempo;
    
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






/******************************************************/
/*               EXTRA TESTING CODE                   */
/******************************************************/

/*void doubleWrite(int pin1, int pin2){
  digitalWrite(pin1, LOW);
  delay(5);
  digitalWrite(pin2, LOW);
  delay(5);
}*/


int kick = 29;   //setting pin 29 to 'kick' sound
int snare = 30;  //setting pin 30 to 'snare' sound
int hihat = 28;  //setting pin 28 to 'hihat' sound
int hhkick = 31; //setting pin 31 to 'hihat' and 'kick' sound
int hhsnare = 32;//setting pin 32 to 'hihat' and 'snare' sound
int tempo = 200;  //316 = 190bpm; Inc = slower; Dec = faster (LIMIT: 83ms to 475ms)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //use serial port
  
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
  
  //rockBeat();
  //discoBeat();
  reggaetonBeat();

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




//INITIALIZING PINS AND VARIABLES
int hihat     = 28;        //set pin 28 to 'hihat' sound
int kick      = 29;        //set pin 29 to 'kick' sound
int snare     = 30;        //set pin 30 to 'snare' sound
int hhkick    = 31;        //set pin 31 to 'hihat' and 'kick' sound
int hhsnare   = 32;        //set pin 32 to 'hihat' and 'snare' sound

int volUp     = 34;        //set pin 34 to volume-up
int volDown   = 35;        //set pin 35 to volume-down

int tempo     = 400;       //316 = 190bpm; Inc = slower; Dec = faster (LIMIT: 350ms to 1500ms)
int adj_tempo = tempo-250; //adjusted tempo to take into account the file delay

void setup() {
  //setup code here, to run once:
  Serial.begin(115200);   //use serial port
  //Files on Audio FX SoundBoard
  //T00 = hihat
  //T01 = snare
  //T02 = kick
  //T03 = kick and hihat
  pinMode(kick,    OUTPUT);
  pinMode(snare,   OUTPUT);
  pinMode(hihat,   OUTPUT);
  pinMode(hhkick,  OUTPUT);
  pinMode(hhsnare, OUTPUT);
  RESET(); //clean start
}

void loop() {

  rockYou();    //we will - we will - rock you TA - BUM BUM TA
  //rockBeat();
  //discoBeat();

}


/*****************************************************/
/*                     FUNCTIONS                     */
/*****************************************************/

  //Initializing pins to 5V so they do NOT play sound
void RESET(){
  digitalWrite(kick,    HIGH);
  digitalWrite(snare,   HIGH);
  digitalWrite(hihat,   HIGH);
  digitalWrite(hhkick,  HIGH);
  digitalWrite(hhsnare, HIGH);
  //When values are set to 0, the sound will be played
}

  //Play part of Drumset
void playSound(int part){
  digitalWrite(part, LOW);  //starts playback of file
  delay(250);               //plays file for the appropriate amount of time
  RESET();                  //stops playback of file
  delay(adj_tempo);         //moves on to next file for the appropriate tempo
}

  //Volume Control
void VolumeCtr(int button){
  //Values that come through the app
  int downButton = 0; //(-)
  int upButton   = 1; //(+)
  
  if (button == downButton)
    volDown = LOW;
  if (button == upButton)
    volUp   = LOW;  
}


/******************************************************/
/*        FUNCTIONS FOR THE DIFFERENT BEATS           */
/******************************************************/


/******************************************************/
/*                     ROCK BEAT                      */
/******************************************************/

void rockBeat(){  
  playSound(hhkick);
  
  playSound(hihat);
  
  playSound(hhsnare);
  
  playSound(hihat);
}

/******************************************************/
/*                    DISCO BEAT                      */
/******************************************************/

void discoBeat(){
  playSound(kick);
  
  playSound(hihat);
  
  playSound(snare);
  
  playSound(hihat);
}

/******************************************************/
/*                   ROCK-YOU BEAT                    */
/******************************************************/

void rockYou(){  
  playSound(kick);
  
  playSound(kick);
  
  playSound(snare);
  
  playSound(0);
}

/******************************************************/
/*                  REGGAETON BEAT                    */
/******************************************************/

/*void reggaetonBeat(){
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
*/


//               DEFAULT/TEST                         //

void demo(){  
  playSound(hhkick);
  /*digitalWrite(hhkick, LOW);
  //doubleWrite(hhkick, hihat);
  delay(250);
  RESET();
  delay(tempo);*/
  
  playSound(hihat);
  /*digitalWrite(hihat, LOW);
  delay(250);
  RESET();
  delay(tempo);*/
  
  playSound(hhsnare);
  /*digitalWrite(hhsnare, LOW);
  //doubleWrite(hhsnare, hihat);
  delay(250);
  RESET();
  delay(tempo);*/

  playSound(hihat);
  /*digitalWrite(hihat, LOW);
  delay (250);
  RESET();
  delay(tempo);*/
}

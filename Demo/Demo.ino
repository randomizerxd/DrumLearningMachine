
//INITIALIZING PINS AND VARIABLES
short hihat     = 49;            //set pin 28 to 'hihat' sound
short kick      = 50;            //set pin 29 to 'kick' sound
short snare     = 51;            //set pin 30 to 'snare' sound
short hhkick    = 52;            //set pin 31 to 'hihat' and 'kick' sound
short hhsnare   = 53;            //set pin 32 to 'hihat' and 'snare' sound

short volUp     = 47;            //set pin 34 to volume-up
short volDown   = 48;            //set pin 35 to volume-down

short tempo     = 340;           //316 = 190bpm; Inc = slower; Dec = faster (LIMIT: 350ms to 1500ms)
short adj_tempo = tempo-250;     //adjusted tempo to account the file delay
short eightTempo= adj_tempo/2;   //tempo used for beats with and
short sixTempo  = eightTempo/2;    //tempo used for beats with sixteenth notes

void setup() {
  //setup code here, to run once:
  Serial.begin(9600);  //use serial port
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

  //rockYou();    //we will - we will - rock you TA - BUM BUM TA
  rockBeat();
  //rockV2Beat();
  //discoBeat();
  //bossaNova(); --boom ta boom boom ta

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
/*        FUNCTIONS FOR THE DIFFERENT BEATS           */
/******************************************************/


/******************************************************/
/*                     ROCK BEAT                      */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o-------v----                    */
/******************************************************/   

void rockBeat(){  
  playSound(hhkick);
  
  playSound(hihat);
  
  playSound(hhsnare);
  
  playSound(hihat);
}

/******************************************************/
/*                    ROCK V2 BEAT                    */
/*                   1   2   3   4                    */
/*                   x---x---x---x                    */
/*                   o--(o)--v----                    */
/******************************************************/

void rockV2Beat(){  
  playSound(hhkick);
  
  playSound(hihat);
  
  playSound(hhsnare);
  
  playSound(hihat);
//Second loop
  playSound(hhkick);
  
  playSound(hhkick);
  
  playSound(hhsnare);
  
  playSound(hihat);
}

/******************************************************/
/*                    DISCO BEAT                      */
/*                   1   2   3   4                    */
/*                   ----x-------x                    */
/*                   o-------v----                    */
/******************************************************/

void discoBeat(){
  playSound(kick);
  
  playSound(hihat);
  
  playSound(snare);
  
  playSound(hihat);
}

/******************************************************/
/*                   ROCK-YOU BEAT                    */
/*                   1 a 2 a 3 a 4                    */
/*                   ----v-------v                    */
/*                   o-o-----o-o--                    */
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

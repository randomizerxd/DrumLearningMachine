//Randy Baldwin
//Last Updated : 10/11/18
// Demo : Plays the beats through the lights and buzzer

//Variable for Piezo Buzzer
int buzzerPin = 3;

//Variables for LEDs
//These LEDs symbolize the RGB LED strip that will be on the 
// drums and cymbals
//Resistor of value 200-1k ohm is needed to limit current
// across LED
int hihatLEDPin = 31;
int snareLEDPin = 32;
int kickLEDPin  = 33;

//cycle through beats
int beatSelectPin = 34;
//Change tempo
int tempoDecreasePin = 35;
int tempoIncreasePin  = 36;

#define rockBeat  0  
#define discoBeat 1
#define reggaetonBeat 2

//Variable to store beat choice
//Initialize to rock beat
int beat = rockBeat;


void setup() {
  pinMode(hihatLEDPin, OUTPUT);
  pinMode(snareLEDPin, OUTPUT);
  pinMode(kickLEDPin, OUTPUT);
  pinMode(beatSelectPin, INPUT);
  pinMode(beatSelectPin, INPUT);
  pinMode(beatSelectPin, INPUT);
  
  pinMode(buzzerPin, OUTPUT);

  //Initialize all LEDs to OFF
  digitalWrite(hihatLEDPin, LOW);
  digitalWrite(snareLEDPin, LOW);
  digitalWrite(kickLEDPin, LOW);
}

void loop() {
  while(beat == rockBeat) {
    playRockBeat();
    checkBeatSelectButton();
  }
  while(beat == discoBeat) {
    playDiscoBeat();
    checkBeatSelectButton();
  }
  while(beat == reggaetonBeat) {
    playReggaetonBeat();
    checkBeatSelectButton();
  }  
  
}

void hihat(int hihatDuration, int delayDuration) {
  digitalWrite(hihatLEDPin, HIGH);
  tone(buzzerPin, 2000, hihatDuration / 4);
  delay(delayDuration / 4);
  digitalWrite(hihatLEDPin, LOW);
  delay(delayDuration / 4);
}
void snare(int snareDuration, int delayDuration) {
  digitalWrite(snareLEDPin, HIGH);
  tone(buzzerPin, 1000, snareDuration / 4);
  delay(delayDuration / 4);
  digitalWrite(snareLEDPin, LOW);  
  delay(delayDuration / 4);
}
void kick(int kickDuration, int delayDuration) {
  digitalWrite(kickLEDPin, HIGH);
  tone(buzzerPin, 500, kickDuration / 4);
  delay(delayDuration / 4);
  digitalWrite(kickLEDPin, LOW); 
  delay(delayDuration / 4);
}
//This function turns on the lights on the hihat and kick 
void hihat_kick(int hihatDuration, int kickDuration, int delayDuration) {
  digitalWrite(hihatLEDPin, HIGH);
  digitalWrite(kickLEDPin, HIGH);
  tone(buzzerPin, 2000, hihatDuration / 4);
  delay(hihatDuration / 4); 
  digitalWrite(hihatLEDPin, LOW);

  noTone(buzzerPin);
  tone(buzzerPin, 500, kickDuration / 10);
  delay(kickDuration / 10);
  digitalWrite(kickLEDPin, LOW);
  
  delay(delayDuration / 8); 
}
//This function turns on the lights on the hihat and snare
void hihat_snare(int hihatDuration, int snareDuration, int delayDuration) {
  digitalWrite(hihatLEDPin, HIGH);
  digitalWrite(snareLEDPin, HIGH);
  tone(buzzerPin, 2000, hihatDuration / 4);
  delay(hihatDuration / 4); 
  digitalWrite(hihatLEDPin, LOW);

  noTone(buzzerPin);
  tone(buzzerPin, 1000, snareDuration / 10);
  delay(snareDuration / 10);
  digitalWrite(snareLEDPin, LOW);
  
  delay(delayDuration / 8);  
}


void checkBeatSelectButton() {
  if( digitalRead(beatSelectPin) == HIGH )
  {
    if( beat == rockBeat ) {
      beat = discoBeat;
    } else
    if( beat == discoBeat ) {
      beat = reggaetonBeat;
    } else
    if( beat == reggaetonBeat ) {
      beat = rockBeat;
    }
  }
}
//Come back and finish this. I feel like this needs to be an interrupt. 
//or maybe I have to use the millis() instead of delay()
void checkTempoDecreaseButton() {
  
}

void playRockBeat() {
  hihat_kick(1000, 1000, 1000);
  hihat(1000, 1000);
  hihat_snare(1000, 1000, 1000);
  hihat(1000, 1000);
}
void playDiscoBeat() {
  kick(500, 500);
  hihat(500, 500);
  snare(500, 500);
  hihat(500, 500);
/* Drum fill / solo
  hihat(500);
  hihat(500);
  hihat(500);
  snare(500);
    
  kick(500);
  kick(500);
  hihat(1000);
*/  
}
void playReggaetonBeat() {
  kick(750, 750);
  snare(250, 250);
  kick(500, 500);
  snare(500, 500);  
}
    
  
  

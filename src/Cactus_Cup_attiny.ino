#include <Filters.h>
#include <avr/interrupt.h>

// STATE MACHINE constants
#define NUM_STATE 5
#define LED_STATE 0
#define MIC_STATE 1
#define SLOW_STATE 2
#define BEAT_DETECT_STATE 3
#define COLOR_SWIRL_STATE 4

// Fast Fourier Transform constants
#define THRESH 7
#define BASSHIGH 220 // was 200
#define BASSLOW 20
#define ENVFREQ 20 // was 10
#define BEATHIGH 3.0
#define BEATLOW 1.7
#define WINDOW 1
#define microphonePin A3

FilterOnePole bass_high(HIGHPASS,BASSLOW);
FilterOnePole bass_low(LOWPASS,BASSHIGH);
FilterOnePole envelope(LOWPASS,ENVFREQ);
FilterOnePole beat_high(HIGHPASS,BEATLOW);
FilterOnePole beat_low(LOWPASS,BEATHIGH);
RunningStatistics stats;

float sample = 0;
float thresh = 0;
float diff = 0;
char t;
float beat;
float bass;
int prevTime;

const int buttonPin = 2;   // the number of the pushbutton pin
const int redPin    = 0;
const int greenPin  = 1;
const int bluePin   = 4;

// variables will change:
int state = 0;

void setup() {
  // microphone setup
  pinMode(microphonePin, INPUT);
  stats.setWindowSecs(WINDOW);
  analogReference(INTERNAL);
  prevTime = millis();

  // led & pushbutton setup
  GIMSK |= _BV(INT0);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  switch(state) {
    case LED_STATE:
      ledState();
      break;
    case MIC_STATE:
      micState();
      break;
    case SLOW_STATE:
      slowState();
      break;
    case BEAT_DETECT_STATE:
      beatDetect();
      break;
    case COLOR_SWIRL_STATE:
      colorSwirl();
      break;
    default:
      ledState();
      break;
  }
  
}

void ledState() {
  setRed();
}

void micState() {
  setGreen();
}

void slowState() {
  setBlue();
}

void setRed(){
  digitalWrite(redPin,   HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin,  LOW);
}

void setGreen() {
  digitalWrite(redPin,   LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin,  LOW);
}

void setBlue() {
  digitalWrite(redPin,   LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin,  HIGH);
}

void beatDetect() {
  digitalWrite(redPin,   LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin,  LOW);
  while(state == BEAT_DETECT_STATE) {
    t = millis() - prevTime;
    sample = analogRead(microphonePin);
    bass_low.input(sample);
    bass_high.input(bass_low.output());
    bass = bass_high.output();
    bass = abs(bass);
  
    envelope.input(bass);
    stats.input(beat);
    thresh = stats.mean() + stats.sigma();
  
    if(t > 5){
      prevTime = millis();
      beat_low.input(envelope.output());
      beat = beat_high.input(beat_low.output());
      if(beat > thresh){
        digitalWrite(redPin, HIGH);
      } else{
        digitalWrite(redPin, LOW);
      }
    }
  }
}

void colorSwirl() {
  for(int x=0; x < 2; x++) {
    for(int y=0; y < 2; y++) {
      for(int z=0; z <2; z++) {
        if(!validState(COLOR_SWIRL_STATE)) {
          x = 2; y = 2; z = 2; 
        }
        if(x) {digitalWrite(redPin,   HIGH);} else {digitalWrite(redPin,   LOW);}
        if(y) {digitalWrite(greenPin, HIGH);} else {digitalWrite(greenPin, LOW);}
        if(z) {digitalWrite(bluePin,  HIGH);} else {digitalWrite(bluePin,  LOW);}
        if(!x && !y && !z) {
          digitalWrite(redPin,   HIGH); 
          digitalWrite(greenPin, HIGH); 
          digitalWrite(bluePin,   HIGH);
        }
        delay(800);
      }
    }
  }
}

boolean validState(int curr_state) {
  if(curr_state != state) {
    return false;
  } else {
    return true;
  }
}

ISR(INT0_vect) {
  state = (state + 1) % NUM_STATE;
}


//#include <QueueArray.h>
#include <Filters.h>
//QueueArray <int> queue;
//#define QUEUE_SIZE 1000
#define SIZE 100
#define THRESH 7
#define BASSHIGH 200
#define BASSLOW 20
#define ENVFREQ 10
#define BEATHIGH 3.0
#define BEATLOW 1.7
#define WINDOW 1
#define microphonePin A1
#define ledPin 0


FilterOnePole bass_high(HIGHPASS,BASSLOW);
FilterOnePole bass_low(LOWPASS,BASSHIGH);
FilterOnePole envelope(LOWPASS,ENVFREQ);
FilterOnePole beat_high(HIGHPASS,BEATLOW);
FilterOnePole beat_low(LOWPASS,BEATHIGH);
RunningStatistics stats;

float sample = 0;
float avg = 465;
float thresh = 0;
float diff = 0;
char t;
float beat;
float bass;
int prev;

char sampleTime;


void setup () 
{
  pinMode(ledPin, OUTPUT);
  pinMode(microphonePin, INPUT);
  //Serial.begin (250000);
  stats.setWindowSecs(WINDOW);
  analogReference(INTERNAL);
  prev = millis();
}

void loop () 
{
  
   t = millis() - prev;
   sample = analogRead(microphonePin);
   bass_low.input(sample);
   bass_high.input(bass_low.output());
   bass = bass_high.output();

   bass = abs(bass);

   envelope.input(bass);
   stats.input(beat);

   thresh = stats.mean() + stats.sigma();

   if(t > 5){
    prev = millis();
    beat_low.input(envelope.output());
    beat = beat_high.input(beat_low.output());
    if(beat > thresh){
      digitalWrite(ledPin,HIGH);
    }else{
      digitalWrite(ledPin,LOW);
    }
   }

   

//  if ( low_pass.output() > 983){
//    digitalWrite(ledPin, HIGH);
//    sampleTime = 0;
//  }
//  else if (sampleTime > 50) {
//    digitalWrite(ledPin, LOW);
//    sampleTime = 0;
//  }
//  //delayMicroseconds(20);
//  sampleTime += 1;
 
  //Serial.print("B ");
  //Serial.print(beat);
  //Serial.print(" B ");
  //Serial.println(thresh);
//  Serial.print(" F ");
//  Serial.println(envelope.output());
 //Serial.print(" T: ");
  //Serial.println(thresh);
//  Serial.print(" Thresh+: ");
//  Serial.println(avg + THRESH)
  
}

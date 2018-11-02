//#include <QueueArray.h>
#include <Filters.h>
int ledPin = 8;
int microphone = A0;
//QueueArray <int> queue;
//#define QUEUE_SIZE 1000
#define SIZE 100
#define THRESH 7

void setup () 
{
  pinMode(ledPin, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin (115200);
}

float freq = 100;

FilterTwoPole lowpassFilter(freq);

float sample = 0;
float avg = 465;
float thresh = 0;
float diff = 0;
char sampleTime;

void loop () 
{

  lowpassFilter.input(analogRead(microphone));
  
  
  sample = analogRead(microphone);
  diff = abs(sample - avg);
  //sample = abs(sample - 465) + 465;
  avg = avg - avg/SIZE;
  avg = avg + sample/SIZE;
  thresh = thresh - thresh/SIZE;
  thresh = thresh + diff/SIZE;

  if ( lowpassFilter.output() > 983){
    digitalWrite(ledPin, HIGH);
    sampleTime = 0;
  }
  else if (sampleTime > 50) {
    digitalWrite(ledPin, LOW);
    sampleTime = 0;
  }
  //delayMicroseconds(20);
  sampleTime += 1;
 
  Serial.print("D: ");
  Serial.println(lowpassFilter.output());
 //Serial.print(" T: ");
  //Serial.println(thresh);
//  Serial.print(" Thresh+: ");
//  Serial.println(avg + THRESH)
  
}

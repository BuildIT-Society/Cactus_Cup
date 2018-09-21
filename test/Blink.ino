#include <SoftwareSerial.h>
int led = 13; // pin 0
int timer = 400; // ms

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  //int timer; // time delay constant
}

void loop() { 
  // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);
    delay(timer);
    digitalWrite(led, LOW);
    delay(timer);
}

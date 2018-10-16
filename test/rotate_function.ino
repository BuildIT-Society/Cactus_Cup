void setup() {
  // put your setup code here, to run once:
pinMode(8, OUTPUT);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rate = 100;
  rotate(rate);
}
void rotate(int rate){
  int pin;
  for (pin=8;pin>=5;pin--){
    digitalWrite(pin, HIGH);
    delay(rate);
    digitalWrite(pin, LOW);
  }
}


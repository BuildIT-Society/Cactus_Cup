char LATCHPIN = 5;
char CLOCKPIN = 6;
char DATAPIN = 7;

byte led_value = B00000001;

void setup() {
  // put your setup code here, to run once:
  pinMode( LATCHPIN, OUTPUT );
  pinMode( CLOCKPIN, OUTPUT );
  pinMode( DATAPIN, OUTPUT );

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    send_byte(led_value);
    led_value = led_value << 1; 
  }
  send_byte(B10101010);
  send_byte(B01010101);
  led_value = 1;
}

/**********************************************************
* Function: send_byte
* Description: Shifts a byte of data least significant bit
* first. 
**********************************************************/
void send_byte(byte led ){
  digitalWrite( LATCHPIN, LOW );
  shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, led); 
  digitalWrite( LATCHPIN, HIGH);
  delay(1000);
}

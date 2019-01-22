#include <Wire.h>

#define START 0x23
#define END 0x21
#define READ 0x0
#define CAL 0x2

#define BUSY 0x00
#define FREE 0x01

byte ADDR = 0x31; //slave addr
byte READ_ADDR = 0x63;
byte WRITE_ADDR = 0x62;
byte STATUS = FREE;
byte CMD=START;

const int ledPin = 13; // onboard LED
static_assert(LOW == 0, "Expecting LOW to be 0");

void setup() {
  Wire.begin(ADDR);                // join i2c bus with ADDR
  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn it off
}

void loop() {
  delay(100);
}

void requestEvent() {
  
  char DCO2[7];
  DCO2[0] = 0x08;
  DCO2[1] = 0xff;
  DCO2[2] = 0x32;
  DCO2[3] = 0x00;  
  DCO2[4] = 0x00;  
  DCO2[5] = 0x00;  
  DCO2[6] = 0x00;  

   switch(CMD){
    case START : Wire.write(STATUS);break;
    case END : STATUS=FREE; break;
    case READ : STATUS =BUSY; Wire.write(DCO2); STATUS= FREE; break;
    case CAL : STATUS= BUSY; Wire.write(0x1); STATUS= FREE; break;
   }

  digitalWrite(ledPin, 0x1);
}

void receiveEvent(int tmp) {

  while (Wire.available()) {
    CMD = Wire.read(); // receive byte as a character    
   }
    digitalWrite(ledPin, 0x0);
}


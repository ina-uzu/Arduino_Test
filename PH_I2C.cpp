#include <Wire.h>

#define READ 0x0
#define I2C 0x1
#define CAL 0x2
#define I 0x3
#define MAX_LENGTH 20


byte CMD = 0x0;
byte ADDR = 0x64; //slave addr
const int ledPin = 13; // onboard LED
static_assert(LOW == 0, "Expecting LOW to be 0");  

void setup() {
  Serial.begin(9600);
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
  char code = 1;  
  int value1 = 4, value2 =56;
  char buffer[MAX_LENGTH];

  switch (CMD) {
    case READ: 
      sprintf(buffer, "%c%d.%d\0", code, value1, value2);
      break;
  
    case I2C: 
      sprintf(buffer, "%c%d\0", code,ADDR);
      break;

    case CAL:
      sprintf(buffer, "%c\0", code);
      break;
  }

  Wire.write(buffer);
  digitalWrite(ledPin, 0x1);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    CMD = Wire.read(); // receive byte as a character
    digitalWrite(ledPin, 0x0);
  }
}

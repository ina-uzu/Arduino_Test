#define MAX_LENGTH 100

int BAUD_RATE = 9600;
char buf[MAX_LENGTH];
int dco2Data = 12345;

void setup() {
  Serial.begin(BAUD_RATE);
  
}

void loop() {
  sprintf(buf,"  %d ppm\r\n", dco2Data);
  Serial.print(buf);
  //delay(1000);
}  
#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

#define LP 5
#define RP 6
#define SRV 11

Servo srv;
VL53L0X s1;

int pos = 0;
float data[160][2];
char bt;

void setup() {
  
  pinMode(LP, OUTPUT);
  pinMode(RP, OUTPUT);
  pinMode(SRV, OUTPUT);

  Serial.begin(115200);
  Wire.begin();

  s1.setTimeout(500);
  if (!s1.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  s1.startContinuous();

  srv.attach(SRV);
}

void loop() {
  
  if(Serial.available()) {
    bt = Serial.read();
    Serial.println(bt);
  }

  if(bt == 'f' || bt == 'F') {
    moveForward();
  }

  if(bt == 'l' || bt == 'L') {
    moveLeft();
  }

  if(bt == 'r' || bt == 'R') {
    moveRight();
  }

  if(bt == 'a' || bt == 'A') {
    roamAuto();
  }

  if(bt == 's' || bt == 'S') {
    halt();
  }
}

void roamAuto() {
  
  float maxDist = data[0][1];
  int maxAngle = 0;

  getSensorData();

  for(int i = 0; i < 160; i++) {
    if(data[i][1] > maxDist) {
      maxDist = data[i][1];
      maxAngle = data[i][0];
    }
  }

  if(maxAngle <= 60) {
    moveLeft();
    delay(3000);
    halt();
  }

  if(maxAngle > 60 && maxAngle < 100) {
    moveForward();
    delay(3000);
    halt();
  }

  if(maxAngle >= 100) {
    moveRight();
    delay(3000);
    halt();
  }

  if(bt != 'a' || bt != 'A')
  {
    return;
  }
}

float dist() {              
  float dist = s1.readRangeContinuousMillimeters() / 10;
  if (s1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  return dist;
}

void getSensorData() {

  float d = 0.00;
  
  for(pos = 10; pos <= 170; pos += 1) {
    srv.write(pos);
    d = dist();
    data[pos - 10][0] = pos;
    data[pos - 10][1] = d;
    delay(10);
  }
  dispDataSerial();
  for(pos = 170; pos >= 10; pos -= 1) {
    srv.write(pos);
    d = dist();
    data[(170 - pos)][0] = pos;
    data[(170 - pos)][1] = d;
    delay(10);
  }
  dispDataSerial();
}

void dispDataSerial() {
  for(int i = 0; i < 160; i++) {
    Serial.print("Angle: ");
    Serial.print(data[i][0]);
    Serial.print("° | Dist: ");
    Serial.print(data[i][1]);
    Serial.println("cm");
  }
}

void getGPS() {
//  while (ss.available() > 0){
//    // get the byte data from the GPS
//    byte gpsData = ss.read();
//    Serial.write(gpsData);
//  }
}

void moveForward() {
  digitalWrite(LP, HIGH);
  digitalWrite(RP, HIGH);
}

void moveLeft() {
  digitalWrite(LP, LOW);
  digitalWrite(RP, HIGH);
}

void moveRight() {
  digitalWrite(LP, HIGH);
  digitalWrite(RP, LOW);
}

void halt() {
  digitalWrite(LP, LOW);
  digitalWrite(RP, LOW);
}

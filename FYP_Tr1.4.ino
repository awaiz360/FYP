#include <Wire.h>
#include <VL53L0X.h>
#include <Stepper.h>

VL53L0X sensor;
Stepper base(100, 6, 9, 10, 11);

int pos = 0;

void setup() {
  
  Serial.begin(115200);
  Wire.begin();

//  sensor.setTimeout(500);
//  if (!sensor.init())
//  {
//    Serial.println("Failed to detect and initialize sensor!");
//    while (1) {}
//  }

  sensor.startContinuous();

  //base.setSpeed(60);
}

void loop() {

//  for (int i = 0; i <= 180; i++) {
//    base.step(1);
//    dist(i);
//    delay(50);
//  }
//
//  for (int i = 180; i >= 0; i--) {
//    base.step(-1);
//    dist(i);
//    delay(50);
//  }

  base.step(1);
  delay(5);
}

void dist(int i) {

  Serial.print(i);                    
  Serial.print(",");                             
  Serial.print(sensor.readRangeContinuousMillimeters() / 10);
  
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  Serial.print(".");
}

#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

VL53L0X sensor;
Servo base;

int pos = 0;

void setup() {
  
  Serial.begin(115200);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();

  base.attach(9);
}

void loop() {

  for (pos = 15; pos <= 165; pos += 2) {
    base.write(pos);   
    dist(pos);           
    delay(5);                  
  }
  for (pos = 165; pos >= 15; pos -= 2) { 
    base.write(pos);
    dist(pos);            
    delay(5);                 
  }
}

void dist(int i) {

  Serial.print(i);                    
  Serial.print(",");                             
  Serial.print(sensor.readRangeContinuousMillimeters() / 10);
  
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  Serial.print(".");
}

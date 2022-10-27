#include <Servo.h>

#define TRG 3
#define ECH 4
#define SRV 9

Servo base;

int pos = 0;

void setup() {
  
  pinMode(TRG, OUTPUT);
  pinMode(ECH, INPUT);
  pinMode(SRV, OUTPUT);

  base.attach(SRV);

  Serial.begin(9600);
}

void loop() {

  servoSweep();

  Serial.print("Angle: ");
  Serial.print(pos);
  Serial.print(", Dist: ");
  Serial.println(dist());

}

void servoSweep() {
  
  for (pos = 30; pos <= 150; pos += 1) { 
    base.write(pos);              
    delay(15);                       
  }
  for (pos = 150; pos >= 30; pos -= 1) { 
    base.write(pos);              
    delay(15);                      
  }
}

long dist() {

  unsigned long d;
  
  digitalWrite(TRG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);

  d = pulseIn(ECH, HIGH);
  
  return (d / 29 / 2);
}

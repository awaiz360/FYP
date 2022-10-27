#define TRGL 3
#define ECHL 4
#define TRGM 5
#define ECHM 6
#define TRGR 7
#define ECHR 8

void setup() {
  pinMode(TRGL, INPUT);
  pinMode(ECHL, INPUT);
  pinMode(TRGM, INPUT);
  pinMode(ECHM, INPUT);
  pinMode(TRGR, INPUT);
  pinMode(ECHR, INPUT);

  Serial.begin(9600);
}

void loop()
{
  float S_left, S_mid, S_right;
  unsigned long d_1, d_2, d_3;

  digitalWrite(TRGL, LOW);
  delayMicroseconds(2);
  digitalWrite(TRGL, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRGL, LOW);

  d_1 = pulseIn(ECHL, HIGH);
  S_left = (d_1 * 0.034 / 2) / 100;

  digitalWrite(TRGM, LOW);
  delayMicroseconds(2);
  digitalWrite(TRGM, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRGM, LOW);

  d_2 = pulseIn(ECHM, HIGH);
  S_mid = (d_2 / 29 / 2) / 100;

  digitalWrite(TRGR, LOW);
  delayMicroseconds(2);
  digitalWrite(TRGR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRGR, LOW);

  d_3 = pulseIn(ECHR, HIGH);
  S_right = (d_3 / 29 / 2) / 100;

  Serial.print("{");
  Serial.print(S_left);
  Serial.print(",");
  Serial.print(S_mid);
  Serial.print(",");
  Serial.print(S_right);
  Serial.println("}");

  delay(200);
}

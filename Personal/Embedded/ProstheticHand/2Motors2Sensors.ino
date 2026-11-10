//Made by Georgy Rached. Base code for basic motors from https://lastminuteengineers.com/tb6612fng-dc-motor-control-arduino-tutorial/

// motor A connections
int pwmA = 3;
int Ain1 = 6; // pin 5 was faulty, moved to 6 but it works in blinked led
int Ain2 = 4;

// motor B connections
int pwmB = 9;
int Bin1 = 7;
int Bin2 = 8;

const int flexpin1 = A1; //flex sensor 1, controls Motor A
const int flexpin2 = A2; //flex sensor 2, controls Motor B
const int thresholdFullbend = 800;  // Straight ~1023, full bend ~400

//timer for each motor
unsigned long motorAstopTime   = 0;
unsigned long motorAreverseEnd = 0;
unsigned long motorBstopTime   = 0;
unsigned long motorBreverseEnd = 0;
unsigned long lastPrintTime    = 0;

void setup() {
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  stopMotors();
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  int flexposition1 = analogRead(flexpin1);
  int flexposition2 = analogRead(flexpin2);

  //print every 500 ms
  if (now - lastPrintTime >= 500) {
    Serial.print("Flex1: ");
    Serial.print(flexposition1);
    Serial.print("  Flex2: ");
    Serial.println(flexposition2);
    lastPrintTime = now;
  }

  //Motor A
  if (flexposition1 < thresholdFullbend && motorAstopTime == 0 && motorAreverseEnd == 0) {
    digitalWrite(Ain1, LOW);
    digitalWrite(Ain2, HIGH); // forward
    analogWrite(pwmA, 255);
    motorAstopTime = now + 5000;
  }

  if (motorAstopTime != 0 && now >= motorAstopTime) {
    digitalWrite(Ain1, LOW);
    digitalWrite(Ain2, LOW);
    analogWrite(pwmA, 0);
    delay(200);
    digitalWrite(Ain1, HIGH);
    digitalWrite(Ain2, LOW); // reverse
    analogWrite(pwmA, 255);
    motorAreverseEnd = now + 5000;
    motorAstopTime = 0;
  }

  if (motorAreverseEnd != 0 && now >= motorAreverseEnd) {
    digitalWrite(Ain1, LOW);
    digitalWrite(Ain2, LOW);
    analogWrite(pwmA, 0);
    motorAreverseEnd = 0;
  }

  //Motor B
  if (flexposition2 < thresholdFullbend && motorBstopTime == 0 && motorBreverseEnd == 0) {
    digitalWrite(Bin1, HIGH);
    digitalWrite(Bin2, LOW); // forward
    analogWrite(pwmB, 255);
    motorBstopTime = now + 5000;
  }

  if (motorBstopTime != 0 && now >= motorBstopTime) {
    digitalWrite(Bin1, LOW);
    digitalWrite(Bin2, LOW);
    analogWrite(pwmB, 0);
    delay(200);
    digitalWrite(Bin1, LOW);
    digitalWrite(Bin2, HIGH); // reverse
    analogWrite(pwmB, 255);
    motorBreverseEnd = now + 5000;
    motorBstopTime = 0;
  }

  if (motorBreverseEnd != 0 && now >= motorBreverseEnd) {
    digitalWrite(Bin1, LOW);
    digitalWrite(Bin2, LOW);
    analogWrite(pwmB, 0);
    motorBreverseEnd = 0;
  }

  delay(20);
}

void stopMotors() {
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

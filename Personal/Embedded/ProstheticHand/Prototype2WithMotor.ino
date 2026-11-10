//Made by Georgy Rached. Base code for basic motors from https://lastminuteengineers.com/tb6612fng-dc-motor-control-arduino-tutorial/

// motor A connections
int pwmA = 3;
int Ain1 = 5;
int Ain2 = 4;

// motor B connections
int pwmB = 9;
int Bin1 = 7;
int Bin2 = 8;


const int flexpin1 = A1; //initializing pin that reads voltage
const int thresholdFullbend = 650;  // Straight ~1023, half bend ~850, full bend ~650
const int thresholdHalfbend = 900; //threshold to activate a half bend


void setup() {

  //setting PWM and motors pins
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  //stop motors first thing to not cause any twitches
  stopMotors();

  //begin serial monitor
  Serial.begin(9600);
}


void loop() {

  //read the flex positions
  int flexposition1 = analogRead(flexpin1);

  //print out voltage reading
  Serial.print("Flex: ");
  Serial.println(flexposition1);

  //if certain voltage read, move motor for x seconds
  if (flexposition1 < thresholdFullbend) {
    runMotorA(5000); // full bend = Motor A runs 5 seconds
  }
  else if (flexposition1 < thresholdHalfbend) {
    runMotorB(1000); // Half bend = Motor B runs 1 second
  }

  //delay
  delay(100);
}


//start motor A function, with duration as input
void runMotorA(int duration) {
  
  //turn motors on
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(pwmA, 255); //0-225, 255 as highest

  //make the motor move for the duration before turning it off
  delay(duration);

  //stopping the motor
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  analogWrite(pwmA, 0);
}

//samne thing as runMotorA but for the second motor. Can repeat this process for as many motos
//may be better to use a function later on if we have 4 motors to reduce redudancy
void runMotorB(int duration) {
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmB, 255);

  delay(duration);

  // Stop Motor B only
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmB, 0);
}

//function to stop all motors]
void stopMotors() {
  
  //setting everything to 0 
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}
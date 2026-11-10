

// Include the servo library to add servo-control functions:

#include <Servo.h> 



Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int flexpin1 = 1; 
const int flexpin2 = 2;
const int flexpin3 = 3;
const int flexpin4 = 4;

void setup() 
{ 

  Serial.begin(9600);


  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);

} 


void loop() 
{ 
  int flexposition1;   
  int servoposition1;  
  
  int flexposition2;   
  int servoposition2; 
  
  int flexposition3;   
  int servoposition3; 
  
  int flexposition4;   
  int servoposition4; 
  

  flexposition1 = analogRead(flexpin1);
  flexposition2 = analogRead(flexpin2);
  flexposition3 = analogRead(flexpin3);
  flexposition4 = analogRead(flexpin4);

  servoposition1 = map(flexposition1, 59, 256, 0, 180);
  servoposition1 = constrain(servoposition1, 0, 180);
  
  servoposition2 = map(flexposition2, 59, 256, 0, 180);
  servoposition2 = constrain(servoposition2, 0, 180);
  
  servoposition3 = map(flexposition3, 59, 256, 0, 180);
  servoposition3 = constrain(servoposition3, 0, 180);
  
  servoposition4 = map(flexposition4, 59, 256, 0, 180);
  servoposition4 = constrain(servoposition4, 0, 180);

  servo1.write(servoposition1);
  servo2.write(servoposition2);
  servo3.write(servoposition3);
  servo4.write(servoposition4);
 
	Serial.print("F1:"); Serial.print(flexposition1);
	Serial.print(" F2:"); Serial.print(flexposition2);
	Serial.print(" F3:"); Serial.print(flexposition3);
	Serial.print(" F4:"); Serial.print(flexposition4);
	

  delay(20);  
} 

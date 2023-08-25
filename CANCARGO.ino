#include <NewPing.h>
#include <BTS7960.h>
#include <Servo.h>
#define RPWM 5
#define LPWM 6
#define EN 7     
#define servoPin 4
#define trigPin 10
#define echoPin 11
#define MAXD 400
const int obt = 60;
const int rdc = 10;
BTS7960 mainMotor(EN, LPWM, RPWM);
Servo myservo;
NewPing sonar(trigPin, echoPin, MAXD);
float duration, distance;
int iterations = 10;
int servoAngle = 90;
int turnDelay = 500;
int speed = 255;
void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  mainMotor.Enable();
}
void loop() {
 duration = sonar.ping_median(iterations);
 distance = (duration/2)*0.0343;
  if(distance > obt){
    mainMotor.TurnRight(speed);
    servoAngle = 90;
    myservo.write(servoAngle);
  }   
  
  if (distance <= obt && distance >= rdc) {
    changeSpeed();
    changeDirection();
    delay(turnDelay);
    mainMotor.TurnRight(255);
    dataCollection();
  }
  if(distance < rdc){
    servoAngle = 90;
    myservo.write(servoAngle);
    delay(turnDelay);
    mainMotor.TurnLeft(255);
    dataCollection();
  }
}
void changeDirection(){
  servoAngle += 10;
  if (servoAngle > 160) {
    servoAngle = 160;
  }
  myservo.write(servoAngle);
}
void changeSpeed(){
  speed -= 10;
  if (speed < 50){
    speed = 50;
  }
}
void dataCollection(){
  Serial.println(distance);
  Serial.println(servoAngle);
}
 

  

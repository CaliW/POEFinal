
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(2);

//a = 0;
//b = 0;
//c = 0;
//d = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
  AFMS.begin();
  myMotorLeft->setSpeed(0);
  myMotorRight->setSpeed(0);
  myMotorLeft->run(RELEASE);
  myMotorRight->run(RELEASE);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(4);  //if this reads as high, robot goes straight
  int b = digitalRead(5);  //if high, goes right
  int c = digitalRead(6);  //if high, goes left
  int d = digitalRead(7);  //if high, robot stops
  Serial.print("a");
  Serial.print(a);
  Serial.print("  b");
  Serial.print(b);
  Serial.print("  c");
  Serial.print(c);
  Serial.print("  d");
  Serial.println(d);
  if (d == 1){
    //stop
    myMotorRight->run(RELEASE);
    myMotorLeft->run(RELEASE);
  }
  else if (a == 1){
    //go straight
    myMotorRight->setSpeed(100);
    myMotorRight->run(FORWARD);
    myMotorLeft->setSpeed(100);
    myMotorLeft->run(FORWARD);
  }
  else if (b == 1){
    //go right
    myMotorRight->setSpeed(150);//arb
    myMotorRight->run(FORWARD);
    myMotorLeft->setSpeed(50);//arb
    myMotorLeft->run(FORWARD);//backward
  }
  else if (c == 1){
    //go left
    myMotorRight->setSpeed(50);//arb
    myMotorRight->run(FORWARD); //backward
    myMotorLeft->setSpeed(150);//arb
    myMotorLeft->run(FORWARD);
  }
}

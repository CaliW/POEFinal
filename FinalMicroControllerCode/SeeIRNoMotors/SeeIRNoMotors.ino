
int trigPin = 9;    // Triggers ultrasonic sensor 1
int echoPin1 = 10;    // Echo1
int echoPin2 = 11;    // Echo2
int echoPin3 = 12;    // Echo3
int echoPin4 = 13;    // Echo4
//int echoPinB = 8
long duration1, duration2, duration3, duration4, cm1, cm2, cm3, cm4, Pcm1, Pcm2, Pcm3, Pcm4=0; //introduces values?
//duration5, cm5, Pcm5?
int n = 0;   //keeps track of case #
int prevA=0;
long newTime = 0; //initializes time for millis()
int waitTime = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);  //all 4 sensors share same trigger pin
  pinMode(echoPin1, INPUT);  //1st sensor, far left
  pinMode(echoPin2, INPUT);  //2nd sensor, front left
  pinMode(echoPin3, INPUT);  //3rd sensor, front right
  pinMode(echoPin4, INPUT);  //4th sensor, far right
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(3,INPUT);
  //pinMode(echoPinB, INPUT); //sensor on back
  Serial.begin(9600);
}

void loop() {
  int a = digitalRead(3); //reads value from TSOP4840 IR sensor
  //Serial.println(a);
  if (a == 0 && prevA == 1)  //if value read == 0, flash was detected
  {
    pulse(); //pulses 1 of the 4 sensors each time IR flash is detected (~200ms)
    if (n == 0){
        if (abs(cm3-cm2) < 8){ 
          Serial.println("straight");
          digitalWrite(4,HIGH); //writing the 4th digital pin to high signifies that the robot should go straight
          digitalWrite(5,LOW);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
        }
        else if (cm2 > cm3){
          Serial.println("right");
          digitalWrite(4,LOW);
          digitalWrite(5,HIGH);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
        }
        else if (cm3 > cm2){
          Serial.println("left");
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          digitalWrite(6,HIGH);
          digitalWrite(7,LOW);
        }
        else if (cm3 > 500 || cm2 > 500){
          Serial.println("motors stop");
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          digitalWrite(6,LOW);
          digitalWrite(7,HIGH);
        }
      }
    newTime = millis();//sets current time
  }
  //this tells the motor to stop if it doesn't see the IR sensor after a set amount of time
  //this ensures that the robot stops when the beacon is off or when the robot is turned the wrong way
  //no runaway robot
  else if (millis() - newTime > waitTime){
    Serial.println("motors stop");
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
  prevA = a;
}

void pulse() {  //arduino can only read one sensor at a time
                //but when timed correctly, it can read all 4 sensors in under a second
  switch (n) //switch determines which case will be called each time
  {
    case 0:
        //code executed if n == 0
        pulse1();
        break;

    case 1:
        //if n == 1
        pulse2();
        break;
        
    case 2:
        pulse3();
        break;

    case 3:
        pulse4();
        break;
  }
  n = (n+1)%4; //basically n++ in a loop
}

int pulse1(){  //long pulse1()  cm1 initiated as long
  digitalWrite(trigPin, LOW); //start trigger process
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);      //sends trigger signal of  length 10us
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin1, HIGH,150000);//duration = time it takes for signal to go between sensors
  //pulseIn(pin#, pin value, timeout) // timeout = 150000us = 150ms
  cm1 = (duration1)/29.1;  //converts time to distance
  if (cm1 > 4000){
    cm1 = Pcm1;
  }
  Serial.print("(1):  ");
  Serial.print(cm1);
  Pcm1 = cm1;
  return cm1;
}

int pulse2(){
  digitalWrite(trigPin, LOW); //start trigger process
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration2 = pulseIn(echoPin2, HIGH,150000); //,150000
  cm2 = (duration2)/29.1;
  if (cm2 > 4000){
    cm2 = Pcm2;
  }
  Serial.print("   (2):  ");
  Serial.print(cm2);
  Pcm2 = cm2;
  return cm2;
}

int pulse3(){
  digitalWrite(trigPin, LOW); //start trigger process
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration3 = pulseIn(echoPin3, HIGH,150000);
  cm3 = (duration3)/29.1;
  if (cm3 > 4000){
    cm3 = Pcm3;
  }
  Serial.print("   (3):  ");
  Serial.print(cm3);
  Pcm3 = cm3;
  return cm3;
}

int pulse4(){
  digitalWrite(trigPin, LOW); //start trigger process
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration4 = pulseIn(echoPin4, HIGH,150000);
  cm4 = (duration4)/29.1;
  if (cm4 > 4000){
    cm4 = Pcm4;
  }
  Serial.print("   (4):  ");
  Serial.println(cm4);
  Pcm4 = cm4;
  return cm4;
}

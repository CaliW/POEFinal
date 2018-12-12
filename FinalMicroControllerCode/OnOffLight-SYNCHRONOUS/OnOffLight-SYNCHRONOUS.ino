//Beacon code: Precisely controls and times the IR flashes and triggers the beacons ultrasonic sensor
//Use physical switch to turn on/off IR light

int trigPin = 10;    // Ultrasonic Trigger
int echoPin = 11;    // Echo
int blinkTime = 150;
long startT = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);    //controls IR light
  pinMode(trigPin, OUTPUT);  //sets ultra trigger pin
  Serial.begin(9600);

}

void loop() //flashes IR at 40kHz or 0Hz in .1 second intervals (on/off 5x/second)
{
  digitalWrite(9,LOW); //flash IR off
  startT = millis(); //sets current time


  //Keeps IR light off with micro delasy until blinks are supposed to start
  while (millis() - startT < blinkTime) {
    delayMicroseconds(1);
  }

  // For the first blink square wave, let's start the sonar and start the blink at the same time
  digitalWrite(9,HIGH);  //IR on
  delayMicroseconds(16.666666);
  digitalWrite(trigPin, LOW); //start trigger process
  
  digitalWrite(9,LOW);   //IR off
  delayMicroseconds(6.666666);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  while (millis() - startT < blinkTime + 150) //in between time 100 and 200, IR is flashing at 40kHz
  {
    digitalWrite(9,HIGH);  //IR on
    delayMicroseconds(16.666666); //16.666666... microsecond delay = 40kHz
    digitalWrite(9,LOW);   //IR off
    delayMicroseconds(16.666666);
  }
  
}

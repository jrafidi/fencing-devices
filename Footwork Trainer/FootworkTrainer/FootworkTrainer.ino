// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int lowLimit = 50;
int highLimit = 130;
int pos = 90;
int delayStep = 200;

int speedLimit = 100;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  myservo.write(pos);
  
  int stepSize = (int) (analogRead(1) / 100);

  int nextStep;
  if (pos <= lowLimit) {
    nextStep = stepSize;
  } else if (pos >= highLimit) {
    nextStep = -1 * stepSize;
  } else {
    long seed = random(2);
    if (seed == 1) {
      nextStep = stepSize;
    } else {
      nextStep = -1 * stepSize;
    }
  }
  
  pos = pos + nextStep;
  delay(max(analogRead(0), speedLimit));
} 

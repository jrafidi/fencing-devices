#include <Servo.h> 
 
Servo myservo;

int SERVO_PIN = 9;
int SPEED_PIN = 0;
int SPEED_VARIANCE_PIN = 1;
int STEP_SIZE_PIN = 2;
int RANGE_PIN = 3;

float limitDenominator = 1024/60;

int midPoint = 90;
int limitMin = 15;
int pos = 90;
int delayStep = 200;
int speedLimit = 100;

boolean firstPass = true;
 
void setup() 
{ 
  myservo.attach(SERVO_PIN);
}
 
void loop() 
{ 
  myservo.write(pos);
  
  if (firstPass) {
    delay(5000);
    firstPass = false;
  }

  int stepSize = (int) (analogRead(STEP_SIZE_PIN) / 100);
  stepSize = max(stepSize, 1);

  int limit = (int) (analogRead(RANGE_PIN) / limitDenominator);

  int nextStep;
  if (pos <= (midPoint - limit - limitMin)) {
    nextStep = stepSize;
  } else if (pos >= (midPoint + limit + limitMin)) {
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

  int delayTime = analogRead(SPEED_PIN);
  int timeVariance = (int) random(analogRead(SPEED_VARIANCE_PIN));
  long seed = random(2);
  if (seed == 1) {
    delayTime = delayTime + timeVariance;
  } else {
    delayTime = delayTime - timeVariance;
  }

  delay(max(delayTime, speedLimit));
} 

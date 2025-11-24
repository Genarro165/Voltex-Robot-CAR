#include "DistanceSensor.h"

int leftDistance_cm;
int rightDistance_cm;
int middleDistance_cm;
void distanceSensorInit(){
 pinMode(leftEchoPin, INPUT);
 pinMode(rightEchoPin, INPUT);
 pinMode(middleEchoPin, INPUT);
 pinMode(trigPin, OUTPUT);
 digitalWrite(trigPin, LOW);
}
void trigger(){
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
}
void distanceSensorUpdate(){
  trigger();
  unsigned long leftDuration = pulseIn(leftEchoPin, HIGH, 10000);
  leftDistance_cm = leftDuration * 0.034 / 2;
  trigger();
  unsigned long rightDuration = pulseIn(rightEchoPin, HIGH, 10000);
  rightDistance_cm = rightDuration * 0.034 / 2;
  trigger();
  unsigned long middleDuration = pulseIn(middleEchoPin, HIGH, 10000);
  middleDistance_cm = middleDuration * 0.034 / 2;
}

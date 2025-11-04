#include "DistanceSensor.h"

int leftDistance_cm;
int rightDistance_cm;
int middleDistance_cm;
void distanceSensorInit(){
 DDRD &= ~(PDleftEchoPin|PDrightEchoPin|PDmiddleEchoPin);
 DDRB |= (PBtrigPin);
 PORTB |= ~(PBtrigPin);
}
void trigger(){
 PORTB |= (PBtrigPin);
 _delay_us(10);
 PORTB |= ~(PBtrigPin);
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
/* void distanceSensorUpdate(){
unsigned long leftDuration = pulseIn(leftEchoPin, HIGH, 10000);
  leftDistance_cm = leftDuration * 0.034 / 2;
} */

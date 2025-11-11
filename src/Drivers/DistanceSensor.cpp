#include <avr/io.h>
#include <avr/interrupt.h>
#include "DistanceSensor.h"
#include "Util.h"

int leftDistance_cm;
int rightDistance_cm;
int middleDistance_cm;
int leftTimeStart;
int rightTimeStart;
int middleTimeStart;
int lastPinDState;
void distanceSensorInit(){
 // setting echo pins to input
 DDRD &= ~(PDleftEchoPin|PDrightEchoPin|PDmiddleEchoPin);
 // setting trig pin as output 
 DDRB |= (PBtrigPin);
 // trig pin == 0
 PORTB |= ~(PBtrigPin);
 // setting echo pins to enable interupts on both rising and falling edge
 EICRA &= ~(1 << ISC11);
 EICRA |= (1 << ISC10);
 EIMSK |= (1 << INT1);
 PCICR |= (1 << PCIE2);
 PCMSK2 |= (1 << PCINT20) | (1 << PCINT21);
 sei();
 lastPinDState = PIND;
}
void trigger(){
 PORTB |= (PBtrigPin);
 _delay_us(10);
 PORTB |= ~(PBtrigPin);
}
//left pin interupt
ISR(INT1_vect){
 if (PIND & PDleftEchoPin){
  leftTimeStart = ticks;
 }
 else {
  uint leftDuration = ticks- leftTimeStart;
   leftDistance_cm = leftDuration * 0.034 / 2;
   leftTimeStart = 0; 
 } 
}
// middle and right pin interupts
ISR(PCINT2_vect){
 uint8_t changed = PIND ^ lastPinDState; // which pins changed?
 lastPinDState = PIND;

 if (changed & PDmiddleEchoPin) {
        // PD4 changed
  if (PIND & PDmiddleEchoPin) {
   middleTimeStart = ticks;  // Rising edge on PD4
  }
  else {
   uint middleDuration = ticks- middleTimeStart;
   middleDistance_cm = middleDuration * 0.034 / 2;  // Falling edge on PD4
   middleTimeStart = 0;
  }
 }
 if (changed & PDrightEchoPin) {
        // PD5 changed
  if (PIND & PDrightEchoPin) {
   rightTimeStart = ticks;  // Rising edge on PD5
  }
  else {
   uint rightDuration = ticks- rightTimeStart;
   rightDistance_cm = rightDuration * 0.034 / 2;
   rightTimerStart = 0;
  }
 }

/*
void distanceSensorUpdate(){
  trigger();
  unsigned long leftDuration = pulseIn( leftEchoPin, HIGH, 10000);
  leftDistance_cm = leftDuration * 0.034 / 2;
  trigger();
  unsigned long rightDuration = pulseIn(rightEchoPin, HIGH, 10000);
  rightDistance_cm = rightDuration * 0.034 / 2;
  trigger();
  unsigned long middleDuration = pulseIn(middleEchoPin, HIGH, 10000);
  middleDistance_cm = middleDuration * 0.034 / 2;
}
*/

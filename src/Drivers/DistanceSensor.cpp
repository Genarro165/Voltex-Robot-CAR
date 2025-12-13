
#include "DistanceSensor.h"

int leftDistance_cm;
int rightDistance_cm;
int middleDistance_cm;
int leftTimeStart;
int rightTimeStart;
int middleTimeStart;
int lastPinDState;

struct Task triggerTask = {
  .interval = MS_TO_TICKS(100),
  .lastUpdate = 0,
  .callback = &trigger
};

void distanceSensorInit(){
 
 // setting echo pins to input
 DDRD &= ~(PDLEFTECHOPIN|PDRIGHTECHOPIN|PDMIDDLEECHOPIN);
 // setting trig pin as output 
 DDRB |= (PBTRIGPIN);
 // trig pin == 0
 PORTB |= ~(PBTRIGPIN);
 // setting echo pins to enable interupts on both rising and falling edge
 PCICR |= (1 << PCIE2);
 PCMSK2 |= ((1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22));
 sei();
 lastPinDState = PIND;
 registerTask(&triggerTask);
}

void trigger(struct Task* myTask) {
 PORTB |= (PBTRIGPIN);
 _delay_us(10);
 PORTB |= ~(PBTRIGPIN);
}

#ifndef ARDUINO_CORE
//left pin interupt


// middle and right pin interupts
ISR(PCINT2_vect){
 uint8_t changed = PIND ^ lastPinDState; // which pins changed?
 lastPinDState = PIND;

 if (changed & PDMIDDLEECHOPIN) {
        // PD4 changed
  if (PIND & PDMIDDLEECHOPIN) {
   middleTimeStart = ticks;  // Rising edge on PD4
  }
  else {
   uint16_t middleDuration = ticks - middleTimeStart;
   middleDistance_cm = middleDuration * 0.45;  // Falling edge on PD4
   middleTimeStart = 0;
  }
 }
 if (changed & PDRIGHTECHOPIN) {
        // PD5 changed
  if (PIND & PDRIGHTECHOPIN) {
   rightTimeStart = ticks;  // Rising edge on PD5
  }
  else {
   uint16_t rightDuration = ticks - rightTimeStart;
   rightDistance_cm = rightDuration * 0.45;
   rightTimeStart = 0;
  }
 }
 if (changed & PDLEFTECHOPIN) {
        // PD5 changed
  if (PIND & PDLEFTECHOPIN) {
   leftTimeStart = ticks;  // Rising edge on PD5
  }
  else {
   uint16_t leftDuration = ticks - leftTimeStart;
   leftDistance_cm = leftDuration * 0.45;
   leftTimeStart = 0;
  }
 }
}

void distanceSensorUpdate() {

}

#else


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

#endif










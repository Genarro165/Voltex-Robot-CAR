#include "MotorDriver.h"

enum MotorState currentMotorState = HALTED;


unsigned char currentMotorASpeed = 0;
unsigned char currentMotorBSpeed = 0;
  const int timer1_pwm_freq = 60;

  // Fast PWM, 8-bit, non-inverting, prescaler 64


  void timer1_init() {
   TCCR1A = 0;
   TCCR1B = 0;

   TCCR1A |= (1 << COM1A1) | (1 << WGM11);
   TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);

   //timer1 top value
   ICR1 = (F_CPU/(64*timer1_pwm_freq)) - 1;
  }

  void timer1_set_pwm(uint8_t duty_cycleA, uint8_t duty_cycleB) {
      OCR1A = ICR1 / (100 / duty_cycleA);
      OCR1B = ICR1 / (100 / duty_cycleB);
  }




static void setMotorParams(bool a_in1, bool a_in2, bool b_in3, bool b_in4) {


  timer1_set_pwm(currentMotorASpeed, currentMotorBSpeed);


       if (a_in1 == true)
            PORTD |= (MOTOR_A_IN1);
        else
            PORTD &= ~(MOTOR_A_IN1);
       if (a_in2 == true)
            PORTD |= (MOTOR_A_IN2);
        else
            PORTD &= ~(MOTOR_A_IN2);
       if (b_in3 == true)
            PORTD |= (MOTOR_B_IN3);
        else
            PORTD &= ~(MOTOR_B_IN3);
     if (b_in4 == true)
            PORTD |= (MOTOR_B_IN4);
        else
            PORTD &= ~(MOTOR_B_IN4);
}


void setMotorSpeed(unsigned char speed) {
  currentMotorASpeed = speed;
  currentMotorBSpeed = speed;
}

void changeMotorSpeed(unsigned char speed) {
  currentMotorASpeed -= speed;
  currentMotorBSpeed -= speed;
}
void motorDriverInit(){
  DDRD |= (MOTOR_A_PWM | MOTOR_B_PWM | MOTOR_A_IN1 | MOTOR_A_IN2 | MOTOR_B_IN3 | MOTOR_B_IN4);  
}
void setMotorState(enum MotorState newMotorState) {
  if (currentMotorState == newMotorState) {
    return;
  }
  switch(newMotorState) { //this can be written a lot better but i dint have the time to make it better
    case HALTED:
      setMotorSpeed(0);
      setMotorParams(0, 0, 0, 0);
      break;
    case FORWARDS:
      setMotorParams(true, false, true, false);
      break;
    case BACKWARDS:
      setMotorParams(false, true, false, true);
    case LEFT:
      currentMotorASpeed = (unsigned char) currentMotorASpeed*TURN_FACTOR;
      currentMotorBSpeed = (unsigned char) currentMotorBSpeed*(1 + TURN_FACTOR);
      setMotorParams(true, false, true, false);
      break;
    case RIGHT:
      currentMotorASpeed = (unsigned char) currentMotorASpeed*(1 + TURN_FACTOR);
      currentMotorBSpeed = (unsigned char) currentMotorBSpeed*TURN_FACTOR;
      setMotorParams(true, false, true, false);
      break;
    case HARD_LEFT:
      setMotorParams(false, true, true, false);
      break;
    case HARD_RIGHT:
      setMotorParams(true, false, false, true);
    default:
      break;
  }
}






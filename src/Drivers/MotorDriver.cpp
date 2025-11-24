#include "MotorDriver.h"

enum MotorState currentMotorState = HALTED;


unsigned char currentMotorASpeed = 0;
unsigned char currentMotorBSpeed = 0;

static void setMotorParams(int a_in1, int a_in2, int b_in3, int b_in4) {
  analogWrite(MOTOR_A_PWM, currentMotorASpeed);
  analogWrite(MOTOR_B_PWM, currentMotorBSpeed);
  digitalWrite(MOTOR_A_IN1, a_in1);
  digitalWrite(MOTOR_A_IN2, a_in2);
  digitalWrite(MOTOR_B_IN3, b_in3);
  digitalWrite(MOTOR_B_IN4, b_in4);
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
  pinMode (MOTOR_A_PWM, OUTPUT);
  pinMode (MOTOR_B_PWM, OUTPUT);
  pinMode (MOTOR_A_IN1, OUTPUT);
  pinMode (MOTOR_A_IN2, OUTPUT);
  pinMode (MOTOR_B_IN3, OUTPUT);
  pinMode (MOTOR_B_IN4, OUTPUT);  
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
      setMotorParams(LOW, HIGH, LOW, HIGH);
      break;
    case BACKWARDS:
      setMotorParams(HIGH, LOW, HIGH, LOW);
    case LEFT:
      currentMotorASpeed = (unsigned char) currentMotorASpeed*TURN_FACTOR;
      currentMotorBSpeed = (unsigned char) currentMotorBSpeed*(1 + TURN_FACTOR);
      setMotorParams(LOW, HIGH, LOW, HIGH);
      break;
    case RIGHT:
      currentMotorASpeed = (unsigned char) currentMotorASpeed*(1 + TURN_FACTOR);
      currentMotorBSpeed = (unsigned char) currentMotorBSpeed*TURN_FACTOR;
      setMotorParams(LOW, HIGH, LOW, HIGH);
      break;
    case HARD_LEFT:
      setMotorParams(HIGH, LOW, LOW, HIGH);
      break;
    case HARD_RIGHT:
      setMotorParams(LOW, HIGH, HIGH, LOW);
    default:
      break;
  }
}




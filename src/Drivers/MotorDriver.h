#pragma once
#include <Arduino.h>

//motor A is the left channel and motor B is the right channel

#define MOTOR_A_PWM 6
#define MOTOR_B_PWM 5

#define MOTOR_A_IN1 3
#define MOTOR_A_IN2 2
#define MOTOR_B_IN3 7
#define MOTOR_B_IN4 4

//this controls the turn speed of the gradual turns
#define TURN_FACTOR 0.75

enum MotorState {
  HALTED,   //this state turns everything off
  FORWARDS, 
  BACKWARDS,
  LEFT,     //this state does a gradual left turn
  RIGHT,    //this does a gradual right turn
  HARD_LEFT,//this does an in place turn
  HARD_RIGHT
};

//the current motor direction
extern enum MotorState currentMotorState;

//set the absolute speed of the motors
void setMotorSpeed(unsigned char speed);

//chang the speed by a relative amount
void changeMotorSpeed(unsigned char speed);

//set the direction of the car
void setMotorState(enum MotorState newMotorState);
void motorDriverInit();


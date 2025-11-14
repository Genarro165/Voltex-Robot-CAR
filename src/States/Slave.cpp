#include "Slave.h"

void slaveState(struct State* currState){
  if (lineSensors[0] && lineSensors[1] && lineSensors[2] && lineSensors[3] ){
    setMotorState(FORWARDS);
  }
  else if(lineSensors[1] == HIGH){
    setMotorState(LEFT);
  }
  else if(lineSensors[0] == HIGH){
    setMotorState(HARD_LEFT);
  }
  else if(lineSensors[2] == HIGH){
    setMotorState(RIGHT);
  }
   else if(lineSensors[3] == HIGH){
    setMotorState(HARD_RIGHT);
  } 
  else{
      if (currState->id == Slave) {
            currState->id = Idle;
      }
   }
  if (middleDistance_cm <20){
    changeMotorSpeed(-10);
  }
  else if (middleDistance_cm >40){
    changeMotorSpeed(10);
  }
}



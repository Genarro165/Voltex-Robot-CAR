#include "LineSensor.h"
int lineSensors [4] ={0};
void lineSensorInit(){
  DDRC &= ~(HLS_PIN|MLS_PIN|MRS_PIN|HMS_PIN);
}
void lineSensorUpdate(){
  lineSensors[0] = PINC & HLS_PIN;
  lineSensors[1] = PINC & MLS_PIN;
  lineSensors[2] = PINC & MRS_PIN;
  lineSensors[3] = PINC & HRS_PIN;
}










#include "LineSensor.h"
int lineSensors [4] ={0};
void lineSensorInit(){
  pinMode (HLS_PIN, INPUT);
  pinMode (MLS_PIN, INPUT);
  pinMode (MRS_PIN, INPUT);
  pinMode (HRS_PIN, INPUT);
}
void lineSensorUpdate(){
  lineSensors[0] = digitalRead(HLS_PIN);
  lineSensors[1] = digitalRead(MLS_PIN);
  lineSensors[2] = digitalRead(MRS_PIN);
  lineSensors[3] = digitalRead(HRS_PIN);
}








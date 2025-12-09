#include "LineSensor.h"
#include "PortExpander.h"
int lineSensors [4] ={0};

void lineSensorInit(){
  portExpanderWrite(portExpanderMode|(HLS_PIN | MLS_PIN | MRS_PIN | HRS_PIN));
}

void lineSensorUpdate(){
  lineSensors[0] = portExpanderData & HLS_PIN;
  lineSensors[1] = portExpanderData & MLS_PIN;
  lineSensors[2] = portExpanderData & MRS_PIN;
  lineSensors[3] = portExpanderData & HRS_PIN;
}




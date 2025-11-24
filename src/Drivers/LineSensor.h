#pragma once
#include <Arduino.h>
#define HLS_PIN A0
#define MLS_PIN A1
#define MRS_PIN A2
#define HRS_PIN A3

extern int lineSensors[4];
void lineSensorInit();
void lineSensorUpdate();






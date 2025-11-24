#pragma once
#include <Arduino.h>
#define trigPin  8
#define leftEchoPin  11
#define rightEchoPin  9
#define middleEchoPin 10

extern int leftDistance_cm;
extern int middleDistance_cm;
extern int rightDistance_cm;
void distanceSensorUpdate();
void distanceSensorInit();

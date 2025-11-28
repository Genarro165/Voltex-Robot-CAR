#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Util.h"

#ifdef ARDUINO_CORE

#include <Arduino.h>

#endif

#define PBtrigPin (1<<0)
#define PDleftEchoPin (1<<4)
#define PDmiddleEchoPin (1<<5)
#define PDrightEchoPin (1<<6)

extern int leftDistance_cm;
extern int middleDistance_cm;
extern int rightDistance_cm;
void distanceSensorUpdate();
void distanceSensorInit();


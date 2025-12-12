#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Util.h"

#ifdef ARDUINO_CORE

#include <Arduino.h>

#endif

#define PBTRIGPIN (1<<0)
#define PDLEFTECHOPIN (1<<4)
#define PDMIDDLEECHOPIN (1<<5)
#define PDRIGHTECHOPIN (1<<6)

extern int leftDistance_cm;
extern int middleDistance_cm;
extern int rightDistance_cm;

void trigger(struct Task* myTask);
void distanceSensorUpdate();
void distanceSensorInit();


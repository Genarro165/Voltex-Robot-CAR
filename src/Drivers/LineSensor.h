#pragma once
#include <avr/io.h>

#define HLS_PIN (1<<0)
#define MLS_PIN (1<<1)
#define MRS_PIN (1<<2)
#define HRS_PIN (1<<3)

extern int lineSensors[4];
void lineSensorInit();
void lineSensorUpdate();








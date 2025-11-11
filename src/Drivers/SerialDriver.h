#pragma once
#include <Arduino.h>
#define SERIAL_BUFFER_SIZE 32
void serialUpdate();
void serialInit();
extern bool serialInputComplete;
extern int serialInputSize;
extern char serialBuffer[SERIAL_BUFFER_SIZE];

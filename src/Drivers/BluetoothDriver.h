#pragma once

#ifdef ARDUINO_CORE

#include <Arduino.h>
#include <SoftwareSerial.h>

#else

#include "../fuck-arduino-kekw/SoftwareSerial.h"
#include "../InputManager.h"
#endif

#define BRX 4
#define BTX 5
#define BLUETOOTH_BUFFER_SIZE 32

extern char bluetoothInputString[BLUETOOTH_BUFFER_SIZE];
extern int bluetoothInputSize;
extern bool bluetoothStringComplete;
void bluetoothUpdate();
void bluetoothInit();

#pragma once
#include <SoftwareSerial.h>
#define BRX 12
#define BTX 13
#define BLUETOOTH_BUFFER_SIZE 16

extern char bluetoothInputString[BLUETOOTH_BUFFER_SIZE];
extern int bluetoothInputSize;
extern bool bluetoothStringComplete;
void bluetoothUpdate();
void bluetoothInit();

#pragma once
#include "Drivers/BluetoothDriver.h"
#include "Drivers/SerialDriver.h"
#include "MainStateMachine.h"

#define INPUT_WORD_SIZE 16
#define INPUT_MAX_ARGS 2
extern char inputBuffer[INPUT_MAX_ARGS][INPUT_WORD_SIZE];
extern unsigned char argumentCount;
void flushArguments();
int strncmp( const char * s1, const char * s2, unsigned int n );
void inputManagerUpdate();

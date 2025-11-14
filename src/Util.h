#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define seconds (ticks>>2^13);
extern volatile uint64_t ticks;

void timerZeroInit();
void timerZeroUpdate();
void eepromWrite(uint16_t address, uint8_t data);
uint8_t eepromRead(uint16_t address);

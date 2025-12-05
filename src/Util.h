#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TICKS_IN_SECONDS (ticks>>2^13);

#define SEC_TO_TICKS(SEC_T) (SEC_T*7812)

#define MS_TO_TICKS(MS_T) (MS_T*8)

extern volatile uint64_t ticks;

void timerZeroInit();
void timerZeroUpdate();

void tick_delay(uint64_t delay);

void eepromWrite(uint16_t address, uint8_t data);
uint8_t eepromRead(uint16_t address);

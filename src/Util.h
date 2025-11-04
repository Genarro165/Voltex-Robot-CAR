pragma once
extern volatile uint64_t ticks;

void timerZeroInit();
void timerZeroUpdate();
void eepromWrite();
void eepromRead();

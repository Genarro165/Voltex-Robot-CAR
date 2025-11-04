pragma once
extern volatile uint64_t ticks;

void timerZeroInit();
void timerZeroUpdate();
void eepromWrite(uint16_t address, uint8_t data);
void eepromRead(uint16_t address);

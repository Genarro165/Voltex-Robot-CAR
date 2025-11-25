#include "Util.h"
volatile uint64_t ticks;
void timerZeroInit(){
  TCCR0A = 0; // normal mode
  TCCR0B = 0;
  TCCR0B |= 0b00000010; // prescaler 8
  TIMSK0 |= 0b00000001; // enable overflow interrupt
  TCNT0 = 0;
  ticks = 0;
}

ISR(TIMER0_OVF_vect) {
   ticks++;  // One tick per overflow
}

void eepromWrite(uint16_t address, uint8_t data) {
    // Wait for completion of previous write
    while (EECR & (1 << EEPE));

    // Set up address and data
    EEAR = address;
    EEDR = data;

    // Write logical one to EEMPE
    EECR |= (1 << EEMPE);

    // Start EEPROM write by setting EEPE
    EECR |= (1 << EEPE);
}

uint8_t eepromRead(uint16_t address) {
    // Wait for completion of previous write
    while (EECR & (1 << EEPE));

    // Set up address
    EEAR = address;

    // Start EEPROM read
    EECR |= (1 << EERE);

    // Return data
    return EEDR;
}

#include <Arduino.h>
#include <stdint.h>

#define PORT_EXPANDER_ADRES 0x33

extern uint8_t portExpanderData;

//initiate write
void portExpanderWrite(uint8_t mode);
//initiate read
void portExpanderRead();

void portExpanderInit();

void portExpanderUpdate();


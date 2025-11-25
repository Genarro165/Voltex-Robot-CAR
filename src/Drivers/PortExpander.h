#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

#define PORT_EXPANDER_ADRES 0x20

extern uint8_t portExpanderData;

//initiate write
void portExpanderWrite(uint8_t mode);
//initiate read
void portExpanderRead();

void portExpanderInit();

void portExpanderUpdate();


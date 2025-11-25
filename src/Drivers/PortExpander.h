#include <avr/io.h>
#include <avr/interrupt.h>

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include <stdbool.h>

#define PORT_EXPANDER_ADRES 0x20

extern uint8_t portExpanderData;

//initiate write
void portExpanderWrite(uint8_t mode);

void portExpanderInit();

void portExpanderUpdate();


#pragma once

#include "../fuck-arduino-kekw/Wire.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#define PORT_EXPANDER_ADRES 0x20
#define PORT_EXPANDER_INT (1 << 2)

extern uint8_t portExpanderData;

//initiate write
void portExpanderWrite(uint8_t mode);

void portExpanderInit();

void portExpanderUpdate();

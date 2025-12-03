#pragma once
#include <stdint.h>
#include "avr/interrupt.h"

#define CALC_BAUD(BAUD) F_CPU/16/BAUD-1

// UART Buffer Defines
// Supported sizes: 2,4,8,16,32,64,128 or 256 bytes
#define SERIAL_RX_BUFFER_SIZE (32)
#define SERIAL_TX_BUFFER_SIZE (32)
 
// Buffer size checks
#define SERIAL_RX_BUFFER_MASK (SERIAL_RX_BUFFER_SIZE - 1)

#define SERIAL_TX_BUFFER_MASK (SERIAL_TX_BUFFER_SIZE - 1)

extern bool serialInputComplete;
extern int serialInputSize;
extern char serialInputBuffer[SERIAL_RX_BUFFER_SIZE];

void serialTransmit(char data);
void serialInit(uint16_t ubbr);


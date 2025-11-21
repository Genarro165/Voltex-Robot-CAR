#pragma once
#include <stdint.h>

#define F_CPU 16000000UL

#define CALC_BAUD(BAUD) F_CPU/16/BAUD-1

// UART Buffer Defines
// Supported sizes: 2,4,8,16,32,64,128 or 256 bytes
#define SERIAL_RX_BUFFER_SIZE (32)
#define SERIAL_TX_BUFFER_SIZE (32)
 
// Buffer size checks
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)

#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)


void serialInit();

extern bool serialInputComplete;
extern int serialInputSize;
extern char serialBuffer[SERIAL_RX_BUFFER_SIZE];



#include "SerialDriver.h"

bool serialInputComplete = false;
int serialInputSize = 0;
char serialInputBuffer[SERIAL_RX_BUFFER_SIZE] = {0};
 
static char USART_TxBuf[SERIAL_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail; 

//shouldnt this be atomic??
ISR(USART_RX_vect) {

  if (serialInputSize < SERIAL_BUFFER_SIZE) {
    char inChar = UDR0;

    if (inChar == '\r') {
      serialTransmit('\r');
      serialTransmit('\n');
      serialInputComplete = true;
    } else {
      serialTransmit(inChar);
    }

    if (serialInputComplete == false) {
      serialBuffer[serialInputSize] = inChar;
      serialInputSize++;
    } else {
      serialInputComplete = true;
    }
  }
}

ISR(USART_UDRE_vect) {
    unsigned char tmptail;
   
    // Cheqck if all data is transmitted
    if (USART_TxHead != USART_TxTail) {
      // Calculate buffer index
      tmptail = (USART_TxTail + 1) & USART_TX_BUFFER_MASK;
   
      // Store new index
      USART_TxTail = tmptail;
   
      // Start transmission
      UDR0 = USART_TxBuf[tmptail];
    } else {
      // Disable UDRE interrupt
      UCSR0B &= ~(1 << UDRIE0);
    }
}

void serialTransmit(char data) {
    unsigned char tmphead;
   
    // Calculate buffer index
    tmphead = (USART_TxHead + 1) & USART_TX_BUFFER_MASK;
   
    // Wait for free space in buffer
    while (tmphead == USART_TxTail)
      ;
   
    // Store data in buffer
    USART_TxBuf[tmphead] = data;
   
    // Store new index
    USART_TxHead = tmphead;
   
    // Enable UDRE interrupt
    UCSR0B |= (1 << UDRIE0);
}
 
void serialUpdate(){
  while (Serial.available()){
    if (serialInputSize < SERIAL_BUFFER_SIZE) {
      char inChar = Serial.read();

      if (inChar == '\r') {
        Serial.print("\r\n");
        serialInputComplete = true;
      } else {
        Serial.print(inChar);
      }

      if (serialInputComplete == false) {
        serialBuffer[serialInputSize] = inChar;
        serialInputSize++;
      } else {
        serialInputComplete = true;
      }
    }
  }
}

void usart0_init(unsigned int ubrr) {
    //initialize variables
    USART_RxHead = 0;
    USART_RxTail = 0;
    USART_TxHead = 0;
    USART_TxTail = 0;

    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable transmitter and reciever
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}



#include "SerialDriver.h"

bool serialInputComplete = false;
uint8_t serialInputSize = 0;
char serialBuffer[SERIAL_BUFFER_SIZE] = {0};

//shouldnt this be atomic??
ISR(USART_RX_vect) {
  // Read the received data
  uint8_t size = serialInputSize;
  char c = UDR0;
  if (!serialInputComplete && serialInputSize !< SERIAL_BUFFER_SIZE) {
    serialBuffer[size] = c;
    serialInputSize = size + 1;
  }
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

void serialInit(){
  Serial.begin(9600);
}

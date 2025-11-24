#include "SerialDriver.h"

bool serialInputComplete = false;
int serialInputSize = 0;
char serialBuffer[SERIAL_BUFFER_SIZE] = {0};

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

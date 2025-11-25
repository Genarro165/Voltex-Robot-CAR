#include "PortExpander.h"

uint8_t portExpanderData;

void portExpanderWrite(uint8_t mode) {
  Wire.beginTransmission(PORT_EXPANDER_ADRES);
  Wire.write(mode);
  Wire.endTransmission();
}

void portExpanderRead() {
  Wire.requestFrom(PORT_EXPANDER_ADRES, 1);
}

void portExpanderInit() {
  Wire.begin();
  portExpanderData = 0;
}

void portExpanderUpdate() {
  while(Wire.available()) { //stores incomming 
    portExpanderData = Wire.read();
  }
}


#include "PortExpander.h"

uint8_t portExpanderData;

enum portEvent : uint8_t {
  NONE,
  NEW_VAL,
  READ
} portExpanderEvent;

void portExpanderWrite(uint8_t mode) {
  Wire.beginTransmission(PORT_EXPANDER_ADRES);
  Wire.write(mode);
  Wire.endTransmission();
}

ISR(PCINT2_vect) {
  if (((PIND & (1 << 2)) == 0) && (portExpanderEvent == NONE)) {
    portExpanderEvent = NEW_VAL;
  }
}

void portExpanderInit() {
  Wire.begin();
  
  //set int pin to input pullup
  DDRD &= ~PORT_EXPANDER_INT;
  PORTD |= PORT_EXPANDER_INT;

  //enable the pin change interupt for pin the int pin
  PCMSK2 |= (1 << PCINT18);
  PCICR |= (1 << PCIE2); //enable the pin change group 2 wich contains the int pin
  
  //initialize state
  portExpanderData = 0;
  portExpanderEvent = NONE;
}

void portExpanderUpdate() {
  
  //request updated data from the pcf
  if (portExpanderEvent == NEW_VAL) {
    Wire.requestFrom(PORT_EXPANDER_ADRES, 1);
    portExpanderEvent = READ;
  }
  //store incoming data
  if (Wire.available() && (portExpanderEvent == READ)) {
    portExpanderData = Wire.read();
    portExpanderEvent = NONE;
  }
}


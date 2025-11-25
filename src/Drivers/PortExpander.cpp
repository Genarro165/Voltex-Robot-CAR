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
  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2); //set pin 2 to input pull up
  //enable the pin change interupt for pin 2
  PCMSK2 |= (1 << PCINT18);
  PCICR |= (1 << PCIE2); //enable the pin change group 2 wich contains pin 2
  portExpanderData = 0;
  portExpanderEvent = NONE;
}

void portExpanderUpdate() {
  if (portExpanderEvent == NEW_VAL) {
    Wire.requestFrom(PORT_EXPANDER_ADRES, 1);
    portExpanderEvent = READ;
  }
  if (Wire.available() && (portExpanderEvent == READ)) { //stores incomming 
    portExpanderData = Wire.read();
    portExpanderEvent = NONE;
  }
}


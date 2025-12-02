#include "PortExpander.h"

uint8_t portExpanderData;

enum portEvent : uint8_t {
  NONE,
  NEW_VAL,
  READ
} portExpanderEvent;

void portExpanderWrite(uint8_t mode) {
  i2c_start();
  i2c_addr(PORT_EXPANDER_ADRES);
  i2c_tx_byte(mode);
  i2c_stop();
}

ISR(PCINT2_vect) {
  if (((PIND & (1 << 2)) == 0) && (portExpanderEvent == NONE)) {
    portExpanderEvent = NEW_VAL;
  }
}

void portExpanderInit() {
  i2c_init();
  
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
    i2c_addr(PORT_EXPANDER_ADRES);
    portExpanderEvent = READ;
  }
  //store incoming data
  if (portExpanderEvent == READ) {
    i2c_rx_byte(&portExpanderData);
    portExpanderEvent = NONE;
  }
}




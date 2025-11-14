#include "BluetoothDriver.h"
#include "../InputManager.h"

char bluetoothInputString[BLUETOOTH_BUFFER_SIZE] = {0};
bool bluetoothStringComplete = false;
int bluetoothInputSize = 0;
SoftwareSerial bluetooth(BRX, BTX);
void bluetoothInit() {
  pinMode(BRX, INPUT);
  pinMode(BTX, OUTPUT);
   // Set the baud rate for the SoftwareSerial object
    bluetooth.begin(9600);
}

void bluetoothUpdate() {
  while (bluetooth.available()) {
    // Get the new byte
    char inChar = (char)bluetooth.read();

  if (inChar == '\r') {
      // Set the flag
      bluetoothStringComplete = true;
    }
    if (bluetoothStringComplete == false){// Add it to the inputString
      if (bluetoothInputSize < BLUETOOTH_BUFFER_SIZE){
    bluetoothInputString[bluetoothInputSize++] = inChar;
        } else {
          bluetoothStringComplete = true;
        }
    }

    
    if (bluetoothInputSize == 7) {
      if (strncmp(bluetoothInputString, "OK+CONN", 7) == 0) {
          Serial.print("Bleutooth connected!\r\n");
          bluetoothInputSize = 0;
      } else if (strncmp(bluetoothInputString, "OK+LOST", 7) == 0) {
          Serial.print("Bleutooth disconnected\r\n");
          bluetoothInputSize = 0;
        }
    }
  }
  


}

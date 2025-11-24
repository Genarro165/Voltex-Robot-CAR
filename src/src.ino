#include "MainStateMachine.h"
#include "MainStateMachine.h"
#include "InputManager.h"
#include "Drivers/LineSensor.h"
#include "Drivers/DistanceSensor.h"
#include "Drivers/MotorDriver.h"
#include "Drivers/SerialDriver.h"
#include "Drivers/BluetoothDriver.h"
#include "States/Autonomous.h"
#include "States/Idle.h"
#include "States/RemoteControl.h"
#include "States/Slave.h"

void setup() {
    //lineSensorInit();
    //distanceSensorInit();
    //motorDriverInit();
    serialInit(CALC_BAUD(9600));
    //bluetoothInit();
    
    registerNewState(Idle, &idleState);
    //registerNewState(Slave, &slaveState);
    //registerNewState(RemoteControl, &remoteControlState);
    //registerNewState(Autonomous, &autonomousState);
    
    prints("yeet\r\n");

}

void loop() {
    //run all of the update functions
    //bluetoothUpdate();
    //distanceSensorUpdate();
    //lineSensorUpdate();
    inputManagerUpdate();

    //execute the current state
    runCurrentState();
}

int main(void) {
    setup();

    while(1) { loop(); }
}

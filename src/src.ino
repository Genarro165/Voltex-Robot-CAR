#include "MainStateMachine.h"
#include "MainStateMachine.h"
#include "InputManager.h"
#include "Drivers/LineSensor.h"
#include "Drivers/DistanceSensor.h"
#include "Drivers/MotorDriver.h"
#include "Drivers/SerialDriver.h"
#include "Drivers/BluetoothDriver.h"
#include "Drivers/PortExpander.h"
#include "States/Autonomous.h"
#include "States/Idle.h"
#include "States/RemoteControl.h"
#include "States/Slave.h"

void setup() {
    //lineSensorInit();
    //distanceSensorInit();
    //motorDriverInit();
    serialInit();
    bluetoothInit();
    portExpanderInit();
    portExpanderWrite(0b11111111);
    registerNewState(Idle, &idleState);
    //registerNewState(Slave, &slaveState);
    //registerNewState(RemoteControl, &remoteControlState);
    //registerNewState(Autonomous, &autonomousState);
    
}

void loop() {
    //run all of the update functions
    serialUpdate();
    bluetoothUpdate();
    portExpanderUpdate();
    //distanceSensorUpdate();
    //lineSensorUpdate();
    inputManagerUpdate();

    //execute the current state
    runCurrentState();
}


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
    serialInit();
    bluetoothInit();
    
    registerNewState(Idle, &idleState);
    //registerNewState(Slave, &slaveState);
    //registerNewState(RemoteControl, &remoteControlState);
    //registerNewState(Autonomous, &autonomousState);
    
}

void loop() {
    //run all of the update functions
    serialUpdate();
    bluetoothUpdate();
    //distanceSensorUpdate();
    //lineSensorUpdate();
    inputManagerUpdate();

    //execute the current state
    runCurrentState();
}


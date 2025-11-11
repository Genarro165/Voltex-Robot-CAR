#pragma once
#include <stddef.h>
#include <stdint.h>
/*
 * so all you need to do to add a new state is to first:
 * Add a new state to the StateID enum.
 * Then create a new state function:
 `
    void idleState(struct State* currState) {
        //if we recieve the startcar event we switch to slave mode
        if (currState->currentEvent == StartCar) {
            currentState->id = Slave;
        }
    }
 `
 * Finally we need to register the new state which we can do like this:
 `
    registerNewState(Idle, &idleState);
 `
 * this registerNewState function has to be called in the setup function
*/

//these are the names of the different states
enum StateID : char {
    Idle,
    Slave,
    RemoteControl,
    Autonomous
};

//these are generated when some piece of information is recieved
enum Event : char {
    None,
    InputComplete
};

//holds the type of state and the event currently being handeled
struct State {
    enum StateID id;
    enum Event currentEvent;
};

//this holds the functions of each of the possible states
extern void (*stateFunctions[6])(struct State*);

//the current state of the state machine
extern struct State currentState;

//register a new state function with its id
void registerNewState(enum StateID funcID, void (*newFunc)(struct State*));

//execute the function of the current state
void runCurrentState();



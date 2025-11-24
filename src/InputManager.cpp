#include "InputManager.h"


void prints(const char* str) {
    for (;*str != '0'; str++) {
        serialTransmit(*str);
    }
}

int strncmp( const char * s1, const char * s2, unsigned int n )
{
    while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}


char inputBuffer[INPUT_MAX_ARGS][INPUT_WORD_SIZE] = {0};
unsigned char argumentCount = 0;


void parseArguments(char* data, int size) {
    unsigned char argumentBase = 0;

    for (int i = 0; i < size; i++) {
        if (data[i] == ' ') {
            if (argumentCount++ > INPUT_MAX_ARGS) {
                break;
            }
            i++;//skip space
            argumentBase = 0;
        }
        inputBuffer[argumentCount][argumentBase] = data[i];
        if (argumentBase++ > INPUT_WORD_SIZE) {
            if (argumentCount++ > INPUT_MAX_ARGS) {
                break;
            }
            argumentBase = 0;
        }
    }
}

void flushArguments() {
    for (uint8_t i = 0; i < sizeof(inputBuffer); i++) {
        ((char*) inputBuffer)[i] = 0;
    }
    argumentCount = 0;
    currentState.currentEvent = None;
}

const char StringStates[][16] = {"Idle", "Slave", "RemoteControl", "Autonomous"};

void inputManagerUpdate() {
    //make sure that the input is handeled
    if (currentState.currentEvent == InputComplete) {
        return;
    }

    if (serialInputComplete) {
        parseArguments(serialInputBuffer, serialInputSize);
        serialInputSize = 0;
        serialInputComplete = false;
        currentState.currentEvent = InputComplete;
    } else if (bluetoothStringComplete) {
        parseArguments(bluetoothInputString, bluetoothInputSize);
        bluetoothStringComplete = false;
        bluetoothInputSize = 0;
        prints("bluetooth command: ");
        prints(inputBuffer[0]);
        prints("\r\n");
    }

    if (strncmp(inputBuffer[0], "setS", INPUT_WORD_SIZE) == 0) {
        prints(inputBuffer[1]);
        prints("\r\n");
        for (uint8_t i = 0; i < 4; i++) {
            if (strncmp(inputBuffer[1], StringStates[i], INPUT_WORD_SIZE) == 0) {
                currentState.id = (enum StateID) i;
            }
        }
        flushArguments();
    } else if (strncmp(inputBuffer[0], "getS", INPUT_WORD_SIZE) == 0) {
        prints(StringStates[currentState.id]);
        prints("\r\n");
        flushArguments();
    } else {
        flushArguments();
    }
}


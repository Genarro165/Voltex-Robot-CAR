#include "InputManager.h"
#include "Drivers/PortExpander.h"

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

//turn string into number
int to_int(const char* str) {
    
    int num = 0;
    char c;
    while (*str != '\0') {
        c = *(str++);
        if (c > 64) {
            c -= 55;
        } else if (c > 47) {
            c -= 48;
        } else {
            
            break;
        }
        num = (num << 4) | c;
    }
    return num;
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
        parseArguments(serialBuffer, serialInputSize);
        serialInputSize = 0;
        serialInputComplete = false;
        currentState.currentEvent = InputComplete;
    } else if (bluetoothStringComplete) {
        parseArguments(bluetoothInputString, bluetoothInputSize);
        bluetoothStringComplete = false;
        bluetoothInputSize = 0;
        currentState.currentEvent = InputComplete;
    }
    if (currentState.currentEvent == InputComplete) {
        Serial.print("recieved: \"");
        Serial.print(inputBuffer[0]);
        Serial.print("\" : \"");
        Serial.print(inputBuffer[1]);
        Serial.print("\"\r\n");

        if (strncmp(inputBuffer[0], "setS", INPUT_WORD_SIZE) == 0) {
            Serial.println(inputBuffer[1]);
            for (uint8_t i = 0; i < 4; i++) {
                if (strncmp(inputBuffer[1], StringStates[i], INPUT_WORD_SIZE) == 0) {
                    currentState.id = (enum StateID) i;
                }
            }
            flushArguments();
        } else if (strncmp(inputBuffer[0], "getS", INPUT_WORD_SIZE) == 0) {
            Serial.println(StringStates[currentState.id]);
            flushArguments();
        } else if (strncmp(inputBuffer[0], "setSpeed", INPUT_WORD_SIZE) == 0) {
            Serial.print(inputBuffer[1]);
            flushArguments();
        } else if (strncmp(inputBuffer[0], "getP", INPUT_WORD_SIZE) == 0) {
            Serial.print(portExpanderData);
            Serial.print("\r\n");
            flushArguments();
        } else if (strncmp(inputBuffer[0], "setP", INPUT_WORD_SIZE) == 0) {
            uint8_t val = to_int(inputBuffer[1]);
            Serial.print(val);
            Serial.print("\r\n");
            portExpanderWrite(val);
            flushArguments();
        } else {
            flushArguments();
        }
    }
}


#include "Microstarter.h"
#include <Arduino.h>

Microstarter::Microstarter(int uPin) {
    this->uPin = uPin;                          // atributes parameter value to uPin
    this->uState = Start_state::STOP;           // defines microstarter state as STOP so the robot will only move if it receives signal from IR module
};

void Microstarter::uUpdate() {
    bool readPin = digitalRead(this->uPin);      // reads signal received from uPin

    if (readPin == true) {
        this->uState = Start_state::START;      // if uPin receives signal, changes uState to START, causing the robot to move
    } else {
        this->uState = Start_state::STOP;       // if uPin doesn't receive signal, keeps uState as STOP
    } 
};
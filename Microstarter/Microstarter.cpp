#include "Microstarter.h"
#include <Arduino.h>

Microstarter::Microstarter(int uPin) {
    this->uPin = uPin;
    this->uState = Start_state::STOP;
}

void Microstarter::uUpdate() {
    bool readPin = digitalRead(this->uPin);
    if (readPin == true) {
        this->uState = Start_state::START;
    } else {
        this->uState = Start_state::STOP;
    } 
}
#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int pin) {
    this->pin = pin;            // atributes constructor's parameter value to pin
}

void DigitalSensor::updateSensor() {
    this->rawRead = digitalRead(this->pin);                // reads pin and atributes it to rawRead
    this->close = this->rawRead == 1 ? true : false;       // if sensor is "seeing something", defines variable close as true.

    return this->rawRead;                                  // returns rawRead updated value
}
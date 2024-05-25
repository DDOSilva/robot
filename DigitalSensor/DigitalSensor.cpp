#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int pin) {
    this->pin = pin;
}

void DigitalSensor::updateSensor() {
    this->rawRead = digitalSensor(this-> pin);
    this->close = this->rawRead == 1 ? true : false;
    return this->rawRead;
}
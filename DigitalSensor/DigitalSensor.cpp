#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int pin) {
    this->pin = pin;
}

void DigitalSensor::updateSensor() {
    this->state = digitalRead(this->pin);
}
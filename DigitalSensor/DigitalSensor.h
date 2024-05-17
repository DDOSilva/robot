#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

class DigitalSensor {
    public:
        DigitalSensor(int pin);

        int pin;
        bool state;

        void updateSensor();
}

#endif
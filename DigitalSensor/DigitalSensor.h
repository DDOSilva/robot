#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

class DigitalSensor {
    public:
        DigitalSensor(int pin);

        int rawRead;
        int pin;
        bool close;

        void updateSensor();
}

#endif

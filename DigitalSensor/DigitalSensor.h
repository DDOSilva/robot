#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

class DigitalSensor {
    public:
        DigitalSensor(int pin);

        int rawRead;            // receives pin value 
        int pin;                // receives value in constructor
        bool close;             // rawRead value converted to binary, checks if the sensor is "seeing" something. 

        void updateSensor();    // reads pin and update rawRead and close values
};

#endif

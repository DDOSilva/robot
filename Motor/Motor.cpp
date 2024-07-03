#include "Motor.h"

MotorConfig::MotorConfig (int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin) {
    this->inPin1 = inPin1;              // atributes parameter value to inPin1 
    this->inPin2 = inPin2;              // atributes parameter value to inPin2
    this->pwmPin = pwmPin;              // atributes parameter value to pwmPin
    this->cSpeed = cSpeed;              // atributes parameter value to cSpeed
    this->channelPin = channelPin;      // atributes parameter value to channelPin
}

Motor::Motor (int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin) {}

    // defines motor's power (speed) and rotation's direction (clockwiser/counterclockwise)
    // speed value needs to be in a -100 to 100 range
    void Motor::setSpeed(int speed) {
        this->speed = speed;                        // atributes parameter value to speed
        float fixSpeed = this->config.cSpeed;       // creates fixSpeed with cSpeed value (defined as 1.0 in robot.cpp). will be used in convertion to [-255,255]

        // converts pwm value from a -100 to 100 range to a -255 to 255 range.
        int pwm = (int)(this->maxSpeed / (100.0) * 255.0 *((float)abs(fixSpeed) / 100);

        // conditions that will check rotation's direction 
        if (fixSpeed < 0 && fixSpeed >= -100) {             // if value is negative, rotation will be counterclockwise
            digitalWrite(this->config.inPin1, 1);
            digitalWrite(this->config.inPin2, 0);           // this pin configuration will define the direction
        } else if (fixSpeed >= 0 && fixSpeed <= 100) {      // if value is positive, rotation will be clockwise
            digitalWrite(this->config.inPin1, 0);
            digitalWrite(this->config.inPin2, 1);           // this pin configuration will define the direction
        } else {
            Serial.println("INVALID SPEED VALUE");      // error
            return;
        }
        ledcWrite(this->config.channelPin, pwm);        // writes pwm value on channelPin
}
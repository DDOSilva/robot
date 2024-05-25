#include "Motor.h"

MotorConfig::MotorConfig (int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin) {
    this->inPin1 = inPin1;
    this->inPin2 = inPin2;
    this->pwmPin = pwmPin;
    this->cSpeed = cSpeed;
    this->channelPin = channelPin;
}

Motor::Motor (int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin) {}

//should be between -100 and 100
void Motor::setSpeed(int speed) {
    this->speed = speed;
    float fixSpeed = this->config.cSpeed;

    //convertion to [-255, 255] range
    int pwm = (int)(this->maxSpeed / (100.0) * 255.0 *((float)abs(fixSpeed) / 100);

    //conditions
    if (fixSpeed < 0 && fixSpeed >= -100) {
        digitalWrite(this->config.inPin1, 1);
        digitalWrite(this->config.inPin2, 0);
    } else if (fixSpeed >= 0 && fixSpeed <= 100) {
        digitalWrite(this->config.inPin1, 0);
        digitalWrite(this->config.inPin2, 1);
    } else {
        Serial.println("INVALID SPEED VALUE");
        return;
    }
    ledcWrite(this->config.channelPin, pwm);
}
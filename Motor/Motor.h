#ifndef MOTOR_H
#define MOTOR_H

// struct that will store important info like pins and so on
struct MotorConfig {
    MotorConfig(int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin);
    int inPin1;             // used to determine if motor's rotation will be clockwise or counterclockwise
    int inPin2;             // used to determine if motor's rotation will be clockwise or counterclockwise
    int pwmPin;             // controls motor's power (speed)
    float cSpeed;           // used to control motor's power (speed)
    int channelPin;         // sends signal to esp
}

class Motor {
    public:
        Motor(int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin);
        float maxSpeed = 100;           // max power that the motor can reach (100%)
        int speed;                      // receives power (speed) from pwm
        MotorConfig config;             // accesses info from struct
        void setSpeed(int speed);       // set motor's desired power (speed), using a -100 to 100 range
};
#endif
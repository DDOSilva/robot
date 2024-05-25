#ifndef MOTOR_H
#define MOTOR_h

struct MotorConfig {
    MotorConfig(int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin);
    int inPin1;
    int inPin2;
    int pwmPin;
    float cSpeed;
    int channelPin;
}

class Motor {
    public:
        Motor(int pwmPin, int inPin1, int inPin2, int cSpeed, int channelPin);
        float maxSpeed = 100;
        int speed;
        MotorConfig config;
        void setSpeed(int speed);
}
#endif
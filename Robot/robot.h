#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>

#include "Microstarter.h"
#include "vision.h"
#include "DigitalSensor.h"
#include "Motor.h"
#include "Strategy.h"

using namespace std;

// defining every pin 
#define FRONT_SENSOR_PIN 35
#define FULL_RIGHT_SENSOR_PIN 25
#define FULL_LEFT_SENSOR_PIN 13
#define LEFT_SENSOR_PIN 26
#define RIGHT_SENSOR_PIN 34

#define RIGHT_MOTOR_PWM_PIN 21
#define RIGHT_MOTOR_IN1_PIN 19
#define RIGHT_MOTOR_IN2_PIN 18
#define RIGHT_MOTOR_SPEED_CONST 1.0
#define RIGHT_MOTOR_CHANNEL 0

#define LEFT_MOTOR_PWM_PIN 4
#define LEFT_MOTOR_IN1_PIN 17
#define LEFT_MOTOR_IN2_PIN 16
#define LEFT_MOTOR_SPEED_CONST 1.0
#define LEFT_MOTOR_CHANNEL 1

#define MICRO_START_SIGNAL_PIN 2

#define STRATEGY_PIN_A 22
#define STRATEGY_PIN_B 23
#define STRATEGY_PIN_C 14

#define STDBY 5

// creates integer constants
namespace robotState {
    enum states {
        AWAITING_START,     // 0
        INIT_STRAT,         // 1
        AUTO_STRAT,         // 2
        STOPPED             // 3
    };
};

class Robot {
    public:
        string name = "robot";
        int ledPin = 13;                        
        robotState::states robot_state;

        // creates all objects needed
        Microstarter uStart;
        DigitalSensor frontSensor;
        DigitalSensor leftSensor;
        DigitalSensor rightSensor;
        DigitalSensor fullRightSensor;
        DigitalSensor fullLeftSensor;
        Vision vision;

        Motor rightMotor;
        Motor leftMotor;
        InitialStrat* initStrategy;
        AutoStrat autoStrategy;

        void readSensors();         // read every robot's sensor
        void update();              // general update
        void print();               // will print the information needed 
        void fight();               // controls every robot's state

        Robot();

};

#endif
#ifndef STRATEGY_H
#define STRATEGY_H

#include "Vision.h"
#include "Motor.h"

#include <Arduino.h>
#include <list>

class Moveset {
    public:
        int motorPowerL;        // defines left motor power
        int motorPowerR;        // defines right motor power
        int msTime;             // duration of motors operation in ms
        int msStartTime;        // starts with 0. it's used to monitorate program's execution time
        bool started;           // used to set program's start
        bool finished;          // used to set program's end

        // utilizes 2 Motor objects
        bool update(Motor &leftMotor, Motor &rightMotor);

        // recieves power and time (in ms) that motor's will operate, defining a movement and its duration
        Moveset(int motorPowerL, motorPowerR, msTime);      
};

class InitialStrat {
    public:
        std::list<Moveset> moves;
        Moveset &currentMove;
        bool stratFinished;
        bool update(Motor &leftMotor, Motor &rightMotor);

        // recieves a list that will define the robot's moves based on the selected strategy
        InitialStrat(std::list<Moveset> moves);             
};

class AutoStrat {
    public:
        int motorPowerL;
        int motorPowerR;

        // recognizes enemy's positions and determines "what the robot needs to do"
        void updateMotor(Vision &vision, Motor &leftMotor, Motor &rightMotor);
};

InitialStrat *get_selectedStrategy(int pinA, int pinB, int pinC);

#endif
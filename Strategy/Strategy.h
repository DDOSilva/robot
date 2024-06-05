#ifndef STRATEGY_H
#define STRATEGY_H

#include "Vision.h"
#include "Motor.h"

#include <Arduino.h>
#include <list>

class Moveset {
    public:
        int motorPowerL;
        int motorPowerR;
        int msTime;
        int msStartTime;
        bool started;
        bool finished;
        bool update(Motor &leftMotor, Motor &rightMotor);
        Moveset(int motorPowerL, motorPowerR, msTime);
}

class InitialStrat {
    public:
        std::list<Moveset> moves;
        Moveset &currentMove;
        bool stratFinished;
        bool update(Motor &leftMotor, Motor &rightMotor);
        InitialStrat(std::list<Moveset> moves);
}

class AutoStrat {
    public:
        int motorPowerL;
        int motorPowerR;
        void updateMotor(Vision &vision, Motor &leftMotor, Motor &rightMotor);
}

InitialStrat *get_selectedStrategy(int pinA, int pinB, int pinC);

#endif
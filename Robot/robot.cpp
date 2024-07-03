#include "robot.h"
#include <Arduino.h>



Robot::Robot() : frontSensor(FRONT_SENSOR_PIN),                 // initializes everything before entering the "body"
                    leftSensor(LEFT_SENSOR_PIN),
                    rightSensor(RIGHT_SENSOR_PIN),
                    fullLeftSensor(FULL_LEFT_SENSOR_PIN),
                    fullRightSensor(FULL_RIGHT_SENSOR_PIN),
                    rightMotor(RIGHT_MOTOR_CHANNEL, RIGHT_MOTOR_IN1_PIN, RIGHT_MOTOR_IN2_PIN, RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_SPEED_CONST),
                    leftMotor(LEFT_MOTOR_CHANNEL, LEFT_MOTOR_IN1_PIN, LEFT_MOTOR_IN2_PIN, LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_SPEED_CONST),
                    vision(),
                    autoStrategy(),
                    uStart(MICRO_START_SIGNAL_PIN)
{
    this->robot_state = robotState::AWAITING_START;
}


// updates every sensor
void Robot::readSensors() {
    this-> frontSensor.updateSensor();
    this-> leftSensor.updateSensor();
    this-> rightSensor.updateSensor();
    this-> fullLeftSensor.updateSensor();
    this-> fullRightSensor.updateSensor();
}


// general print. prints info about every component
void Robot::print() {
    //microstarter
    Serial.print(this->uStart.uUpdate);
    Serial.print("\t");

    //sensors
    Serial.print(this->fullLeftSensor.rawRead);
    Serial.print("\t");
    Serial.print(this->leftSensor.rawRead);
    Serial.print("\t");
    Serial.print(this->frontSensor.rawRead;
    Serial.print("\t");
    Serial.print(this->rightSensor.rawRead);
    Serial.print("\t");
    Serial.print(this->fullRightSensor.rawRead);
    Serial.print("\t");
}

// general updates. updates the robot and all the classes needed
void Robot::update() {

    this->uStart.uUpdate();
    this->readSensors();
    this->vision.updatePosition(this->frontSensor, this->rightSensor, this->leftSensor, this->fullRightSensor, this->fullLeftSensor);
    this->fight();
}


void Robot::fight () {
    bool initStratFinished = false;     // atributes false to initStratFinished

    switch (this->robot_state) {
        case robotState::AWAITING_START:                        // robot is turned on and awaiting a signal to start moving 
            if (this->uStart.uState == Start_state::START) {
                this->robot_state = robotState::INIT_STRAT;
                this->initStrategy = get_SelectedStrategy(STRATEGY_PIN_A, STRATEGY_PIN_B, STRATEGY_PIN_C);
            }
            break;
        
        case robotState::INIT_STRAT:                            // robot is executing initial strategy
            initStratFinished = this->initStrategy->update(this->leftMotor, this->rightMotor);
            if (initStratFinished)
                this->robot_state = robotState::AUTO_STRAT;
            if (this->uStart.uState == Start_state::STOP)
                this->robot_state = robotState::STOPPED;
            break;

        case robotState::AUTO_STRAT:                            // initial strategy ended, robot must execute auto strategy
            this->autoStrategy.updateMotor(this->vision, this->leftMotor, this->rightMotor);
            
            if(this->uStart.uState == Start_state::STOP)
                this->robot_state = robotState::STOPPED;
            break;
        
        case robotState::STOPPED:                               // robot receives signal to stop by the microstarter
            leftMotor.setSpeed(0);                              // set left motor power as 0%
            rightMotor.setSpeed(0);                             // set right motor power as 0%
            break;

        default:
            Serial.println("UNKNOWN BEHAVIOR");                 // error
    }
}




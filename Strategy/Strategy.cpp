#include <Strategy.h>

Moveset::Moveset(int motorPowerL, int motorPowerR, int msTime) {
    this->motorPowerL = motorPowerL;        // atributes parameter value to motorPowerL
    this->motorPowerR = motorPowerR;        // atributes parameter value to motorPowerR
    this->msTime = msTime;                  // atributes parameter value to msTime
    this->msStartTime = 0;                  // atributes 0 to msStartTime
    this->started = false;                  // atributes false to started state
    this->finished = false;                 // atributes false to finished state
}

//if the move is finished, method will return true
bool Move::update(Motor &leftMotor, &rightMotor) {
    int msDeltaTime = 0;                            // time variation. start with 0.
    int msNow = millis();                           // millis() returns the time passed (in ms) since arduino's initialization. this value is atributed to msNow.

    if (!this->started) {                           
        this->started = true;                       // if started is false, changes it to true
            Serial.println(started);                // used to check if it started
        this->msStartTime = msNow;                  // atributes msStarTime to msNow to monitorate the time passed
        leftMotor.setSpeed(this->motorPowerL);      // sets motorPowerL value as left motor speed (power)
        rightMotor.setSpeed(this->motorPowerR);     // sets motorPowerR value as right motor speed (power)

        return false;
    } else {
        msDeltaTime = msNow - this->msStartTime;    // atributes time variation value (ms) to msDeltaTime 
        if (msDeltaTime >= this->msTime) {          // condition to check if it's finished
            this->finished = true;                  // changes finished to true
                Serial.println(finished)            // used to check if it ended

            return true;                            
        } else {
            return false;
        }
    }
    
    char msg[] = "WRONG MOVE LOGIC";                // used to print if there's an error
        Serial.println(msg);

    return true;
}

// recieves every movement that will be done by the robot by a list named moves
// movement that will be realized is updated after every complete movement
InitialStrat::InitialStrat(std::list<Moveset> moves) : moves(moves), currentMove(moves.front()) {
    this->moves.popFront();                   
    this->stratFinished = false;        // atributes false to stratFinished. used to check if it the strategy ended
}

bool InitialStrat::update(Motor &leftMotor, Motor &rightMotor) {
    if(this->stratFinished) {
        return true;                    // returns true if initial strategy is finished
    }
    
    bool currentMoveFinished;                                                   // will check if the movement is finished or not
    currentMoveFinished = this->currentMove.update(leftMotor, rightMotor);      // updates currentMoveFinished state 

    if(currentMoveFinished) {
                Serial.println("CURRENT MOVE FINISHED: ");                      
            Serial.println(this->moves.empty());
        if(this->moves.empty()) {
            this->stratFinished = true;                                         // atributes true to stratFinished
                Serial.println(stratFinished);                                  // prints stratFinished state
            
            return true;
        }
        this->currentMove = this->moves.front();
        this->moves.popFront();                                                 // checks if the movement is done and removes it from the list  

        this->currentMove.update(leftMotor, rightMotor);                        // updates currentMove to next one to be executed
        return false;
    }
    else {
        return false;
    }

    char msg[] = "WRONG INITIAL STRATEGY LOGIC";            // used to print if there's an error
    Serial.println(msg);

    return true;
}

void AutoStrat::updateMotor(Vision &vision, Motor &leftMotor, Motor &rightMotor) {
        Serial.println("ENEMY POSITION: ");
    
    if(vision.enemy_position == EnemyPosition::FRONT) {                    // robot will move forward
            Serial.println("FRONT");                                       // prints enemy position
        leftMotor.setSpeed(100);                                           // sets left motor power as 100%
        rightMotor.setSpeed(100);                                          // sets right motor power as 100%
        return;
    } else if(vision.enemy_position == EnemyPosition::LEFT) {              // robot will move to his left
            Serial.println("LEFT");                                        // prints enemy position
        leftMotor.setSpeed(30);                                            // set left motor power as 30&
        rightMotor.setSpeed(100);                                          // sets right motor power as 100%
        return;
    } else if(vision.enemy_position == EnemyPosition::RIGHT) {             // robot will move to his right
            Serial.println("RIGHT");                                       // prints enemy position
        leftMotor.setSpeed(100);                                           // sets left motor power as 100%
        rightMotor.setSpeed(30);                                           // sets right motor power as 30%
        return;
    } else if(vision.enemy_position == EnemyPosition::FULL_LEFT) {         // robot will turn to his left
            Serial.println("FULL_LEFT");                                   // prints enemy position
        leftMotor.setSpeed(-100);                                          // sets left motor power as -100% 
        rightMotor.setSpeed(100);                                          // sets right motor power as 100%
        return;
    } else if(vision.enemyPosition == EnemyPosition::FULL_RIGHT) {         // robot will turn to his right
            Serial.println("FULL_RIGHT");                                  // prints enemy position
        leftMotor.setSpeed(100);                                           // sets left motor power as 100%
        rightMotor.setSpeed(-100);                                         // sets right motor power as -100%
        return;
    } else if(vision.enemyPosition == EnemyPosition::SEARCH_LEFT) {        // robot will search for the enemy (left)
            Serial.println("SEARCH_LEFT");                                 // prints enemy position
        leftMotor.setSpeed(10);                                            // sets left motor power as 10%
        rightMotor.setSpeed(100);                                          // sets right motor power as 100%
        return;
    } else if(vision.enemyPosition == EnemyPosition::SEARCH_RIGHT) {       // robot will search for the enemy (right)
            Serial.println("SEARCH_RIGHT");                                // prints enemy position
        leftMotor.setSpeed(100);                                           // sets left motor power as 100%
        rightMotor.setSpeed(10);                                           // sets right motor power as 10%
        return;
    }
}

InitialStrat *get_SelectedStrategy(int pinA, int pinB, int pinC) {
    bool selectA = digitalRead(pinA);           // read dipswitch pin and stores it
    bool selectB = digitalRead(pinB);           // read dipswitch pin and stores it
    bool selectC = digitalRead(pinC);           // read dipswitch pin and stores it

    int selectedNumber = ((int(selectB)) + (int(selectC)) << 1);        // selects strategy
    InitialStrat *initialStrategy;

    std::list<Move> moves = {};
    switch(selectedNumber) {
        // desempate (00)
        case 0:
                Serial.println("AUTOSTRAT: DESEMPATE");
            moves.pushBack(Moveset(100, -100, 300));
            break;
        // direita - frente - esquerda (01)
        case 1:
                Serial.println("AUTOSTRAT: DIREITA - FRENTE - ESQUERDA");
            moves.pushBack(Moveset(100, 30, 100));
            moves.pushBack(Moveset(100, 100, 80));
            moves.pushBack(Moveset(30, 100, 120));
            break;
        // frente - esquerda - direita (10)
        case 2:
                Serial.println("AUTOSTRAT: FRENTE - ESQUERDA - DIREITA");
            moves.pushBack(Moveset(100, 100, 400));
            break;
        default:
            break;
    }

    // prints chosen strategy
    Serial.prinln("CHOSEN STRAT: ");
    Serial.println(selectA);
    Serial.println(selectB);
    Serial.println(selectC);

    initialStrategy = new InitialStrat(moves);

    return initialStrategy;

}

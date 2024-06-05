#include <Strategy.h>

Moveset::Moveset(int motorPowerL, int motorPowerR, int msTime) {
    this->motorPowerL = motorPowerL;
    this->motorPowerR = motorPowerR;
    this->msTime = msTime;
    this->msStartTime = 0;
    this->started = false;
    this->finished = false;
}

//if the move finishes, return true
bool Move::update(Motor &leftMotor, &rightMotor) {
    int msDeltaTime = 0;
    int msNow = millis();
    if (!this->started) {
        this->started = true;
            Serial.println(started);
        this->msStartTime = msNow;
        leftMotor.setSpeed(this->motorPowerL);
        rightMotor.setSpeed(this->motorPowerR);

        return false;
    } else {
        msDeltaTime = msNow - this->msStartTime;
        if (msDeltaTime >= this->msTime) {
            this->finished = true;
                Serial.println(finished)

            return true;
        } else {
            return false;
        }
    }
    
    char msg[] = "WRONG MOVE LOGIC";
        Serial.println(msg);

    return true;
}

InitialStrat::InitialStrat(std::list<Moveset> moves) : moves(moves), currentMove(moves.front()) {
    this->moves.popFront();
    this->stratFinished = false;
}

bool InitialStrat::update(Motor &leftMotor, Motor &rightMotor) {
    if(this->stratFinished) {
        return true;
    }
    
    bool currentMoveFinished;
    currentMoveFinished = this->currentMove.update(leftMotor, rightMotor);

    if(currentMoveFinished) {
                Serial.println("CURRENT MOVE FINISHED: ");
            Serial.println(this->moves.empty());
        if(this->moves.empty()) {
            this->stratFinished = true;
                Serial.println(stratFinished);
            
            return true;
        }
        this->currentMove = this->moves.front();
        this->moves.popFront();

        this->currentMove.update(leftMotor, rightMotor);
        return false;
    }
    else {
        return false;
    }

    char msg[] = "WRONG INITIAL STRATEGY LOGIC";
    Serial.println(msg);

    return true;
}

void AutoStrat::updateMotor(Vision &vision, Motor &leftMotor, Motor &rightMotor) {
        Serial.println("ENEMY POSITION: ");
    
    if(vision.enemy_position == EnemyPosition::FRONT) {
            Serial.println("FRONT");
        leftMotor.setSpeed(100);
        rightMotor.setSpeed(100);
        return;
    } else if(vision.enemy_position == EnemyPosition::LEFT) {
            Serial.println("LEFT");
        leftMotor.setSpeed(30);
        rightMotor.setSpeed(100);
        return;
    } else if(vision.enemy_position == EnemyPosition::RIGHT) {
            Serial.println("RIGHT");
        leftMotor.setSpeed(100);
        rightMotor.setSpeed(30);
        return;
    } else if(vision.enemy_position == EnemyPosition::FULL_LEFT) {
            Serial.println("FULL_LEFT");
        leftMotor.setSpeed(-100);
        rightMotor.setSpeed(100);
        return;
    } else if(vision.enemyPosition == EnemyPosition::FULL_RIGHT) {
            Serial.println("FULL_RIGHT");
        leftMotor.setSpeed(100);
        rightMotor.setSpeed(-100);
        return;
    } else if(vision.enemyPosition == EnemyPosition::SEARCH_LEFT) {
            Serial.println("SEARCH_LEFT");
        leftMotor.setSpeed(10);
        rightMotor.setSpeed(100);
        return;
    } else if(vision.enemyPosition == EnemyPosition::SEARCH_RIGHT) {
            Serial.println("SEARCH_RIGHT");
        leftMotor.setSpeed(100);
        rightMotor.setSpeed(10);
        return;
    }
}

InitialStrat *get_SelectedStrategy(int pinA, int pinB, int pinC) {
    bool selectA = digitalRead(pinA);
    bool selectB = digitalRead(pinB);
    bool selectC = digitalRead(pinC);

    int selectedNumber = (int(selectB)) + (int(selectC)) << 1);
    InitialStrat *initialStrategy;
    std::list<Move> moves = {};
    switch(selectedNumber) {
        //desempate (00)
        case 0:
                Serial.println("AUTOSTRAT: DESEMPATE");
            moves.pushBack(Moveset(100, -100, 300));
            break;
        //direita - frente - esquerda (01)
        case 1:
                Serial.println("AUTOSTRAT: DIREITA - FRENTE - ESQUERDA");
            moves.pushBack(Moveset(100, 30, 100));
            moves.pushBack(Moveset(100, 100, 80));
            moves.pushBack(Moveset(30, 100, 120));
            break;
        //frente - esquerda - direita (10)
        case 2:
                Serial.println("AUTOSTRAT: FRENTE - ESQUERDA - DIREITA");
            moves.pushBack(Moveset(100, 100, 400));
            break;
        default:
            break;
    }

    Serial.prinln("CHOSEN STRAT: ");
    Serial.println(selectA);
    Serial.println(selectB);
    Serial.println(selectC);

    initialStrategy = new InitialStrat(moves);

    return initialStrategy;

}

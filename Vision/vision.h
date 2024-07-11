#ifndef VISION_H
#define VISION_H

#include "DigitalSensor.h"

#define D_LIMIT_CM 20               // sets a distance limit of 20cm for the sensors

/*
// creates integer constants
namespace EnemyPosition {
    enum position {         // makes the representation of enemy position easier
        LEFT,               // 0
        RIGHT,              // 1
        FRONT,              // 2
        FULL_LEFT,          // 3
        FULL_RIGHT,         // 4
        SEARCH_LEFT,        // 5
        SEARCH_RIGHT        // 6
    };
}

class Vision {
    public:
        Vision();
        EnemyPosition::Position enemy_position;                 // stores enemy position. 
        EnemyPosition::Position latest_enemy_position;          // stores enemy position. will be used to check latest one and search for the enemy if enemy_position is receiving no value

        // constant updates enemy position and sends it to enemy_position and latest_enemy_position according to sensors reading
        // uses 5 DigitalSensor objects, named after it's positions in the actual robot
        void updatePosition(DigitalSensor &front_sensor, DigitalSensor &right_sensor, DigitalSensor &left_sensor,
        DigitalSensor &full_right_sensor, DigitalSensor &full_left_sensor);
};

#endif

*/

namespace EnemyPosition {
    enum position {
        FRONT,
        LEFT,
        RIGHT,
        FULL_LEFT,
        FULL_RIGHT,
        SEARCH_LEFT,
        SEARCH_RIGHT
    };
}

class Vision {
    public:
        EnemyPosition::position enemy_position;
        EnemyPosition::position latest_enemy_position;

        void updatePosition(DigitalSensor &front_left_sensor, DigitalSensor &front_right_sensor, 
        DigitalSensor &left_sensor, DigitalSensor &right_sensor);

};

#endif
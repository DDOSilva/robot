#ifndef VISION_H
#define VISION_H

#include "DigitalSensor.h"

#define D_LIMIT_CM 20

namespace EnemyPosition {
    enum position {
        LEFT,
        RIGHT,
        FRONT,
        FULL_LEFT,
        FULL_RIGHT,
        SEARCH_LEFT,
        SEARCH_RIGHT
    };
}

class Vision {
    public:
        Vision();
        EnemyPosition::Position enemy_position;
        EnemyPosition::Position latest_enemy_position;
        void updatePosition(DigitalSensor &front_sensor, DigitalSensor &right_sensor, DigitalSensor &left_sensor,
        DigitalSensor &full_right_sensor, DigitalSensor &full_left_sensor);
}

#endif
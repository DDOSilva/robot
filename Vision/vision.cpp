#include "vision.h"

#include <iostream>
#include <Arduino.h>

Vision::Vision() {}

void Vision::updatePosition (DigitalSensor &front_sensor, DigitalSensor &right_sensor, DigitalSensor &left_sensor,
DigitalSensor &full_right_sensor, DigitalSensor &full_left_sensor) {
    
    if (this->front_sensor.close) {
        this->enemy_position = EnemyPosition::FRONT;
        return;
    } else if (this->full_right_sensor.close) {
        this->enemy_position = EnemyPosition::FULL_RIGHT;
        this->latest_enemy_position = EnemyPosition::RIGHT;
        return;
    } else if (this->full_left_sensor.close) {
        this->enemy_position = EnemyPosition::FULL_LEFT;
        this->latest_enemy_position = EnemyPosition::LEFT;
        return;
    } else if (this->right_sensor.close) {
        this->enemy_position = EnemyPosition::RIGHT;
        this->latest_enemy_position = EnemyPosition::RIGHT;
        return;
    } else if (this->left_sensor.close) {
        this->enemy_position = EnemyPosition::LEFT;
        this->latest_enemy_position = EnemyPosition::LEFT;
        return;
    } else if (this->latest_enemy_position = EnemyPosition::RIGHT) {
        this->enemy_position = EnemyPosition::SEARCH_RIGHT;
        return;
    } else if (this->latest_enemy_position = EnemyPosition::LEFT) {
        this->enemy_position = EnemyPosition::SEARCH_LEFT;
    }
}
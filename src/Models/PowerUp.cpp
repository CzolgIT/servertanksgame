//
// Created by inql on 21.01.19.
//

#include "Main.h"

int PowerUp::getId() const {
    return id;
}

void PowerUp::setId(int id) {
    PowerUp::id = id;
}

int PowerUp::getX() const {
    return x;
}

void PowerUp::setX(int x) {
    PowerUp::x = x;
}

int PowerUp::getY() const {
    return y;
}

void PowerUp::setY(int y) {
    PowerUp::y = y;
}

PowerUpType PowerUp::getPowerUpType() const {
    return powerUpType;
}

void PowerUp::setPowerUpType(PowerUpType powerUpType) {
    PowerUp::powerUpType = powerUpType;
}

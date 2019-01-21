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

PowerUpType PowerUp::getPowerUpType() const {
    return powerUpType;
}

void PowerUp::setPowerUpType(PowerUpType powerUpType) {
    PowerUp::powerUpType = powerUpType;
}

const SDL_Point &PowerUp::getPosition() const {
    return position;
}

void PowerUp::setPosition(const SDL_Point &position) {
    PowerUp::position = position;
}

int PowerUp::getWidth() const {
    return width;
}

int PowerUp::getHeight() const {
    return height;
}

Collider *PowerUp::getCollider() const {
    return collider;
}

PowerUp::PowerUp(const SDL_Point &position, int width, int height) : position(position), width(width), height(height) {
    collider = new Collider(position.x,position.y,width,height,0);
}

PowerUp::~PowerUp() = default;

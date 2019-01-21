#include "Main.h"

PowerUp::PowerUp( int id , SDL_Point position , Uint8 powerUpType)
{
    this->id = id;
    this->position = position;
    this->powerUpType = PowerUpType(powerUpType);
    this->todestroy = false;
    collider = new Collider(position.x,position.y,50,50,0);
    this->todestroy = false;
}

PowerUp::~PowerUp() = default;

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



//
// Created by inql on 21.01.19.
//

#ifndef SERVERTANKSGAME_POWERUP_H
#define SERVERTANKSGAME_POWERUP_H

#include "Main.h"

class PowerUp{
public:

    PowerUp(const SDL_Point &position, int width, int height);

    virtual ~PowerUp();

    int getId() const;

    void setId(int id);

    PowerUpType getPowerUpType() const;

    void setPowerUpType(PowerUpType powerUpType);

    const SDL_Point &getPosition() const;

    void setPosition(const SDL_Point &position);

    Collider *getCollider() const;

    int getWidth() const;

    int getHeight() const;

private:
    int id;
    SDL_Point position;
    PowerUpType powerUpType;
    int width = 50;
    int height = 50;
    Collider *collider;
};



#endif //SERVERTANKSGAME_POWERUP_H

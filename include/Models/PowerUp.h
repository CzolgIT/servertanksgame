//
// Created by inql on 21.01.19.
//

#ifndef SERVERTANKSGAME_POWERUP_H
#define SERVERTANKSGAME_POWERUP_H

#include "Main.h"

class PowerUp{
public:

    PowerUp( int id , SDL_Point position , Uint8 powerUpType );

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

    bool todestroy;

private:

    int id;
    SDL_Point position;
    PowerUpType powerUpType;
    int width;
    int height;
    Collider *collider;
};



#endif //SERVERTANKSGAME_POWERUP_H

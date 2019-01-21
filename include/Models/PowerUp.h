//
// Created by inql on 21.01.19.
//

#ifndef SERVERTANKSGAME_POWERUP_H
#define SERVERTANKSGAME_POWERUP_H

#include "Main.h"

class PowerUp{
public:

    int getId() const;

    void setId(int id);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    PowerUpType getPowerUpType() const;

    void setPowerUpType(PowerUpType powerUpType);

private:
    int id;
    int x;
    int y;
    PowerUpType powerUpType;
};



#endif //SERVERTANKSGAME_POWERUP_H

#ifndef SERVERTANKSGAME_BULLET_H
#define SERVERTANKSGAME_BULLET_H

#include "Main.h"

class Bullet
{
public:

    Bullet( SDL_Point position , int direction );
    void move( float timeStep );
    void print();

private:

    int direction;
    SDL_Point position;
    float x;
    float y;

};

#endif //SERVERTANKSGAME_BULLET_H

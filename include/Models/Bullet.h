#ifndef SERVERTANKSGAME_BULLET_H
#define SERVERTANKSGAME_BULLET_H

#include "Main.h"

class Bullet
{
public:

    Bullet( SDL_Point position , int direction , int id , int clientId );
    void move( float timeStep );
    void print();
    int getId();
    int getClientId();

private:

    int id;
    int clientId;
    int direction;
    SDL_Point position;
    float x;
    float y;

};

#endif //SERVERTANKSGAME_BULLET_H

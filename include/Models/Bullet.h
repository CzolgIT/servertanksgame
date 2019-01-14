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
    SDL_Point getPosition();
    int getDirection();

    bool todestroy;
    Collider* getCollider();

private:

    int id;
    int clientId;
    int direction;
    SDL_Point position;
    float x;
    float y;

    Collider *collider;


};

#endif //SERVERTANKSGAME_BULLET_H

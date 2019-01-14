//
// Created by mm on 1/14/19.
//

#ifndef SERVERTANKSGAME_WALL_H
#define SERVERTANKSGAME_WALL_H

#include "Main.h"

class Wall
{
public:

    Wall( SDL_Point position, int id);
    void print();
    int getId();
    SDL_Point getPosition();
    Collider* getCollider();

private:

    int id;
    SDL_Point position;
    float x;
    float y;

    Collider *collider;


};

#endif //SERVERTANKSGAME_WALL_H

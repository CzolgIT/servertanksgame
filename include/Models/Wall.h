//
// Created by mm on 1/14/19.
//

#ifndef SERVERTANKSGAME_WALL_H
#define SERVERTANKSGAME_WALL_H

#include "Main.h"

class Wall
{
public:

    Wall( SDL_Point position,int width, int height);
    void print();;
    SDL_Point getPosition();
    Collider* getCollider();

private:

    SDL_Point position;
    float x;
    float y;
    int width, height;
public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

private:

    Collider *collider;


};

#endif //SERVERTANKSGAME_WALL_H

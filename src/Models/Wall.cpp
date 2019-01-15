//
// Created by mm on 1/14/19.
//

#include "Main.h"

Wall::Wall(SDL_Point position, int width, int height) {

    this->position = position;
    collider = new Collider(position.x,position.y,width,height,0);
}


SDL_Point Wall::getPosition() {
    return position;
}


Collider* Wall::getCollider()
{
    return collider;
}


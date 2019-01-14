//
// Created by mm on 1/14/19.
//

#include "Main.h"

Wall::Wall(SDL_Point position, int id) {

    this->position = position;
    this->id = id;

}

int Wall::getId()
{
    return id;
}

SDL_Point Wall::getPosition() {
    return position;
}


Collider* Wall::getCollider()
{
    return collider;
}


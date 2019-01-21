//
// Created by mm on 1/14/19.
//

#include "Main.h"

Wall::Wall(SDL_Point position, int width, int height) {

    this->position = position;
    this->setWidth(width);
    this->setHeight(height);
    collider = new Collider(position.x,position.y,width,height,0);
}


SDL_Point Wall::getPosition() {
    return position;
}


Collider* Wall::getCollider()
{
    return collider;
}

int Wall::getWidth() const {
    return width;
}

void Wall::setWidth(int width) {
    Wall::width = width;
}

int Wall::getHeight() const {
    return height;
}

void Wall::setHeight(int height) {
    Wall::height = height;
}


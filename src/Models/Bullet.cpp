#include "Main.h"

Bullet::Bullet( SDL_Point position , int direction )
{
    this->position = position;
    this->direction = direction;
    this->x = position.x;
    this->y = position.y;
}

void Bullet::move( float timeStep )
{
    this->x += (cos(double(direction) *M_PI/180) * BULLETSPEED * timeStep );
    this->y += (sin(double(direction) *M_PI/180) * BULLETSPEED * timeStep );

    position.x = int(x);
    position.y = int(y);
}

void Bullet::print() {
    std::cout << "Bullet       position: [ " << position.x << " , " << position.y << " ]\n"
              << "-----------------------------------------------------------\n";
}
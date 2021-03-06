#include "Main.h"

Bullet::Bullet( SDL_Point position , int direction , int id , int clientId )
{
    this->id = id;
    this->clientId = clientId;
    this->position = position;
    this->direction = direction;
    this->x = position.x;
    this->y = position.y;
    this->todestroy = false;

    this->collider = new Collider( x , y , 36 , 12 , direction );
}

void Bullet::move( float timeStep )
{
    this->x += (cos(double(direction) *M_PI/180) * BULLETSPEED * timeStep );
    this->y += (sin(double(direction) *M_PI/180) * BULLETSPEED * timeStep );

    position.x = int(x);
    position.y = int(y);

    if ( x< 0 || x > 64*64 || y<0 || y> 64*64 )
        todestroy=true;

    collider->update( x , y , 36 , 12 , direction );
}

void Bullet::print()
{
    std::cout << "Bullet (" << id << ")   position: [ " << position.x << " , " << position.y << " ]\n";
}

int Bullet::getId()
{
    return id;
}

int Bullet::getClientId()
{
    return clientId;
}

SDL_Point Bullet::getPosition() {
    return position;
}

int Bullet::getDirection() {
    return direction;
}

Collider* Bullet::getCollider()
{
    return collider;
}

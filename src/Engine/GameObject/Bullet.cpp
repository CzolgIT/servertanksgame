#include "Main.h"

Bullet::Bullet( int x, int y, int dir) : _GameObject( x , y , 12 , 36 , DYNAMIC )
{
    direction = dir-90;
}

void Bullet::move( float timeStep )
{
    x -= (cos((direction+90) *M_PI/180) * BULLETSPEED * timeStep);
    y -= (sin((direction+90) *M_PI/180) * BULLETSPEED * timeStep);

    if( x < (int)((double)width/2) ||
        x > 2048 - (int)((double)width/2) ||
        y < (int)((double)height/2) ||
        y > 2048 - (int)((double)height/2)
        )
    {
        this->setToBeDestroyed();
    }

    collider->update(x,y,width,height, direction);

}

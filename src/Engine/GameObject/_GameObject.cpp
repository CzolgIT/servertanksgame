#include "Main.h"

_GameObject::_GameObject( float x , float y , int width , int height , ObjectType type )
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->collider = new Collider(x,y, width, height);
    this->type = type;
}

Collider * _GameObject::getCollider(){

    return collider;
}

void _GameObject::destroy()
{

}

float _GameObject::getX()
{
    return x;
}
float _GameObject::getY()
{
    return y;
}
int _GameObject::getW()
{
    return width;
}
int _GameObject::getH()
{
    return height;
}
ObjectType _GameObject::getType()
{
    return type;
}
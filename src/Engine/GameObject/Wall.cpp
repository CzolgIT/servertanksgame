#include "Main.h"

Wall::Wall( int x , int y , int width , int height ) : _GameObject( x , y , width , height , STATIC )
{
    collider = new Collider(x,y,width,height);
}


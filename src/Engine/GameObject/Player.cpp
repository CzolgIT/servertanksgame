#include "Main.h"

Player::Player( float x , float y) : _GameObject( x,y,(int)((double)170*TANKSCALE),(int)((double)130*TANKSCALE) , DYNAMIC )
{
    direction=90;
    towerDirection=90;

    moveSpeed = 0;
    directionSpeed = 0;
    towerSpeed = 0;
    collider = new Collider(x,y,width,height, direction);

    blocked = {0,0};
}

void Player::handleEvent( SDL_Event& e )
{
    // not used anymore
}

void Player::move( float timeStep )
{
    // acceleration
    moveSpeed = accelerate( SDL_SCANCODE_UP , moveSpeed , 0 , TANKMAXSPEED , timeStep );
    moveSpeed = accelerate( SDL_SCANCODE_DOWN , moveSpeed , 0 , -TANKMAXSPEED , timeStep );
    directionSpeed = accelerate( SDL_SCANCODE_RIGHT , directionSpeed , 0 , TANKMAXDIR , timeStep );
    directionSpeed = accelerate( SDL_SCANCODE_LEFT , directionSpeed , 0 , -TANKMAXDIR , timeStep );
    towerSpeed = accelerate( SDL_SCANCODE_X , towerSpeed , 0 , TANKMAXDIR , timeStep );
    towerSpeed = accelerate( SDL_SCANCODE_Z , towerSpeed , 0 , -TANKMAXDIR , timeStep );


    double xm = cos(iDirection *M_PI/180) * moveSpeed * timeStep;
    double ym = sin(iDirection *M_PI/180) * moveSpeed * timeStep;

    /* OPTIONAL PUSHING OUT TANK
    if (xm > 0 && blocked.x > 0)
    {
        if (xm > blocked.x)
        {
            x -= xm - blocked.x;
        }
    }
    else if (xm < 0 && blocked.x < 0)
    {
        if (xm < blocked.x)
        {
            x -= xm - blocked.x;
        }
    }
    else
    x -= xm - blocked.x;

    if (ym > 0 && blocked.y > 0)
    {
        if (ym > blocked.y)
        {
            y -= ym - blocked.y;
        }
    }
    else if (ym < 0 && blocked.y < 0)
    {
        if (ym < blocked.y)
        {
            y -= ym - blocked.y;
        }
    }
    else
        y -= ym - blocked.y;
    */

    x -= xm - blocked.x;
    y -= ym - blocked.y;

    blocked.x = 0;
    blocked.y = 0;


    // rotate tank and tower
    direction += directionSpeed * timeStep ;
    towerDirection += directionSpeed * timeStep + towerSpeed * timeStep;

    if ( direction > 360 ) direction -= 360;
    if ( towerDirection > 360 ) towerDirection -= 360;

    if ( direction < 0 ) direction += 360;
    if ( towerDirection < 0 ) towerDirection += 360;

    // dzięki temu kąt obrotu będzie można zapisać jako liczbę
    // od 0 do 180 i zmieści się w jednym bajcie
    iDirection = (int)round(direction/2)*2;
    iTowerDirection = (int)round(towerDirection/2)*2;

    //std::cout << iDirection << "  " << iTowerDirection << "\n";

    // Wall limits
    if( x < (int)((double)width/2) )
    {
        x = (int)((double)width/2) ;
    }
    else if( x > 2048 - (int)((double)width/2) )
    {
        x = 2048 - (int)((double)width/2);
    }

    if( y < (int)((double)height/2) )
    {
        y = (int)((double)height/2);
    }
    else if( y > 2048 - (int)((double)height/2) )
    {
        y = 2048 - (int)((double)height/2);
    }

    collider->update(x,y,width,height, direction);

}

int Player::getTowDir()
{
    return iTowerDirection;
}

float Player::accelerate( int scanCode , float what , float from , float to , float timeStep )
{
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[scanCode])
    {
        if ( from < to ? what < to : what > to )
        {
            what += to * timeStep * TANKACCELERATION ;
            if ( from < to ? what > to : what < to ) what = to;
        }
    }
    else
    {
        if ( from < to ? what > from : what < from )
        {
            what -= to * timeStep * TANKACCELERATION;
            if ( from < to ? what < from : what > from ) what = from;
        }
    }
    return what;
}

SDL_Point Player::shootPosition()
{

    SDL_Point punkt;
    punkt.x = (int)(x+(cos(iTowerDirection *M_PI/180) * -50));
    punkt.y = (int)(y+(sin(iTowerDirection *M_PI/180) * -50));
    return punkt;
}
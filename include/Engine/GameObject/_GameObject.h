#ifndef GameObject_h
#define GameObject_h

#include "Main.h"

enum ObjectType : Uint8{
    STATIC = 0,
    DYNAMIC = 1
};

class _GameObject
{
public:

    _GameObject( float x, float y, int width, int height , ObjectType type);

    // virtual void Start() // not used
    //virtual void update(){}

    virtual void move( float timeStep ){}
    virtual void handleEvent(SDL_Event& e){}
    virtual void destroy();
    virtual Collider * getCollider();

    float getX();
    float getY();
    int getW();
    int getH();
    ObjectType getType();
    bool shouldBeDestroy(){ return toDestroy; }
    void setToBeDestroyed(){ toDestroy = true; }

protected:

    Collider * collider;
    float x,y;
    int width,height;
    bool toDestroy = false;
    ObjectType type;

};

#endif

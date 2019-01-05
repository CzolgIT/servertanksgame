#ifndef Scene_h
#define Scene_h

#include "Main.h"

class _Scene
{
public:

    _Scene();
    bool isRunning() { return running; }
    void update();
    virtual void handleEvents(){}
    int getFlag() { return flagReturn ;}

protected:

    SDL_Event eventHandler;
    bool running;
    int flagReturn;

};

#endif

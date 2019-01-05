#include "Main.h"

_Scene::_Scene()
{
    running = true;
    flagReturn = 1;
}

void _Scene::update()
{
    handleEvents();
}

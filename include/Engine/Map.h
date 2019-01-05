#ifndef Map_h
#define Map_h

#include "Main.h"

class Map
{
public:

    explicit Map();
    void loadFromFile( std::vector<_GameObject*> * gameObjects );

};

#endif

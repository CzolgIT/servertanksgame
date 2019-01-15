#ifndef Map_h
#define Map_h

#include "Main.h"

#define MAP_WIDTH  8
#define MAP_HEIGHT  8

class Map
{
public:

    explicit Map();

    static char * getMapFromFile(char * pointer);

    static std::vector<Wall*> getColliders();


};

#endif

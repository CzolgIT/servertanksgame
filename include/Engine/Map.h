#ifndef Map_h
#define Map_h

#include "Main.h"

#define MAP_WIDTH  64
#define MAP_HEIGHT  64
#define FIELD_SIZE 64

class Map
{
public:

    explicit Map();

    static char * getMapFromFile(char * pointer);

    static std::vector<Wall*> getColliders();

    static std::vector<Collider*> getSpawnPoints();
};

#endif

#include "Main.h"

Map::Map() {}

char * Map::getMapFromFile(char * pointer)
{
    //w, h - 8
    std::ifstream infile("assets/maps/map1.txt");
    char temp;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            infile >> temp;
            pointer[x*8+y] = temp;
        }

    }
    infile.close();
    return pointer;

}



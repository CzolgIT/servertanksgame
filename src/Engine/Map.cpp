#include "Main.h"

Map::Map() {}

void Map::loadFromFile( std::vector<_GameObject*> * gameObjects )
{
    std::ifstream infile("assets/maps/map2.txt");
    int w,h;
    infile >> w >> h;
    char c;

    for(int i =0; i<h; i++)
    {
        for(int j =0; j<w; j++)
        {
            infile >> c;
            if (c == '#')
            {
                auto * wall = new Wall( 32+j*64 , 32+i*64, 64, 64 );
                gameObjects->push_back(wall);
            }
        }
    }
    infile.close();
}
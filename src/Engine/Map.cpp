#include "Main.h"

Map::Map() {}

char * Map::getMapFromFile(char * pointer)
{
    //w, h - 32
    std::ifstream infile("assets/maps/map1.txt");
    char temp;

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            infile >> temp;
            pointer[x*MAP_WIDTH+y] = temp;
        }

    }
    infile.close();
    return pointer;

}

std::vector<Collider*> Map::getSpawnPoints()
{
    std::vector<Collider*> colliders;

    char * map = new char[MAP_HEIGHT*MAP_WIDTH];
    Map::getMapFromFile(map);

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (map[x*MAP_WIDTH+y]== 'S')
            {
                Collider * collider = new Collider(x+FIELD_SIZE*x,y+FIELD_SIZE*y,FIELD_SIZE+FIELD_SIZE/2,FIELD_SIZE+FIELD_SIZE/2);
                colliders.push_back(collider);
            }
        }

    }



    return colliders;


}

std::vector<Wall*>  Map::getColliders()
{
    std::vector<Wall*> colliders;

    char * map = new char[MAP_HEIGHT*MAP_WIDTH];
    Map::getMapFromFile(map);

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (map[x*MAP_WIDTH+y]== 'X')
            {
                SDL_Point pos = {x+FIELD_SIZE*x,y+FIELD_SIZE*y};
                Wall * wall = new Wall(pos,FIELD_SIZE,FIELD_SIZE);
                colliders.push_back(wall);
            }
        }

    }


    return colliders;
}



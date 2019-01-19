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
                Collider * collider = new Collider(FIELD_SIZE*x,FIELD_SIZE*y,FIELD_SIZE+FIELD_SIZE,FIELD_SIZE+FIELD_SIZE);
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
            if (map[y*MAP_WIDTH+x]== 'X')
            {
                SDL_Point pos = {FIELD_SIZE*x,FIELD_SIZE*y};
                Wall * wall = new Wall(pos,FIELD_SIZE,FIELD_SIZE);
                colliders.push_back(wall);
            }
        }

    }


    return colliders;
}



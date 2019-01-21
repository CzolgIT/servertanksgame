#include "Main.h"

Map::Map() {}

char * Map::getMapFromFile(char * pointer)
{
    //w, h - 64
    std::ifstream infile("assets/maps/map2.txt");
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
            if (map[y*MAP_WIDTH+x]== '0' || map[y*MAP_WIDTH+x]== 'A')
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
            if (map[y*MAP_WIDTH+x]== '-' || map[y*MAP_WIDTH+x]== '|' || map[y*MAP_WIDTH+x]== 'V' || map[y*MAP_WIDTH+x]== 'W' ||map[y*MAP_WIDTH+x]== 'X' || map[y*MAP_WIDTH+x]== 'Y')
            {
                SDL_Point pos = {FIELD_SIZE*x,FIELD_SIZE*y};
                Wall * wall = new Wall(pos,FIELD_SIZE,FIELD_SIZE);
                colliders.push_back(wall);
            }
        }

    }
    Wall * upper = new Wall({FIELD_SIZE*MAP_WIDTH/2,0},FIELD_SIZE*MAP_WIDTH,800);
    colliders.push_back(upper);
    Wall * down = new Wall({FIELD_SIZE*MAP_WIDTH/2,FIELD_SIZE*MAP_HEIGHT},FIELD_SIZE*MAP_HEIGHT,800);
    colliders.push_back(down);
    Wall * right = new Wall( {FIELD_SIZE*MAP_WIDTH,FIELD_SIZE*MAP_HEIGHT/2},800,FIELD_SIZE*MAP_HEIGHT);
    colliders.push_back(right);
    Wall * left = new Wall( {0,FIELD_SIZE*MAP_HEIGHT/2},800,FIELD_SIZE*MAP_HEIGHT);
    colliders.push_back(left);

    return colliders;
}



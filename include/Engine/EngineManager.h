#ifndef MpManager_h
#define MpManager_h

#include "Main.h"

class EngineManager
{
public:

    EngineManager( std::vector<std::unique_ptr<Client>>* clients , std::vector<Bullet *>* bullets , std::vector<PowerUp*>* powerUps );

    void checkColliders();
    void move( double stepTime );

    SDL_Point getSpawnPoint();

private:

    std::vector<std::unique_ptr<Client>>* clients;
    std::vector<Bullet *>* bullets;
    std::vector<PowerUp*>* powerUps;
    std::vector<Wall *> walls;
    int bulletIdCounter,powerUpIdCounter;
    double powerUpTimer;

};

#endif

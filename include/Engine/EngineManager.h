#ifndef MpManager_h
#define MpManager_h

#include "Main.h"

class EngineManager
{
public:

    EngineManager( std::vector<std::unique_ptr<Client>>* clients , std::vector<Bullet *>* bullets );

    void sendScoreInfo(std::unique_ptr<Client> &client);
    void checkColliders();
    void move( double stepTime );

private:

    std::vector<std::unique_ptr<Client>>* clients;
    std::vector<Bullet *>* bullets;
    std::vector<Wall *> walls;
    int bulletIdCounter;
    std::map<int,int> scoreMap;

};

#endif

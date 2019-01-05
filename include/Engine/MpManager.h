#ifndef MpManager_h
#define MpManager_h

#include "Main.h"

class MpManager : public _Scene
{
public:

    MpManager(int color = 1);
    void handleEvents();
    void CheckColliders();
    void sendPackets();

private:
    std::vector<_GameObject*> gameObjects;
    Player* player;

};

#endif

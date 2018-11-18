#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_net/SDL_net.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_net.h>
#endif

#include "Packets/BasePacket.h"
#include "Models/Client.h"
#include "Packets/JoinRequestPacket.h"
#include "Packets/JoinResponsePacket.h"
#include "NetManager.h"
#include "Packets/UniversalPacket.h"
#include "Packets/HeartbeatPacket.h"
#include "Packets/PlayerDisconnectedPacket.h"


#define SERVERIP "127.0.0.1" //temporary for testing
#define SERVERPORT 7777 //temporary for testing
#define MAX_CLIENTS 2 //lol

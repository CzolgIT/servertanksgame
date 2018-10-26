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

#include "BasePacket.h"
#include "Client.h"
#include "JoinRequestPacket.h"
#include "JoinResponsePacket.h"
#include "NetManager.h"
#include "UniversalPacket.h"


#define SERVERIP "127.0.0.1" //temporary for testing
#define SERVERPORT 1177 //temporary for testing
#define MAX_CLIENTS 2 //lol

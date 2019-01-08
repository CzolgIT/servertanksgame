#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <iomanip>

#include <cstdio>
#include <sstream>
#include <fstream>
#include <cmath>
#include <typeinfo>
#include <queue>
#include <atomic>
#include <algorithm>
#include <mutex>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_net/SDL_net.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_net.h>
#endif

#include "Packets/BasePacket.h"
#include "Packets/JoinRequestPacket.h"
#include "Packets/JoinResponsePacket.h"
#include "Packets/UniversalPacket.h"
#include "Packets/HeartbeatPacket.h"
#include "Packets/InfoRequestPacket.h"
#include "Packets/GameInfoPacket.h"
#include "Packets/HostChangedPacket.h"
#include "Packets/MapDataPacket.h"
#include "Packets/PlayerDisconnectedPacket.h"
#include "Packets/PlayerJoinedPacket.h"
#include "Packets/PlayerReadyPacket.h"
#include "Packets/StartGameRequestPacket.h"
#include "Packets/SyncPacket.h"
#include "Packets/EventPacket.h"

#include "Models/Client.h"
#include "Room.h"

#include "ConnectionUtils/TcpConnection.h"
#include "ConnectionUtils/UdpConnection.h"

#include "NetManager.h"

#include "Engine/Collisions/Vector2D.h"
#include "Engine/Collisions/Projection.h"
#include "Engine/Collisions/Collider.h"


#include "Engine/GameObject/_GameObject.h"
#include "Engine/GameObject/Bullet.h"
#include "Engine/GameObject/Player.h"
#include "Engine/GameObject/Wall.h"
#include "Engine/Map.h"
#include "Engine/_Scene.h"
#include "Engine/MpManager.h"


#define delete_object(x) {delete x; x = nullptr;}

#define SERVERIP "127.0.0.1" //temporary for testing
#define SERVERPORT 7777 //temporary for testing
#define MAX_CLIENTS 10 //lol


#define TANKMAXSPEED 200
#define TANKMAXDIR 128
#define TANKACCELERATION 3
#define TANKSCALE 0.5
#define BULLETSPEED 500

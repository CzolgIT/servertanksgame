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
#include <map>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_net/SDL_net.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_net.h>
#endif

#include "Models/PowerUpType.h"

#include "Engine/Collisions/Vector2D.h"
#include "Engine/Collisions/Projection.h"
#include "Engine/Collisions/Collider.h"

#include "Packets/BasePacket.h"
#include "Packets/BulletInfoPacket.h"
#include "Packets/CurrentPositionPacket.h"
#include "Packets/JoinRequestPacket.h"
#include "Packets/JoinResponsePacket.h"
#include "Packets/UniversalPacket.h"
#include "Packets/HeartbeatPacket.h"
#include "Packets/InfoRequestPacket.h"
#include "Packets/MapDataPacket.h"
#include "Packets/PlayerDisconnectedPacket.h"
#include "Packets/PlayerDeadPacket.h"
#include "Packets/PlayerJoinedPacket.h"
#include "Packets/PlayerReadyPacket.h"
#include "Packets/SyncPacket.h"
#include "Packets/EventPacket.h"

#include "Timer.h"
#include "Models/Bullet.h"
#include "Models/Client.h"
#include "Models/Wall.h"
#include "Models/PowerUp.h"
#include "Engine/Map.h"
#include "Engine/EngineManager.h"
#include "Packets/PowerUpPacket.h"

#include "ConnectionUtils/TcpConnection.h"
#include "ConnectionUtils/UdpConnection.h"

#include "NetManager.h"




#define delete_object(x) {delete x; x = nullptr;}

//#define SERVERIP "25.63.145.1" //hamachi
//#define SERVERIP "153.19.7.230" //sigma
#define SERVERIP "127.0.0.1" //localhost
#define SERVERPORT 7777
#define MAX_CLIENTS 100


#define TANKMAXSPEED 300
#define TANKMAXDIR 180
#define TANKACCELERATION 3
#define TANKSCALE 0.5
#define BULLETSPEED 1000

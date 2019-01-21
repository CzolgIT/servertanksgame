#ifndef NetManager_h
#define NetManager_h

#include <sstream>
#include "Main.h"

class NetManager
{
public:
    NetManager();
    ~NetManager();
    void update( int argc );
    void acceptClient();
    void processTcp();
    void setHostId(Uint8 hostId);
    void setMapId(Uint8 mapId);

    void processUdp();
    void createRoom(Uint8 hostId, int maxClients);
    void deleteRoom(Uint8 id);

    void monitoring();

    Room* getRoom(Uint8 id);
    Uint8 getAvailableRoomId();

    Uint8 getMapId();
    Uint8 getHostId();
    Uint8 getAvailableId();
    Client* getClient(Uint8 id);
    bool disconnectClient(Uint8 id);

    SDL_Point getSpawnPoint();

private:

    EngineManager* engineManager;

    std::vector<std::unique_ptr<Client>> clients;
    std::vector<Bullet *> bullets;

    std::vector<std::unique_ptr<Room>> rooms;
    IPaddress address;
    TCPsocket TCP_socket; //for connectivity
    SDLNet_SocketSet TCP_SocketSet;
    UDPsocket UDP_socket; //for gameplay
    UDPpacket UDP_packet;
    UniversalPacket universalPacket;
    Uint8 hostId;
    Uint8 mapId;
    Timer* timer;



};

template<class T>
std::string toString(const T&t){
    std::ostringstream stream;
    stream << t;
    return stream.str();
}

#endif

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

    void processUdp();

    void monitoring();

    Uint8 getAvailableId();
    Client* getClient(Uint8 id);
    bool disconnectClient(Uint8 id);

    SDL_Point getSpawnPoint();

private:

    EngineManager* engineManager;

    std::vector<std::unique_ptr<Client>> clients;
    std::vector<Bullet*> bullets;
    std::vector<PowerUp*> powerUps;

    IPaddress address;
    TCPsocket TCP_socket; //for connectivity
    SDLNet_SocketSet TCP_SocketSet;
    UDPsocket UDP_socket; //for gameplay
    UDPpacket UDP_packet;
    UniversalPacket universalPacket;
    Timer* timer;



};

template<class T>
std::string toString(const T&t){
    std::ostringstream stream;
    stream << t;
    return stream.str();
}

#endif

#ifndef NetManager_h
#define NetManager_h

#include "Main.h"

class NetManager
{
public:
    NetManager();
    ~NetManager();
    void Activate();
    void Close();
    void Update();
    void AcceptClient();
    
private:
    std::vector<std::unique_ptr<Client>> clients;

    IPaddress address;
    TCPsocket TCP_socket; //for connectivity
    SDLNet_SocketSet TCP_SocketSet;
    UDPsocket UDP_socket; //for gameplay
    UDPpacket UDP_packet;
    
};

#endif

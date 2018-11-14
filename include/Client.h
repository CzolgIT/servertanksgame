#ifndef CLIENT_H
#define CLIENT_H

#include "Main.h"

class Client
{
public:
    Client(Uint8 ID, TCPsocket tcpsock, UDPsocket udpsock);
    ~Client();
    
    void UDPSend(const BasePacket& packet);
    void TCPSend(const BasePacket& packet);
    void SetUDPAddress(IPaddress address);
    void AttachSocketSet(SDLNet_SocketSet* socketSet);
    void SetPosition(SDL_Point newPosition);

    TCPsocket GetTCPSocket();
    Uint8 GetID();
    SDL_Point GetPosition();

    bool NeedsUDPAddress();


    
private:
    TCPsocket tcpSocket;
    UDPsocket udpSocket;
    UDPpacket udpPacket;
    Uint8 id;
    bool hasUDPAddress;

    SDLNet_SocketSet* SockSet;

    SDL_Point position;
};


#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include "Main.h"

class Client
{
public:
    Client(Uint8 ID, TCPsocket tcpsock, UDPsocket udpsock);
    ~Client();
    
    void udpSend(const BasePacket &packet);
    void tcpSend(const BasePacket &packet);
    void setUdpAddress(IPaddress address);
    void attachSocketSet(SDLNet_SocketSet *socketSet);
    void setPosition(SDL_Point newPosition);
    void setIDirection(int iDirection);
    void setITowerDirection(int iTowerDirection);

    TCPsocket getTcpSocket();
    Uint8 getId();
    SDL_Point getPosition();
    int getIDirection();
    int getITowerDirection();

    bool needsUdpAddress();

    void print();
    
private:
    TCPsocket tcpSocket;
    UDPsocket udpSocket;
    UDPpacket udpPacket;
    Uint8 id;
    bool hasUDPAddress;

    SDLNet_SocketSet* SockSet;

    SDL_Point position;
    int iDirection, iTowerDirection;
};


#endif // CLIENT_H

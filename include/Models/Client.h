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
    void setKeys(int x, bool keys);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getTankDirection() const;

    void setTankDirection(float tankDirection);

    float getTowerDirection() const;

    void setTowerDirection(float towerDirection);

    void move();
    float accelerate(bool isPressed, float what , float from , float to , float timeStep );


    TCPsocket getTcpSocket();
    Uint8 getId();
    SDL_Point getPosition();
    int getIDirection();
    int getITowerDirection();
    bool getKeys(int i);

    bool needsUdpAddress();

    void print();
    
private:
    TCPsocket tcpSocket;
    UDPsocket udpSocket;
    UDPpacket udpPacket;
    Uint8 id;
    bool hasUDPAddress;

    SDLNet_SocketSet* SockSet;

    SDL_Point position={128,128};
    int iDirection=0, iTowerDirection=0;
    float x=0,y=0;
    float tankDirection=0,towerDirection=0;
    bool keys[7]; // up down left right z x space
    float moveSpeed=0,directionSpeed=0,towerSpeed=0;
};


#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include "Main.h"

class Client
{
public:

    Client(Uint8 ID, TCPsocket tcpsock, UDPsocket udpsock);
    ~Client();

    // Networking
    void udpSend(const BasePacket &packet);
    void tcpSend(const BasePacket &packet);
    void setUdpAddress(IPaddress address);
    void attachSocketSet(SDLNet_SocketSet *socketSet);
    TCPsocket getTcpSocket();
    Uint8 getId();
    bool isIsPlayerReady() const;

    void setIsPlayerReady(bool isPlayerReady);

    void setNickname(std::string nickname);
    std::string getNickname();
    void setKeys(int x, bool keys);
    bool getKeys(int i);
    bool needsUdpAddress();

    void setPosition(SDL_Point newPosition);
    void setIDirection(int iDirection);
    void setITowerDirection(int iTowerDirection);


    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    float getTankDirection() const;
    void setTankDirection(float tankDirection);
    float getTowerDirection() const;
    void setTowerDirection(float towerDirection);

    void setTankSpeed(int tankSpeed);

    void move( float timeStep );
    float accelerate(bool isPressed, float what , float from , float to , float timeStep );
    SDL_Point shootPosition();
    bool isReadyToShoot();
    void setUnableToShoot();

    void setBulletsPointer( std::vector<Bullet *> *bullets );

    SDL_Point getPosition();
    int getIDirection();
    int getITowerDirection();
    int getTankSpeed();
    int getRotationSpeed();
    int getTurretRotationSpeed();

    Uint8 getActHp() const;
    Collider* getCollider();
    void setActHp(Uint8 actHp);



    void print();
    void doDamage(int damage);
    
private:
    TCPsocket tcpSocket;
    UDPsocket udpSocket;
    UDPpacket udpPacket;
    Uint8 id;
    bool hasUDPAddress;
    std::string nickname;

    int actHp = 100;

    bool isPlayerReady;
    SDLNet_SocketSet* SockSet;

    // GameObject
    SDL_Point position={128,128};
    float x=128,y=128;
    Collider *collider;

    int iDirection=0, iTowerDirection=0;
    float tankDirection=0,towerDirection=0;
    bool keys[7]={false}; // up down left right z x space
    float tankSpeed=0,rotationSpeed=0,turretRotationSpeed=0;

    bool readyToShoot=false;
    float shootLoading=0;

    std::vector<Bullet *> *bullets;

};


#endif // CLIENT_H

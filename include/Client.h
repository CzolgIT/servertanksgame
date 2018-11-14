#ifndef CLIENT_H
#define CLIENT_H

#include "Main.h"

class Client
{
public:
    Client(Uint8 ID, UDPsocket udpsock);
    ~Client();
    
    void UDPSend(const BasePacket& packet);
    void TCPSend(const BasePacket& packet);
    void SetUDPAddress(IPaddress address);
    
    Uint8 GetID() {return id;}
    
private:
    UDPsocket udpSocket;
    UDPpacket udpPacket;
    Uint8 id;
};


#endif // CLIENT_H

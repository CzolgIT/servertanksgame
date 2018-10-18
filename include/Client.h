#ifndef CLIENT_H
#define CLIENT_H

#include <SDL2/SDL_net.h>
#include<memory>
#include"../shared/BasePacket.h"

class Client
{
public:
    Client(Uint8 ID, UDPsocket udpsock);
    ~Client();
    
    void UDPSend(const BasePacket& packet);
    
    void SetUDPAddress(IPaddress address);
    
    Uint8 GetID() {return ID_;}
    
private:
    UDPsocket UDPsocket_;
    UDPpacket UDPpacket_;
    Uint8 ID_;
    
    
    
};


#endif

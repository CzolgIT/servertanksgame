#include "Main.h"

UniversalPacket::UniversalPacket():
    size(UNIVERSAL_PACKET_SIZE),
    data(new Uint8[UNIVERSAL_PACKET_SIZE]())
{}

Uint8 * UniversalPacket::getData() const
{
  return data.get();  
}

unsigned int UniversalPacket::getSize() const
{
    return size;
}

std::unique_ptr<BasePacket> UniversalPacket::createFromContents()
{
    
    switch(data[0])
    {
        case PT_PLAYER_DISCONNECTED:
            return constructPacket(new PlayerDisconnectedPacket);
        case PT_SYNC:
            return constructPacket(new SyncPacket);
        case PT_HEARTBEAT:
            return constructPacket(new HeartbeatPacket);
        case PT_JOIN_REQUEST:
            return constructPacket(new JoinRequestPacket);
        case PT_JOIN_RESPONSE:
            return constructPacket(new JoinResponsePacket);
        case PT_EVENT:
            return constructPacket(new EventPacket);
        case PT_INFO_REQUEST:
            return constructPacket(new InfoRequestPacket);
        case PT_PLAYER_READY:
            return constructPacket(new PlayerReadyPacket);
        case PT_PLAYER_DEAD:
            return constructPacket(new PlayerDeadPacket);
        case PT_POWERUP:
            return constructPacket(new PowerUpPacket);
        default:
            return nullptr;
    }
}

std::unique_ptr<BasePacket> UniversalPacket::constructPacket(BasePacket *packet)
{
    
    memcpy(packet->getData(), data.get(), packet->getSize());
    
    return std::unique_ptr<BasePacket>(packet);
    
    
}

UniversalPacket::~UniversalPacket() {

}



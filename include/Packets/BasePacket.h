#ifndef BASEPACKET_H
#define BASEPACKET_H

#include "Main.h"

// First byte of a packed should always be the type
enum PacketType : Uint8{
    //todo: packettype list
    PT_BASE = 0,
    PT_JOIN_REQUEST = 1,
    PT_JOIN_RESPONSE = 2,
    PT_HEARTBEAT = 3,
    PT_PLAYER_DISCONNECTED = 4,
    PT_PLAYER_JOINED = 5,
    PT_PLAYER_READY = 6,
    PT_SYNC = 7,
    PT_START_REQUEST = 8,
    PT_HOST_CHANGED = 9,
    PT_GAME_INFO = 10,
    PT_EVENT = 11,
    PT_MAP_INFO = 12,
    PT_INFO_REQUEST = 13,
    PT_UNKNOWN = 0xff
};

class BasePacket
{
protected:
    BasePacket( PacketType type, unsigned int packetSize );
        // Content of the packet 
        std::unique_ptr<Uint8[]> data;
        
        unsigned int size;
    
        
public:
    virtual ~BasePacket();
    
    //return the type of the packet
    
    virtual PacketType getType() const;
    
    virtual Uint8* getData() const;
    
    virtual unsigned int getSize() const;
    
    virtual void print() const;
};
Uint32 floatToUint32(float f);
float Uint32toFloat(Uint32 i);
#endif

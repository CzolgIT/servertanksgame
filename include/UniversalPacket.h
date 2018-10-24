#ifndef UNIVERSAL_PACKET_H
#define UNIVERSAL_PACKET_H

#include <memory>
#include <SDL2/SDL.h>

// Here will be all includes for futher packets (based on their type)
#include "BasePacket.h"
#include "JoinRequestPacket.h"
#include "JoinResponsePacket.h"

// Larger than the largest packet that will be received
#define UNIVERSAL_PACKET_SIZE 100

class UniversalPacket{
public:
    UniversalPacket();
    ~UniversalPacket();
    
    Uint8* getData() const;
    unsigned int getSize() const;
    
    std::unique_ptr<BasePacket> createFromContents();
private:
    std::unique_ptr<Uint8[]> data;
    
    unsigned int size;
    
    std::unique_ptr<BasePacket> constructPacket(BasePacket* packet);
};


#endif

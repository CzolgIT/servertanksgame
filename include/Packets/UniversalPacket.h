#ifndef UNIVERSAL_PACKET_H
#define UNIVERSAL_PACKET_H

#include "Main.h"

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
    unsigned int size;
    std::unique_ptr<Uint8[]> data;
    std::unique_ptr<BasePacket> constructPacket(BasePacket *packet);
};


#endif

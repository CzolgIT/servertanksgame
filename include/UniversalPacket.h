#ifndef UNIVERSAL_PACKET_H
#define UNIVERSAL_PACKET_H

#include "Main.h"

// Larger than the largest packet that will be received
#define UNIVERSAL_PACKET_SIZE 100

class UniversalPacket{
public:
    UniversalPacket();
    ~UniversalPacket();
    
    Uint8* GetData() const;
    unsigned int GetSize() const;
    
    std::unique_ptr<BasePacket> CreateFromContents();
private:
    std::unique_ptr<Uint8[]> data;
    
    unsigned int size;
    
    std::unique_ptr<BasePacket> ConstructPacket(BasePacket *packet);
};


#endif

#include "Main.h"

UniversalPacket::UniversalPacket():
    size(UNIVERSAL_PACKET_SIZE),
    data(new Uint8[UNIVERSAL_PACKET_SIZE]())
{}

Uint8 * UniversalPacket::GetData() const
{
  return data.get();  
}

unsigned int UniversalPacket::GetSize() const
{
    return size;
}

std::unique_ptr<BasePacket> UniversalPacket::CreateFromContents()
{
    
    switch(data[0])
    {
        default:
            return nullptr;
    }
}

std::unique_ptr<BasePacket> UniversalPacket::ConstructPacket(BasePacket *packet)
{
    
    memcpy(packet->GetData(), data.get(), packet->GetSize());
    
    return std::unique_ptr<BasePacket>(packet);
    
    
}



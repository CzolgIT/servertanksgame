#include"Main.h"

BasePacket::BasePacket( PacketType type, unsigned int packetSize ):
        size((packetSize > 1) ? packetSize : 1) // size should be always 1 or greater

        {
            data = std::unique_ptr<Uint8[]>(new Uint8[size]()); //allocate
            
            data[0] = type;
            
        }
BasePacket::~BasePacket()
{
}

PacketType BasePacket::GetType() const
{
          return (PacketType)data[0];
    
}

Uint8 * BasePacket::GetData() const
{
    return data.get();
}

unsigned int BasePacket::GetSize() const
{
    return size;
}

void BasePacket::Print() const
{
    std::cout << "Not defined - this is a base packet\n";
}




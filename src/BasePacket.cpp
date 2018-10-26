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

PacketType BasePacket::getType() const
{
          return (PacketType)data[0];
    
}

Uint8 * BasePacket::getData() const
{
    return data.get();
}

unsigned int BasePacket::getSize() const
{
    return size;
}

void BasePacket::print() const
{
    std::cout << "Not defined - this is a base packet\n";
}




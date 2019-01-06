#include "Main.h"

BasePacket::BasePacket( PacketType type, unsigned int packetSize ):
        size((packetSize > 1) ? packetSize : 1) // size should be always 1 or greater

        {
            data = std::unique_ptr<Uint8[]>(new Uint8[size]()); //allocate
            
            data[0] = type;
            
        }
BasePacket::~BasePacket() = default;

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


Uint32 floatToUint32(float f)
{
    Uint32 i = 0;
    char* iPtr = (char*)&i;
    char* fPtr = (char*)&f;
    memcpy(iPtr, fPtr, 4);
    return i;
}

float Uint32toFloat(Uint32 i)
{
    float f = 0;
    char* fPtr = (char*)&f;
    char* iPtr = (char*)&i;
    memcpy(fPtr, iPtr, 4);
    return f;
}
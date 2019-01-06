#include "Main.h"

EventPacket::EventPacket() : BasePacket(PT_EVENT,EVENT_PACKET_SIZE)
{

}


void EventPacket::SetKeys(bool keys[4])
{
    data[1] = keys[0];
    data[2] = keys[1];
    data[3] = keys[2];
    data[4] = keys[3];
}

bool * EventPacket::GetKeys()
{
    bool * keys = new bool[4];
    keys[0] = data[1];
    keys[1] = data[2];
    keys[2] = data[3];
    keys[3] = data[4];
    return keys;
}

EventPacket::~EventPacket() = default;

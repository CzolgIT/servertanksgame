#include "Main.h"

EventPacket::EventPacket() : BasePacket(PT_EVENT,EVENT_PACKET_SIZE)
{

}


void EventPacket::setKeys(bool *keys)
{
    data[2] = keys[0];
    data[3] = keys[1];
    data[4] = keys[2];
    data[5] = keys[3];
    data[6] = keys[4];
    data[7] = keys[5];
    data[8] = keys[6];
}

bool * EventPacket::getKeys()
{
    bool * keys = new bool[7];
    keys[0] = data[2];
    keys[1] = data[3];
    keys[2] = data[4];
    keys[3] = data[5];
    keys[4] = data[6];
    keys[5] = data[7];
    keys[6] = data[8];
    return keys;
}

void EventPacket::setId(Uint8 id) {
    data[1] = id;
}

void EventPacket::setTime(Uint32 time) {
    SDLNet_Write32(time, &data[9]);
}

Uint8 EventPacket::getId() {
    return data[1];
}

Uint32 EventPacket::getTime() {
    SDLNet_Read32(&data[9]);
}

void EventPacket::print() const {
    std::cout << "Move packet received" << std::endl;
}

EventPacket::~EventPacket() = default;

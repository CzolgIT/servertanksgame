
#include <Packets/JoinResponsePacket.h>

#include "Main.h"

void JoinResponsePacket::setResponse(JoinResponse joinResponse){

    data[1] = joinResponse;
}

JoinResponse JoinResponsePacket::getResponse() const
{
    return (JoinResponse)data[1];
}

void JoinResponsePacket::setId(Uint8 id) {
    data[2] = id;
}

Uint8 JoinResponsePacket::getId() const {
    return (Uint8)data[2];
}

void JoinResponsePacket::setIsHost(bool b) {
    if(b)
        data[3] = 1;
    else
        data[3] = 0;
}

bool JoinResponsePacket::isHost() {
    return (Uint8)data[3] == 1;
}

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

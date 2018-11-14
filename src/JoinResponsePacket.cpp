
#include <JoinResponsePacket.h>

#include "Main.h"

void JoinResponsePacket::SetResponse(JoinResponse joinResponse){

    data[1] = joinResponse;
}

JoinResponse JoinResponsePacket::GetResponse() const
{
    return (JoinResponse)data[1];
}

void JoinResponsePacket::SetId(Uint8 id) {
    data[2] = id;
}

Uint8 JoinResponsePacket::GetId() const {
    return (Uint8)data[2];
}

#include "Main.h"

void JoinResponsePacket::SetResponse(JoinResponse joinResponse){

    data[1] = joinResponse;
}

JoinResponse JoinResponsePacket::GetResponse() const
{
    return (JoinResponse)data[1];
}

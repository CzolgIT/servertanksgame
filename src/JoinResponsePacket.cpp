#include "Main.h"

void JoinResponsePacket::setResponse(JoinResponse joinResponse){

    data[1] = joinResponse;
}

JoinResponse JoinResponsePacket::getResponse() const
{
    return (JoinResponse)data[1];
}

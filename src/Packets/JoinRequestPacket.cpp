#include "Main.h"

JoinRequestPacket::JoinRequestPacket():BasePacket(PT_JOIN_REQUEST, JOINREQUEST_PACKET_SIZE) {}

void JoinRequestPacket::setNickname(std::string nickname)
{
    data[1] = 'x';
    data[2] = 'd';
    data[3] = ' ';
    data[4] = ' ';
    data[5] = ' ';
    data[6] = ' ';
    data[7] = ' ';
    data[8] = ' ';
    data[9] = 'x';
    data[10] = 'd';

}

std::string JoinRequestPacket::getNickname()
{
    return toString(data[1])+toString(data[2])+toString(data[3])+toString(data[4])+toString(data[5])
          +toString(data[6])+toString(data[7])+toString(data[8])+toString(data[9])+toString(data[10]);
}
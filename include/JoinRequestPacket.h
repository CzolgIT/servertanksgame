#ifndef JOIN_REQUEST_PACKET_H
#define JOIN_REQUEST_PACKET_H

#include "Main.h"

#define JOINREQUEST_PACKET_SIZE (1+8)

class JoinRequestPacket : public BasePacket
{
public:
    JoinRequestPacket() :BasePacket(PT_JOIN_REQUEST, JOINREQUEST_PACKET_SIZE){}
    ~JoinRequestPacket(){}
};

#endif

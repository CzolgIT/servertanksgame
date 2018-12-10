#ifndef JOIN_REQUEST_PACKET_H
#define JOIN_REQUEST_PACKET_H
#endif

#include "Main.h"

#define JOINREQUEST_PACKET_SIZE (1+8)

class JoinRequestPacket : public BasePacket
{
public:
    JoinRequestPacket() :BasePacket(PT_JOIN_REQUEST, JOINREQUEST_PACKET_SIZE){}
    ~JoinRequestPacket(){}

    void setNickname(std::string nick);

    std::string getNickname();


private:
    Uint64 nickname;

    void uint64ToString();
};


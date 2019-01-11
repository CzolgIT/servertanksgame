#ifndef JOIN_REQUEST_PACKET_H
#define JOIN_REQUEST_PACKET_H

#include "Main.h"


// packet type + 10 chars
#define JOINREQUEST_PACKET_SIZE (1+10)

class JoinRequestPacket : public BasePacket
{
public:

    JoinRequestPacket();
    void setNickname(std::string nickname);

    std::string getNickname();

};


#endif

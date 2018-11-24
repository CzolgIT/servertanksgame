//
// Created by inql on 22.11.18.
//

#ifndef SERVERTANKSGAME_HOSTCHANGEDPACKET_H
#define SERVERTANKSGAME_HOSTCHANGEDPACKET_H

#include "Main.h"

#define HOSTCHANGED_PACKET_SIZE (1+1)

class HostChangedPacket : public BasePacket{
public:
    HostChangedPacket():BasePacket(PT_HOST_CHANGED, HOSTCHANGED_PACKET_SIZE){}
    ~HostChangedPacket();


};


#endif //SERVERTANKSGAME_HOSTCHANGEDPACKET_H

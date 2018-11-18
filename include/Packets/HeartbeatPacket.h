//
// Created by inql on 14.11.18.
//

#ifndef HEARTBEATPACKET_H
#define HEARTBEATPACKET_H

#include "Main.h"

#define HEARTBEAT_PACKET_SIZE (1+1)

// Let the receiver know that server is alive

class HeartbeatPacket : public BasePacket
{
public:
    HeartbeatPacket();
    HeartbeatPacket(Uint8 id);
    ~HeartbeatPacket();

    void setId(Uint8 id);

    Uint8 getId() const;

    void print() const override;

};


#endif //HEARTBEATPACKET_H

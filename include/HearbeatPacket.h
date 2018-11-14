//
// Created by inql on 14.11.18.
//

#ifndef TANKSGAME_HEARBEATPACKET_H
#define TANKSGAME_HEARBEATPACKET_H

#include "Main.h"

#define HEARTBEAT_PACKET_SIZE (1+1)

// Let the receiver know that server is alive

class HearbeatPacket : public BasePacket
{
public:
    HearbeatPacket();
    HearbeatPacket(Uint8 id);
    ~HearbeatPacket();

    void setId(Uint8 id);

    Uint8 getId() const;

    void print() const override;

};


#endif //TANKSGAME_HEARBEATPACKET_H

//
// Created by inql on 20.11.18.
//

#ifndef SERVERTANKSGAME_PLAYERJOINEDPACKET_H
#define SERVERTANKSGAME_PLAYERJOINEDPACKET_H

#include "Main.h"

#define PLAYERJOINED_PACKET_SIZE (1+1+8)

class PlayerJoinedPacket : public BasePacket {
public:
    PlayerJoinedPacket();
    PlayerJoinedPacket(Uint8 id);
    ~PlayerJoinedPacket();

    void setId(Uint8 id);
    //todo: initial position

    Uint8 getId();
    //todo: get initial position

    void print()const override;

private:
    Uint8 id;
};


#endif //SERVERTANKSGAME_PLAYERJOINEDPACKET_H

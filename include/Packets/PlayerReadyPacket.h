//
// Created by inql on 20.11.18.
//

#ifndef SERVERTANKSGAME_PLAYERREADYPACKET_H
#define SERVERTANKSGAME_PLAYERREADYPACKET_H

#include "Main.h"

#define PLAYERREADY_PACKET_SIZE (1+1)

class PlayerReadyPacket : public BasePacket {
public:
    PlayerReadyPacket();
    PlayerReadyPacket(Uint8 id);
    ~PlayerReadyPacket();

    void setId(Uint8 id);

    Uint8 getId();

private:
    Uint8 id;


};


#endif //SERVERTANKSGAME_PLAYERREADYPACKET_H

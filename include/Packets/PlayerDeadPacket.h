//
// Created by inql on 20.01.19.
//

#ifndef SERVERTANKSGAME_PLAYERDEADPACKET_H
#define SERVERTANKSGAME_PLAYERDEADPACKET_H

#include "Main.h"

#define PLAYERDEAD_PACKET_SIZE (1+1+1)

class PlayerDeadPacket : public BasePacket {
public:
    PlayerDeadPacket();
    ~PlayerDeadPacket();

    void setPlayerId(Uint8 id);
    void setKillerId(Uint8 id);
    Uint8 getPlayerId();
    Uint8 getKillerId();

};


#endif //SERVERTANKSGAME_PLAYERDEADPACKET_H

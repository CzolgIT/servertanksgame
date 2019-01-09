//
// Created by inql on 09.01.19.
//

#ifndef SERVERTANKSGAME_LASTPLAYERSENTPACKET_H
#define SERVERTANKSGAME_LASTPLAYERSENTPACKET_H

#include "Main.h"
#define LAST_PLAYER_SENT_SIZE (1+1)
class LastPlayerSentPacket : public BasePacket{
public:
    LastPlayerSentPacket();
    ~LastPlayerSentPacket();
};

#endif //SERVERTANKSGAME_LASTPLAYERSENTPACKET_H

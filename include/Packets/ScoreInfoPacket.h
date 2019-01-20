//
// Created by mm on 1/20/19.
//

#ifndef SERVERTANKSGAME_SCOREINFOPACKET_H
#define SERVERTANKSGAME_SCOREINFOPACKET_H


#include "Main.h"

#define SCORE_INFO_PACKET_SIZE (1+1+30)


class ScoreInfoPacket : public BasePacket {
public:

    ScoreInfoPacket();
    void setPlayerId(int id);
    Uint8 getPlayerId();

    ~ScoreInfoPacket();
};

#endif //SERVERTANKSGAME_SCOREINFOPACKET_H

//
// Created by mm on 1/20/19.
//

#ifndef SERVERTANKSGAME_SCOREINFOPACKET_H
#define SERVERTANKSGAME_SCOREINFOPACKET_H


#include "Main.h"

#define SCORE_INFO_PACKET_SIZE (1+1+2)


class ScoreInfoPacket : public BasePacket {
public:

    ScoreInfoPacket();
    void setPlayerId(int id);
    Uint8 getPlayerId();
    void setPlayerStatsId(Uint8 id);
    Uint8 getPlayerStatsId();
    void setPlayerKills(Uint8 killCount);
    Uint8 getPlayerKills();


    ~ScoreInfoPacket();
};

#endif //SERVERTANKSGAME_SCOREINFOPACKET_H

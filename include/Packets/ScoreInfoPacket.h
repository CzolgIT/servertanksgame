//
// Created by mm on 1/20/19.
//

#ifndef SERVERTANKSGAME_SCOREINFOPACKET_H
#define SERVERTANKSGAME_SCOREINFOPACKET_H


#include "Main.h"

#define SCORE_INFO_PACKET_SIZE (1+3)


class ScoreInfoPacket : public BasePacket {
public:

    ScoreInfoPacket();
    void setPlayerStatsId(Uint8 id);
    Uint8 getPlayerStatsId();
    void setPlayerKills(Uint8 killCount);
    Uint8 getPlayerKills();
    void setPlayerDeaths(Uint8 deathCount);
    Uint8 getPlayerDeaths();


    ~ScoreInfoPacket();
};

#endif //SERVERTANKSGAME_SCOREINFOPACKET_H

//
// Created by inql on 22.11.18.
//

#include "Main.h"

#ifndef SERVERTANKSGAME_GAMEINFOPACKET_H
#define SERVERTANKSGAME_GAMEINFOPACKET_H

#define GAMEINFO_PACKET_SIZE (1+1+1 + MAX_CLIENTS)

// data indexes explanation:
// data[0] -> packet type
// data[1] -> host id
// data[2] -> map id
// data[3...3+MAX_CLIENTS] -> other players ids
class GameInfoPacket : BasePacket{
public:

};


#endif //SERVERTANKSGAME_GAMEINFOPACKET_H

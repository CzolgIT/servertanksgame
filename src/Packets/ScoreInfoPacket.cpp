//
// Created by mm on 1/20/19.
//
#include "Main.h"

ScoreInfoPacket::ScoreInfoPacket() : BasePacket(PT_SCORE_INFO, SCORE_INFO_PACKET_SIZE) {

}

void ScoreInfoPacket::setPlayerId(int id) {
    data[1] = (Uint8) id;
}

Uint8 ScoreInfoPacket::getPlayerId() {
    return (Uint8) data[1];
}



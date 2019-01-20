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

void ScoreInfoPacket::setPlayerStatsId(Uint8 id) {
    data[2] = id;
}

Uint8 ScoreInfoPacket::getPlayerStatsId() {
    return data[2];
}

void ScoreInfoPacket::setPlayerKills(Uint8 killCount) {
    data[3] = killCount;
}

Uint8 ScoreInfoPacket::getPlayerKills() {
    return data[3];
}

ScoreInfoPacket::~ScoreInfoPacket() = default;



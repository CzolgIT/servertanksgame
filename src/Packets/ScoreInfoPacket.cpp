//
// Created by mm on 1/20/19.
//
#include "Main.h"

ScoreInfoPacket::ScoreInfoPacket() : BasePacket(PT_SCORE_INFO, SCORE_INFO_PACKET_SIZE) {

}

void ScoreInfoPacket::setPlayerStatsId(Uint8 id) {
    data[1] = id;
}

Uint8 ScoreInfoPacket::getPlayerStatsId() {
    return data[1];
}

void ScoreInfoPacket::setPlayerKills(Uint8 killCount) {
    data[2] = killCount;
}

Uint8 ScoreInfoPacket::getPlayerKills() {
    return data[2];
}

void ScoreInfoPacket::setPlayerDeaths(Uint8 death) {
    data[3] = death;
}

Uint8 ScoreInfoPacket::getPlayerDeaths() {
    return data[3];
}
void ScoreInfoPacket::print() const {
    std::cout << "ScoreInfoPacket info: ID:" << (int)data[1] << " K: " << (int)data[2] << "D: "<<(int)data[3] << std::endl;
}
ScoreInfoPacket::~ScoreInfoPacket() = default;



//
// Created by inql on 20.01.19.
//

#include "Main.h"

PlayerDeadPacket::PlayerDeadPacket() : BasePacket(PT_PLAYER_DEAD,PLAYERDEAD_PACKET_SIZE) {

}

PlayerDeadPacket::~PlayerDeadPacket() {

}

void PlayerDeadPacket::setPlayerId(Uint8 id) {
    data[1] = id;
}

void PlayerDeadPacket::setKillerId(Uint8 id) {
    data[2] = id;
}

Uint8 PlayerDeadPacket::getPlayerId() {
    return data[1];
}

Uint8 PlayerDeadPacket::getKillerId() {
    return data[2];
}

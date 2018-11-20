//
// Created by inql on 20.11.18.
//
#include "Main.h"

PlayerReadyPacket::PlayerReadyPacket() : BasePacket(PT_PLAYER_READY,PLAYERREADY_PACKET_SIZE) {
}

PlayerReadyPacket::PlayerReadyPacket(Uint8 id) : PlayerReadyPacket() {
    setId(id);
}

void PlayerReadyPacket::setId(Uint8 id) {
    this->id = id;
}

Uint8 PlayerReadyPacket::getId() {
    return this->id;
}

PlayerReadyPacket::~PlayerReadyPacket() = default;

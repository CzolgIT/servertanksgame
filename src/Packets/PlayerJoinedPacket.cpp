//
// Created by inql on 20.11.18.
//

#include "Main.h"

PlayerJoinedPacket::PlayerJoinedPacket():BasePacket(PT_PLAYER_JOINED,PLAYERJOINED_PACKET_SIZE) {

}

PlayerJoinedPacket::PlayerJoinedPacket(Uint8 id):PlayerJoinedPacket() {
    setId(id);
}

PlayerJoinedPacket::~PlayerJoinedPacket() = default;

void PlayerJoinedPacket::setId(Uint8 id) {
    this->id = id;
}

Uint8 PlayerJoinedPacket::getId() {
    return id;
}

void PlayerJoinedPacket::print() const {
    std::cout << "Player ID: " << (int)this->id << "has joined." << std::endl;
}

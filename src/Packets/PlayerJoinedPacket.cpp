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
    data[2] = id;
}

Uint8 PlayerJoinedPacket::getId() {
    return data[2];
}

void PlayerJoinedPacket::print() const {
    std::cout << "Player ID: " << (int)data[2]<< "has joined." << std::endl;
}

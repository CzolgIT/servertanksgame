//
// Created by inql on 20.11.18.
//
#include "Main.h"

PlayerJoinedPacket::PlayerJoinedPacket():BasePacket(PT_PLAYER_JOINED,PLAYERJOINED_PACKET_SIZE) {

}

//PlayerJoinedPacket::PlayerJoinedPacket(Uint8 id):PlayerJoinedPacket() {
//    setId(id);
//}

PlayerJoinedPacket::~PlayerJoinedPacket() = default;

void PlayerJoinedPacket::setId(Uint8 id) {
    data[1] = id;
}

Uint8 PlayerJoinedPacket::getId() {
    return data[1];
}

void PlayerJoinedPacket::print() const {
    std::cout << "Player ID: " << (int)data[1]<< " nickname: "<< getNickname()  << "has joined." << std::endl;
}

void PlayerJoinedPacket::setNickname(std::string nickname) {
    data[2] = (Uint8)nickname[0];
    data[3] = (Uint8)nickname[1];
    data[4] = (Uint8)nickname[2];
    data[5] = (Uint8)nickname[3];
    data[6] = (Uint8)nickname[4];
    data[7] = (Uint8)nickname[5];
    data[8] = (Uint8)nickname[6];
    data[9] = (Uint8)nickname[7];
    data[10] = (Uint8)nickname[8];
    data[11] = (Uint8)nickname[9];
}

std::string PlayerJoinedPacket::getNickname() const {
    return toString(data[2])+toString(data[3])+toString(data[4])+toString(data[5])
           +toString(data[6])+toString(data[7])+toString(data[8])+toString(data[9])+toString(data[10])+toString(data[11]);
}

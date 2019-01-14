//
// Created by inql on 20.11.18.
//
#include "Main.h"

PlayerJoinedPacket::PlayerJoinedPacket():BasePacket(PT_PLAYER_JOINED,PLAYERJOINED_PACKET_SIZE) {
    for(int i=2; i<12; i++){
        data[i] = (Uint8)0;
    }
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
    for(int i =0; i<nickname.length(); i++){
        data[i+2] = (Uint8)nickname[i];
    }
}

std::string PlayerJoinedPacket::getNickname() const {
    return toString(data[2])+toString(data[3])+toString(data[4])+toString(data[5])
           +toString(data[6])+toString(data[7])+toString(data[8])+toString(data[9])+toString(data[10])+toString(data[11]);
}

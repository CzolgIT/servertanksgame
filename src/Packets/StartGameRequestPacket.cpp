//
// Created by inql on 20.11.18.
//
#include "Main.h"


StartGameRequestPacket::StartGameRequestPacket() : BasePacket(PT_START_REQUEST, STARTREQUEST_PACKET_SIZE){

}

StartGameRequestPacket::StartGameRequestPacket(Uint8 id, Uint8 roomId) : StartGameRequestPacket(){

    setId(id);
    setRoomId(roomId);
}

StartGameRequestPacket::~StartGameRequestPacket() = default;

void StartGameRequestPacket::setId(Uint8 id) {
    this->id = id;
}

void StartGameRequestPacket::setRoomId(Uint8 roomId) {
    this->roomId = roomId;
}

Uint8 StartGameRequestPacket::getId() {
    return this->id;
}

Uint8 StartGameRequestPacket::getRoomId() {
    return this->roomId;
}

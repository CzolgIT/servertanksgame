//
// Created by inql on 07.01.19.
//
#include "Main.h"

InfoRequestPacket::InfoRequestPacket() : BasePacket(PT_INFO_REQUEST, INFOREQUEST_PACKET_SIZE) {

}

InfoRequestPacket::InfoRequestPacket(Uint8 id, RequestType requestType) : InfoRequestPacket() {
    setId(id);
    setRequested(requestType);
}

InfoRequestPacket::~InfoRequestPacket() = default;

void InfoRequestPacket::setId(Uint8 id) {
    data[1] = id;
}

void InfoRequestPacket::setRequested(RequestType type) {
    data[2] = type;
}

Uint8 InfoRequestPacket::getId() const {
    return data[1];
}

RequestType InfoRequestPacket::getRequested() const {
    return (RequestType )data[2];
}

void InfoRequestPacket::print() const {
    std::cout << "Player ID: " << (int)getId() << " asked to be sent the " << ((getRequested() == RT_MAP_DATA) ? "map":"player list") << std::endl;}

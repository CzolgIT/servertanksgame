//
// Created by inql on 14.11.18.
//

#include <HearbeatPacket.h>

#include "Main.h"

HearbeatPacket::HearbeatPacket():BasePacket(PT_HEARTBEAT,HEARTBEAT_PACKET_SIZE) {

}
HearbeatPacket::HearbeatPacket(Uint8 id) : HearbeatPacket() {

    setId(id);

}
HearbeatPacket::~HearbeatPacket() {

}

void HearbeatPacket::setId(Uint8 id) {
    data[1] = id;
}

Uint8 HearbeatPacket::getId() const {
    return data[1];
}

void HearbeatPacket::print() const {
    std::cout << "Player ID: " << (int)getId() << " sent heartbeat" << std::endl;
}




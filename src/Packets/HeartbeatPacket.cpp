//
// Created by inql on 14.11.18.
//

#include "Main.h"

HeartbeatPacket::HeartbeatPacket():BasePacket(PT_HEARTBEAT,HEARTBEAT_PACKET_SIZE) {

}
HeartbeatPacket::HeartbeatPacket(Uint8 id) : HeartbeatPacket() {

    setId(id);

}
HeartbeatPacket::~HeartbeatPacket() {

}

void HeartbeatPacket::setId(Uint8 id) {
    data[1] = id;
}

Uint8 HeartbeatPacket::getId() const {
    return data[1];
}

void HeartbeatPacket::print() const {
    std::cout << "Player ID: " << (int) getId() << " sent heartbeat" << std::endl;
}




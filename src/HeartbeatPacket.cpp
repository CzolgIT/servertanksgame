//
// Created by inql on 14.11.18.
//

#include "Main.h"

HeartbeatPacket::HeartbeatPacket():BasePacket(PT_HEARTBEAT,HEARTBEAT_PACKET_SIZE) {

}
HeartbeatPacket::HeartbeatPacket(Uint8 id) : HeartbeatPacket() {

    SetId(id);

}
HeartbeatPacket::~HeartbeatPacket() {

}

void HeartbeatPacket::SetId(Uint8 id) {
    data[1] = id;
}

Uint8 HeartbeatPacket::GetId() const {
    return data[1];
}

void HeartbeatPacket::Print() const {
    std::cout << "Player ID: " << (int) GetId() << " sent heartbeat" << std::endl;
}




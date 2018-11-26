//
// Created by inql on 18.11.18.
//

#include "Main.h"

SyncPacket::SyncPacket() : BasePacket(PT_SYNC, SYNC_PACKET_SIZE) {

}

SyncPacket::~SyncPacket() {

}

void SyncPacket::setMode(SyncMode syncMode) {

    data[1] = syncMode;

}

void SyncPacket::setId(Uint8 id) {

    data[2] = id;

}

void SyncPacket::setTime(Uint32 time) {

    SDLNet_Write32(time, &data[3]);

}

SyncMode SyncPacket::getMode() {
    return (SyncMode)data[1];
}

Uint8 SyncPacket::getId() {
    return (Uint8)data[2];
}

Uint32 SyncPacket::getTime() {
    return SDLNet_Read32(&data[3]);
}

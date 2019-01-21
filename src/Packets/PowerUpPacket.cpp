//
// Created by inql on 21.01.19.
//
#include "Main.h"

PowerUpPacket::PowerUpPacket() : BasePacket(PT_POWERUP, POWERUP_PACKET_SIZE){

}

PowerUpPacket::~PowerUpPacket() = default;

void PowerUpPacket::setPowerUpType(PowerUpType powerUpType) {
    data[1] = powerUpType;
}

void PowerUpPacket::setToShow(bool toShow) {
    data[2] = toShow;
}

PowerUpType PowerUpPacket::getPowerUpType() {
    return static_cast<PowerUpType>(data[1]);
}
bool PowerUpPacket::getToShow() {
    return data[2];
}

void PowerUpPacket::setPowerUpId(Uint8 id) {
    data[3] = id;
}

void PowerUpPacket::setX(Uint16 x) {
    SDLNet_Write16(x,&data[4]);
}

void PowerUpPacket::setY(Uint16 y) {
    SDLNet_Write16(y,&data[6]);
}

Uint8 PowerUpPacket::getPowerUpId() {
    return data[3];
}

Uint16 PowerUpPacket::getX() {
    return SDLNet_Read16(&data[4]);
}

Uint16 PowerUpPacket::getY() {
    return SDLNet_Read16(&data[6]);
}



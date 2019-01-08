//
// Created by inql on 08.01.19.
//
#include "Main.h"

CurrentPositionPacket::CurrentPositionPacket():BasePacket(PT_CURRENT_POSITION,CURRENT_POSITION_PACKET_SIZE) {

}

void CurrentPositionPacket::setPlayerId(Uint8 playerId) {
    data[1] = playerId;
}

void CurrentPositionPacket::setX(Uint32 x) {
    SDLNet_Write32(x, &data[2]);
}

void CurrentPositionPacket::setY(Uint32 y) {
    SDLNet_Write32(y, &data[6]);
}

void CurrentPositionPacket::setTankRotation(Uint32 tankRotation) {
    SDLNet_Write32(tankRotation, &data[10]);
}

void CurrentPositionPacket::setTurretRotation(Uint32 turretRotation) {
    SDLNet_Write32(turretRotation, &data[14]);
}

Uint8 CurrentPositionPacket::getPlayerId() const {
    return data[1];
}

Uint32 CurrentPositionPacket::getX() const {
    return SDLNet_Read32(&data[2]);
}

Uint32 CurrentPositionPacket::getY() const {
    return SDLNet_Read32(&data[6]);
}

Uint32 CurrentPositionPacket::getTankRotation() const {
    return SDLNet_Read32(&data[10]);
}

Uint32 CurrentPositionPacket::getTurretRotation() const {
    return SDLNet_Read32(&data[14]);
}

void CurrentPositionPacket::print() const {
    std::cout << "CurrentPositionPacketReceived:ID:" << (int)getPlayerId() <<" X:" << (int)getX() << "Y:" << (int)getY() << " TankRot:" << (int)getTankRotation() << " TurretRot:" << (int)getTurretRotation() << std::endl;
}

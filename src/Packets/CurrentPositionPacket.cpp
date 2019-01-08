//
// Created by inql on 08.01.19.
//
#include "Main.h"

CurrentPositionPacket::CurrentPositionPacket():BasePacket(PT_CURRENT_POSITION,CURRENT_POSITION_PACKET_SIZE) {

}

void CurrentPositionPacket::setPlayerId(Uint8 playerId) {
    data[1] = playerId;
}

void CurrentPositionPacket::setX(Uint16 x) {
    SDLNet_Write16(x, &data[2]);
}

void CurrentPositionPacket::setY(Uint16 y) {
    SDLNet_Write16(y, &data[4]);
}

void CurrentPositionPacket::setTankRotation(Uint16 tankRotation) {
    SDLNet_Write16(tankRotation, &data[6]);
}

void CurrentPositionPacket::setTurretRotation(Uint16 turretRotation) {
    SDLNet_Write16(turretRotation, &data[8]);
}

Uint8 CurrentPositionPacket::getPlayerId() const {
    return data[1];
}

Uint16 CurrentPositionPacket::getX() const {
    return SDLNet_Read16(&data[2]);
}

Uint16 CurrentPositionPacket::getY() const {
    return SDLNet_Read16(&data[4]);
}

Uint16 CurrentPositionPacket::getTankRotation() const {
    return SDLNet_Read16(&data[6]);
}

Uint16 CurrentPositionPacket::getTurretRotation() const {
    return SDLNet_Read16(&data[8]);
}

void CurrentPositionPacket::print() const {
    std::cout << "CurrentPositionPacketReceived:ID:" << (int)getPlayerId() <<" X:" << (int)getX() << "Y:" << (int)getY() << " TankRot:" << (int)getTankRotation() << " TurretRot:" << (int)getTurretRotation() << std::endl;
}

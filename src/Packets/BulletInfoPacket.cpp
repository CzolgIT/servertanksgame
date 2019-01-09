//
// Created by inql on 09.01.19.
//
#include "Main.h"

BulletInfoPacket::BulletInfoPacket():BasePacket(PT_BULLET_INFO,BULLET_INFO_PACKET_SIZE) {

}

void BulletInfoPacket::setPlayerId(Uint8 playerId) {
    data[1] = playerId;
}
void BulletInfoPacket::setBulletId(Uint8 bulletId) {
    data[2] = bulletId;
}
void BulletInfoPacket::setX(Uint16 x) {
    SDLNet_Write16(x, &data[3]);
}

void BulletInfoPacket::setY(Uint16 y) {
    SDLNet_Write16(y, &data[5]);
}
void BulletInfoPacket::setAngle(Uint16 angle) {
    SDLNet_Write16(angle, &data[7]);
}


Uint8 BulletInfoPacket::getPlayerId() const {
    return data[1];
}
Uint8 BulletInfoPacket::getBulletId() const {
    return data[2];
}
Uint16 BulletInfoPacket::getX() const {
    return SDLNet_Read16(&data[3]);
}

Uint16 BulletInfoPacket::getY() const {
    return SDLNet_Read16(&data[5]);
}
Uint16 BulletInfoPacket::getAngle() const {
    SDLNet_Read16(&data[7]);
}
void BulletInfoPacket::print() const {
    std::cout << "BulletInfoPacketID:" << (int)getPlayerId() << "BulletID:" << (int)getBulletId() << " X:" << (int)getX() << "Y:" << (int)getY() << " Angle:" << (int)getAngle() << std::endl;
}

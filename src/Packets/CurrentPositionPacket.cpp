#include "Main.h"

CurrentPositionPacket::CurrentPositionPacket():BasePacket(PT_CURRENT_POSITION,CURRENT_POSITION_PACKET_SIZE) {}

void CurrentPositionPacket::setPlayerId(Uint8 playerId) { data[1] = playerId; }
void CurrentPositionPacket::setX(Uint16 x) { SDLNet_Write16(x, &data[2]); }
void CurrentPositionPacket::setY(Uint16 y) { SDLNet_Write16(y, &data[4]); }
void CurrentPositionPacket::setTankRotation(Uint16 tankRotation) { SDLNet_Write16(tankRotation, &data[6]); }
void CurrentPositionPacket::setTurretRotation(Uint16 turretRotation) { SDLNet_Write16(turretRotation, &data[8]); }
void CurrentPositionPacket::setTankSpeed(Uint16 tankSpeed) { SDLNet_Write16(tankSpeed, &data[10]); }
void CurrentPositionPacket::setRotationSpeed(Uint16 rotationSpeed) { SDLNet_Write16(rotationSpeed, &data[12]); }
void CurrentPositionPacket::setTurretRotationSpeed(Uint16 turretRotationSpeed) { SDLNet_Write16(turretRotationSpeed, &data[14]); }
void CurrentPositionPacket::setActualHp(Uint8 actHp) {data[16] = actHp;}
void CurrentPositionPacket::setFromClient(Client* client)
{
    data[1] = client->getId();
    SDLNet_Write16(static_cast<Uint16>(client->getPosition().x), &data[2]);
    SDLNet_Write16(static_cast<Uint16>(client->getPosition().y), &data[4]);
    SDLNet_Write16(static_cast<Uint16>(client->getIDirection()), &data[6]);
    SDLNet_Write16(static_cast<Uint16>(client->getITowerDirection()), &data[8]);
    SDLNet_Write16(static_cast<Uint16>(client->getTankSpeed()), &data[10]);
    SDLNet_Write16(static_cast<Uint16>(client->getRotationSpeed()), &data[12]);
    SDLNet_Write16(static_cast<Uint16>(client->getTurretRotationSpeed()), &data[14]);
    data[16] = client->getActHp();
}

Uint8 CurrentPositionPacket::getPlayerId() const { return data[1]; }
Uint16 CurrentPositionPacket::getX() const { return SDLNet_Read16(&data[2]); }
Uint16 CurrentPositionPacket::getY() const { return SDLNet_Read16(&data[4]); }
Uint16 CurrentPositionPacket::getTankRotation() const { return SDLNet_Read16(&data[6]); }
Uint16 CurrentPositionPacket::getTurretRotation() const { return SDLNet_Read16(&data[8]); }
Uint16 CurrentPositionPacket::getTankSpeed() const { return SDLNet_Read16(&data[10]); }
Uint16 CurrentPositionPacket::getRotationSpeed() const { return SDLNet_Read16(&data[12]); }
Uint16 CurrentPositionPacket::getTurretRotationSpeed() const { return SDLNet_Read16(&data[14]); }
Uint8 CurrentPositionPacket::getActualHp() const {return data[16];}

void CurrentPositionPacket::print() const
{
    std::cout << "CurrentPositionPacketReceived:ID: " << (int)getPlayerId()
              << " X: " << (int)getX()
              << " Y: " << (int)getY()
              << " TankRot: " << (int)getTankRotation()
              << " TurretRot: " << (int)getTurretRotation()
              << " TankSpeed: " << (int)getTankSpeed()
              << " RotationSpeed: " << (int)getRotationSpeed()
              << " TurretRotationSpeed: " << (int)getTurretRotationSpeed()
              << std::endl;
}

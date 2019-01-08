//
// Created by inql on 08.01.19.
//

#ifndef SERVERTANKSGAME_CURRENTPOSITIONPACKET_H
#define SERVERTANKSGAME_CURRENTPOSITIONPACKET_H

#include "Main.h"

//(packet type + playerId + x + y + tankrot + turretrot)
#define CURRENT_POSITION_PACKET_SIZE (1+1+2+2+2+2)

class CurrentPositionPacket : public BasePacket{
public:
    CurrentPositionPacket();
    void setPlayerId(Uint8 playerId);
    void setX(Uint16 x);
    void setY(Uint16 y);
    void setTankRotation(Uint16 tankRotation);
    void setTurretRotation(Uint16 turretRotation);

    Uint8 getPlayerId() const;
    Uint16 getX() const;
    Uint16 getY() const;
    Uint16 getTankRotation() const;
    Uint16 getTurretRotation() const;

    void print() const override;
};

#endif //SERVERTANKSGAME_CURRENTPOSITIONPACKET_H

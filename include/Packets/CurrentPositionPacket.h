//
// Created by inql on 08.01.19.
//

#ifndef SERVERTANKSGAME_CURRENTPOSITIONPACKET_H
#define SERVERTANKSGAME_CURRENTPOSITIONPACKET_H

#include "Main.h"

//(packet type + playerId + x + y + tankrot + turretrot)
#define CURRENT_POSITION_PACKET_SIZE (1+1+4+4+4+4)

class CurrentPositionPacket : public BasePacket{
public:
    CurrentPositionPacket();
    void setPlayerId(Uint8 playerId);
    void setX(Uint32 x);
    void setY(Uint32 y);
    void setTankRotation(Uint32 tankRotation);
    void setTurretRotation(Uint32 turretRotation);

    Uint8 getPlayerId() const;
    Uint32 getX() const;
    Uint32 getY() const;
    Uint32 getTankRotation() const;
    Uint32 getTurretRotation() const;

    void print() const override;
};

#endif //SERVERTANKSGAME_CURRENTPOSITIONPACKET_H

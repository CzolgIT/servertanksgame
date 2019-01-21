//
// Created by inql on 21.01.19.
//

#ifndef SERVERTANKSGAME_POWERUPPACKET_H
#define SERVERTANKSGAME_POWERUPPACKET_H

#include "Main.h"

#define POWERUP_PACKET_SIZE (1+1+1+1+2+2)



// data indexes explanation:
// data[0] -> packet type
// data[1] -> poweruptype
// data[2] -> show/destroy
// data[3] -> powerupid
// data[4-5] -> position x
// data[6-7] -> position y
class PowerUpPacket : public BasePacket{
public:

    PowerUpPacket();
    ~PowerUpPacket();
    void setPowerUpType(PowerUpType powerUpType);
    void setToShow(bool toShow);
    void setPowerUpId(Uint8 id);
    void setX(Uint16 x);
    void setY(Uint16 y);
    PowerUpType getPowerUpType();
    bool getToShow();
    Uint8 getPowerUpId();
    Uint16 getX();
    Uint16 getY();
    void setFromPowerUp(PowerUp* powerUp);
};

#endif //SERVERTANKSGAME_POWERUPPACKET_H

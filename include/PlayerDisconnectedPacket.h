//
// Created by inql on 15.11.18.
//

#ifndef SERVERTANKSGAME_PLAYERDISCONNECTEDPACKET_H
#define SERVERTANKSGAME_PLAYERDISCONNECTEDPACKET_H

#include "Main.h"

#define PLAYERDISCONNECTED_PACKET_SIZE (1+1)

class PlayerDisconnectedPacket : public BasePacket {

public:
    PlayerDisconnectedPacket();
    PlayerDisconnectedPacket(Uint8 id);
    ~PlayerDisconnectedPacket();

    void setId(Uint8 id);

    Uint8 getId() const;

    void print()const override;

};


#endif //SERVERTANKSGAME_PLAYERDISCONNECTEDPACKET_H

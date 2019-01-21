//
// Created by inql on 20.11.18.
//

#ifndef SERVERTANKSGAME_PLAYERJOINEDPACKET_H
#define SERVERTANKSGAME_PLAYERJOINEDPACKET_H

#include "Main.h"

#define PLAYERJOINED_PACKET_SIZE (1+1+10+8)

class PlayerJoinedPacket : public BasePacket {
public:
    PlayerJoinedPacket();
    ~PlayerJoinedPacket();

    void setId(Uint8 id);
    Uint8 getId();

    void setNickname(std::string nickname);
    std::string getNickname() const;

    void print()const override;
};


#endif //SERVERTANKSGAME_PLAYERJOINEDPACKET_H

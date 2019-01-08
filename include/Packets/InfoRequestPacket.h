//
// Created by inql on 07.01.19.
//

#ifndef SERVERTANKSGAME_INFOREQUESTPACKET_H
#define SERVERTANKSGAME_INFOREQUESTPACKET_H

#include "Main.h"

#define INFOREQUEST_PACKET_SIZE (1+1+1)

enum RequestType : Uint8{
    RT_MAP_DATA = 0,
    RT_PLAYER_LIST = 1
};

class InfoRequestPacket : public BasePacket{
public:
    InfoRequestPacket();
    InfoRequestPacket(Uint8 id, RequestType requestType);
    ~InfoRequestPacket();

    void setId(Uint8 id);
    void setRequested(RequestType type);

    Uint8 getId() const;
    RequestType getRequested() const;

    void print() const override;
};

#endif //SERVERTANKSGAME_INFOREQUESTPACKET_H

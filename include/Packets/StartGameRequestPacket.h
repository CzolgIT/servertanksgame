//
// Created by inql on 20.11.18.
//

#ifndef SERVERTANKSGAME_STARTGAMEREQUESTPACKET_H
#define SERVERTANKSGAME_STARTGAMEREQUESTPACKET_H

#include "Main.h"

#define STARTREQUEST_PACKET_SIZE (1+1+1)

class StartGameRequestPacket : public BasePacket {
public:
    StartGameRequestPacket();
    StartGameRequestPacket(Uint8 id, Uint8 roomId);
    ~StartGameRequestPacket();

    void setId(Uint8 id);
    void setRoomId(Uint8 roomId);

    Uint8 getId();
    Uint8 getRoomId();
private:
    Uint8 id;
    Uint8 roomId;

};


#endif //SERVERTANKSGAME_STARTGAMEREQUESTPACKET_H

//
// Created by inql on 18.11.18.
//

#ifndef SERVERTANKSGAME_SYNCPACKET_H
#define SERVERTANKSGAME_SYNCPACKET_H


#include "Main.h"

#define SYNC_PACKET_SIZE (1+1+1+4)

enum SyncMode : Uint8{
    SYNC_RETURN = 0,    //send the packet back immediately
    SYNC_SET = 1        //set the local time to the packets time
};

class SyncPacket : public BasePacket{
public:
    SyncPacket();
    ~SyncPacket();

    void setMode(SyncMode syncMode);
    void setId(Uint8 id);
    void setTime(Uint32 time);

    SyncMode getMode();
    Uint8 getId();
    Uint32 getTime();



};


#endif //SERVERTANKSGAME_SYNCPACKET_H

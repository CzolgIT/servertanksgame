
#ifndef EVENTPACKET_H
#define EVENTPACKET_H

#include "Main.h"

//(packettype+playerid+keyspressed+time)
#define EVENT_PACKET_SIZE (1+1+7+4)

class EventPacket : public BasePacket
{
public:

    EventPacket();
    void setId(Uint8 id);
    void setKeys(bool *keys);
    void setTime(Uint32 time);
    bool * getKeys();
    Uint8 getId();
    Uint32 getTime();
    ~EventPacket();

    void print() const override;

};


#endif //EVENTPACKET_H

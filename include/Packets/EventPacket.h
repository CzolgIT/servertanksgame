
#ifndef EVENTPACKET_H
#define EVENTPACKET_H

#include "Main.h"

#define EVENT_PACKET_SIZE (1+4)

class EventPacket : public BasePacket
{
public:

    EventPacket();
    void SetKeys(bool keys[4]);
    bool * GetKeys();
    ~EventPacket();

};


#endif //EVENTPACKET_H

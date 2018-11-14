#ifndef JOIN_RESPONSE_PACKET_H
#define JOIN_RESPONSE_PACKET_H

#include "Main.h"

#define JOIN_RESPONSE_PACKET_SIZE 3

enum JoinResponse : Uint8{
    JR_OK = 0,
    JR_REJECT = 1
};

// data indexes explanation:
// data[0] -> packet type
// data[1] -> response
// data[2] -> given id

class JoinResponsePacket : public BasePacket{
public:
    JoinResponsePacket() : BasePacket(PT_JOIN_RESPONSE, JOIN_RESPONSE_PACKET_SIZE) {}
    ~JoinResponsePacket() {}
    
    void SetResponse(JoinResponse joinResponse);
    void SetId(Uint8 id);

    JoinResponse GetResponse() const;
    Uint8 GetId() const ;
};

#endif

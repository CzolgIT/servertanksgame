//
// Created by inql on 18.11.18.
//

#ifndef SERVERTANKSGAME_UDPCONNECTION_H
#define SERVERTANKSGAME_UDPCONNECTION_H

#include "Main.h"

class UdpConnection {
public:
    UdpConnection();
    ~UdpConnection();
    void udpSendTo(Uint8 id, const BasePacket& packet,std::vector<std::unique_ptr<Client>> &clients);
    void udpSendAll(const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients);
    void udpSendAllExcept(Uint8 id, const BasePacket &packet,std::vector<std::unique_ptr<Client>> &clients);



};


#endif //SERVERTANKSGAME_UDPCONNECTION_H

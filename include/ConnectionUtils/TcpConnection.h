//
// Created by inql on 18.11.18.
//

#ifndef SERVERTANKSGAME_TCPCONNECTION_H
#define SERVERTANKSGAME_TCPCONNECTION_H

#include "Main.h"

class TcpConnection {
public:
    TcpConnection();
    ~TcpConnection();
    void tcpSendTo(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients);
    void tcpSendAll(const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients);
    void tcpSendAllExcept(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients);

private:
};


#endif //SERVERTANKSGAME_TCPCONNECTION_H

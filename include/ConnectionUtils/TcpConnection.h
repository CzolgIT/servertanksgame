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
    void tcp_send_to(Uint8 id, const BasePacket& packet,std::vector<std::unique_ptr<Client>>& clients);
    void tcp_send_all(const BasePacket& packet,std::vector<std::unique_ptr<Client>>& clients);
    void tcp_send_all_except(Uint8 id, const BasePacket& packet,std::vector<std::unique_ptr<Client>>& clients);

private:
};


#endif //SERVERTANKSGAME_TCPCONNECTION_H

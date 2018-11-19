//
// Created by inql on 18.11.18.
//

#include "Main.h"

void TcpConnection::tcp_send_to(Uint8 id, const BasePacket &packet,std::vector<std::unique_ptr<Client>>& clients) {

    for(auto& client : clients){
        if(client->getId() == id){
            client->tcpSend(packet);
            break;
        }
    }

}

void TcpConnection::tcp_send_all(const BasePacket &packet,std::vector<std::unique_ptr<Client>>& clients) {

    for(auto& client : clients){
        client->tcpSend(packet);
    }
}

void TcpConnection::tcp_send_all_except(Uint8 id, const BasePacket &packet,std::vector<std::unique_ptr<Client>>& clients) {

    for(auto& client : clients){
        if(client->getId() != id){
            client->tcpSend(packet);
        }
    }

}

TcpConnection::~TcpConnection() {

}

TcpConnection::TcpConnection() {
}

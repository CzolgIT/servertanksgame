//
// Created by inql on 18.11.18.
//

#include "Main.h"

void TcpConnection::tcpSendTo(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {

    for(auto& client : clients){
        if(client->getId() == id){
            client->tcpSend(packet);
            break;
        }
    }

}

void TcpConnection::tcpSendAll(const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {

    for(auto& client : clients){
        client->tcpSend(packet);
    }
}

void TcpConnection::tcpSendAllExcept(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {

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

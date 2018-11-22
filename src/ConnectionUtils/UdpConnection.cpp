//
// Created by inql on 18.11.18.
//
#include "Main.h"
void UdpConnection::udpSendTo(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {

    for(auto& client : clients){
        if(client->getId() == id){
            client->udpSend(packet);
            break;
        }
    }


}

void UdpConnection::udpSendAll(const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {
    for(auto& client : clients){
        client->udpSend(packet);
    }
}

void UdpConnection::udpSendAllExcept(Uint8 id, const BasePacket &packet, std::vector<std::unique_ptr<Client>> &clients) {
    for(auto& client : clients){
        if(client->getId()!= id){
            client->udpSend(packet);
        }
    }
}

//
// Created by inql on 20.11.18.
//

#include <Room.h>

#include "Main.h"

Room::Room() = default;

Room::~Room() = default;

void Room::setRoomId(Uint8 roomId) {
    this->roomId = roomId;
}

void Room::setHostId(Uint8 hostId) {
    this->hostId = hostId;
}

void Room::setMapId(Uint8 mapId) {
    this->mapId = mapId;
}

void Room::addClientToRoom(Client *client) {
    clients.push_back(std::unique_ptr<Client>(client));
}

Uint8 Room::getRoomId() {
    return this->roomId;
}

Uint8 Room::getHostId() {
    return this->hostId;
}

Uint8 Room::getMapId() {
    return this->mapId;
}

Client *Room::getClient(Uint8 id) {
    for(auto& client: clients)
    {
        if(client->getId()==id){
            return client.get();
        }
    }
    return nullptr;
}


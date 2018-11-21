//
// Created by inql on 20.11.18.
//

#ifndef SERVERTANKSGAME_ROOM_H
#define SERVERTANKSGAME_ROOM_H

#include "Main.h"

class Room {
public:
    Room();
    ~Room();

    void setRoomId(Uint8 roomId);
    void setHostId(Uint8 hostId);
    void setMapId(Uint8 mapId);
    void setMaxClients(int maxClients);

    void addClientToRoom(Client* client);

    int getMaxClients();
    Uint8 getRoomId();
    Uint8 getHostId();
    Uint8 getMapId();

    Client* getClient(Uint8 id);
private:

    std::vector<std::unique_ptr<Client>> clients;

    int maxClients;
    Uint8 roomId;
    Uint8 hostId;
    Uint8 mapId;

};


#endif //SERVERTANKSGAME_ROOM_H

//
// Created by inql on 07.01.19.
//

#ifndef SERVERTANKSGAME_MAPDATAPACKET_H
#define SERVERTANKSGAME_MAPDATAPACKET_H

#include "Main.h"

class MapDataPacket : public BasePacket
{
public:
    MapDataPacket(Uint8 mapWidth, Uint8 mapHeight);
    ~MapDataPacket();

    void setMapData(char * data);
    Uint8 getMapWidth() const;
    Uint8 getMapHeight() const;
    char * getMapData() const;

    void print() const override;
};


#endif //SERVERTANKSGAME_MAPDATAPACKET_H

//
// Created by inql on 07.01.19.
//

#ifndef SERVERTANKSGAME_MAPDATAPACKET_H
#define SERVERTANKSGAME_MAPDATAPACKET_H

#include "Main.h"
#define MAP_PACKET_SIZE (1 + 64 * 64)
class MapDataPacket : public BasePacket
{
public:
    MapDataPacket();
    ~MapDataPacket();

    void setMapData(char * data);
    int getMapWidth() const;
    int getMapHeight() const;
    char * getMapData() const;

    void print() const override;
};


#endif //SERVERTANKSGAME_MAPDATAPACKET_H

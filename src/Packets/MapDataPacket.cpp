//
// Created by inql on 07.01.19.
//
#include "Main.h"

MapDataPacket::MapDataPacket() : BasePacket(PT_MAP_INFO,MAP_PACKET_SIZE) {
}

MapDataPacket::~MapDataPacket() = default;

void MapDataPacket::setMapData(char *map) {
    memcpy(&data[1],map,getMapHeight()*getMapWidth());
}

int MapDataPacket::getMapWidth() const {
    return 32;
}

int MapDataPacket::getMapHeight() const {
    return 32;
}


char *MapDataPacket::getMapData() const {
    char * ret = new char[32 * 32];
    for (int i=1; i < 32 * 32+1; i++)
    {
        ret[i-1] = (char)data[i];
    }
    return ret;
}

void MapDataPacket::print() const {
    std::cout << "Got data " << getMapData() << std::endl;
}



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
    return 8;
}

int MapDataPacket::getMapHeight() const {
    return 8;
}


char *MapDataPacket::getMapData() const {
    return (char*)data[1];
}

void MapDataPacket::print() const {
    std::cout << "Got data " << getMapData() << std::endl;
}



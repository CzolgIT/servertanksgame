//
// Created by inql on 07.01.19.
//
#include "Main.h"

MapDataPacket::MapDataPacket(Uint8 mapWidth, Uint8 mapHeight) : BasePacket(PT_MAP_INFO,
                                                                           static_cast<unsigned int>(1 + 2 + mapHeight * mapWidth)) {

}

MapDataPacket::~MapDataPacket() = default;

void MapDataPacket::setMapData(char *data) {
    memcpy(&data[3],data,getMapHeight()*getMapWidth());
}

Uint8 MapDataPacket::getMapWidth() const {
    return data[2];
}

Uint8 MapDataPacket::getMapHeight() const {
    return data[3];
}

char *MapDataPacket::getMapData() const {
    return (char*)&data[3];
}

void MapDataPacket::print() const {
    std::cout << "Received map data of width" << getMapWidth() << " and height" << getMapHeight() << std::endl;
}



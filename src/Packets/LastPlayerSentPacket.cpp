//
// Created by inql on 09.01.19.
//
#include "Main.h"
LastPlayerSentPacket::LastPlayerSentPacket():BasePacket(PT_LAST_PLAYER_SENT,LAST_PLAYER_SENT_SIZE) {

}

LastPlayerSentPacket::~LastPlayerSentPacket() = default;


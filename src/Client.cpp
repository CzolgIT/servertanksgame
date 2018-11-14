#include "Main.h"

Client::Client(Uint8 ID, UDPsocket udpsock):
udpSocket(udpsock),
id(ID)
{
}
Client::~Client()
{
    //TODO: delete sockets & cleanup
}

void Client::UDPSend( const BasePacket& packet){

    udpPacket.data = packet.GetData();
    udpPacket.len = packet.GetSize();
    udpPacket.maxlen = packet.GetSize();
    
    SDLNet_UDP_Send(udpSocket,-1,&udpPacket);
}

void Client::SetUDPAddress( IPaddress address){

    udpPacket.address = address;
}

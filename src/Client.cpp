#include "Main.h"

Client::Client(Uint8 ID,TCPsocket tcpsock, UDPsocket udpsock):
tcpSocket(tcpsock),
udpSocket(udpsock),
id(ID)
{
}
Client::~Client()
{

    SDLNet_TCP_DelSocket(*SockSet,tcpSocket);

    SDLNet_TCP_Close(tcpSocket);

}



void Client::UDPSend( const BasePacket& packet){

    if(!hasUDPAddress)
        return;

    udpPacket.data = packet.GetData();
    udpPacket.len = packet.GetSize();
    udpPacket.maxlen = packet.GetSize();
    
    SDLNet_UDP_Send(udpSocket,-1,&udpPacket);
}

void Client::SetUDPAddress( IPaddress address){

    udpPacket.address = address;

    hasUDPAddress = true;
}

void Client::TCPSend(const BasePacket &packet) {

    SDLNet_TCP_Send(tcpSocket,packet.GetData(),packet.GetSize());

}

void Client::AttachSocketSet(SDLNet_SocketSet *socketSet) {
    SockSet = socketSet;

}

void Client::SetPosition(SDL_Point newPosition) {
    position = newPosition;
}

TCPsocket Client::GetTCPSocket() {
    return tcpSocket;
}

Uint8 Client::GetID() {
    return id;
}

SDL_Point Client::GetPosition() {
    return position;
}

bool Client::NeedsUDPAddress() {
    return !hasUDPAddress;
}

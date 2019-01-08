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



void Client::udpSend(const BasePacket &packet){

    if(!hasUDPAddress)
        return;

    udpPacket.data = packet.getData();
    udpPacket.len = packet.getSize();
    udpPacket.maxlen = packet.getSize();
    
    SDLNet_UDP_Send(udpSocket,-1,&udpPacket);
}

void Client::setUdpAddress(IPaddress address){

    udpPacket.address = address;

    hasUDPAddress = true;
}

void Client::tcpSend(const BasePacket &packet) {

    SDLNet_TCP_Send(tcpSocket, packet.getData(), packet.getSize());

}

void Client::attachSocketSet(SDLNet_SocketSet *socketSet) {
    SockSet = socketSet;

}

void Client::setPosition(SDL_Point newPosition) {
    position = newPosition;
}

TCPsocket Client::getTcpSocket() {
    return tcpSocket;
}

Uint8 Client::getId() {
    return id;
}

SDL_Point Client::getPosition() {
    return position;
}

bool Client::needsUdpAddress() {
    return !hasUDPAddress;
}

void Client::setIDirection(int iDirection) {
    this->iDirection = iDirection;
}

void Client::setITowerDirection(int iTowerDirection) {
    this->iTowerDirection = iTowerDirection;
}

int Client::getIDirection() {
    return this->iDirection;
}

int Client::getITowerDirection() {
    return this->iTowerDirection;
}

void Client::print() {
    std::cout << "Player info:|ID:" << (int)getId() << "|Position:(" << getPosition().x << "," << getPosition().y << ")|" << "iDirection:" << getIDirection() << "iTowerDirection" << getITowerDirection() << std::endl;
}

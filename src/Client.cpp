#include "Client.h"

Client::Client(Uint8 ID, UDPsocket udpsock):
UDPsocket_(udpsock),
ID_(ID)
{
}
Client::~Client()
{
    //TODO: delete sockets & cleanup
}

void Client::UDPSend( const BasePacket& packet){

    UDPpacket_.data = packet.GetData();
    UDPpacket_.len = packet.GetSize();
    UDPpacket_.maxlen = packet.GetSize();
    
    SDLNet_UDP_Send(UDPsocket_,-1,&UDPpacket_);
}

void Client::SetUDPAddress( IPaddress address){

    UDPpacket_.address = address;
}

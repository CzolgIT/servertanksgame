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
    std::cout << "Player       position: [ " << position.x << " , " << position.y << " ]\n"
            "ID: " << int(getId()) <<"      directions: [ "<< iDirection << " , " << iTowerDirection << " ]\n"
            "             keyboard: [ "
            << ( keys[0] ? "^" : " " ) << " , "
            << ( keys[1] ? "v" : " " ) << " , "
            << ( keys[2] ? "<" : " " ) << " , "
            << ( keys[3] ? ">" : " " ) << " , "
            << ( keys[4] ? "Z" : " " ) << " , "
            << ( keys[5] ? "X" : " " ) << " , "
            << ( keys[6] ? "_" : " " ) << " ]\n"
            << "            reloading: " << shootLoading << "\n"
            << "-----------------------------------------------------------\n";

}

void Client::setKeys(int x,bool keys)
{
    this->keys[x] = keys;
}

bool Client::getKeys(int i)
{
    return keys[i];
}

float Client::getX() const {
    return x;
}

void Client::setX(float x) {
    Client::x = x;
}

float Client::getY() const {
    return y;
}

void Client::setY(float y) {
    Client::y = y;
}

float Client::getTankDirection() const {
    return tankDirection;
}

void Client::setTankDirection(float tankDirection) {
    Client::tankDirection = tankDirection;
}

float Client::getTowerDirection() const {
    return towerDirection;
}

void Client::setTowerDirection(float towerDirection) {
    Client::towerDirection = towerDirection;
}

void Client::move( float timeStep )
{
    moveSpeed = accelerate(keys[0] , moveSpeed , 0 , TANKMAXSPEED , timeStep );
    moveSpeed = accelerate(keys[1] , moveSpeed , 0 , -TANKMAXSPEED , timeStep );
    directionSpeed = accelerate(keys[3] , directionSpeed , 0 , TANKMAXDIR , timeStep );
    directionSpeed = accelerate(keys[2] , directionSpeed , 0 , -TANKMAXDIR , timeStep );
    towerSpeed = accelerate(keys[5] , towerSpeed , 0 , TANKMAXDIR , timeStep );
    towerSpeed = accelerate(keys[4] , towerSpeed , 0 , -TANKMAXDIR , timeStep );

    double xm = cos((iDirection) *M_PI/180) * moveSpeed * timeStep;
    double ym = sin((iDirection) *M_PI/180) * moveSpeed * timeStep;

    x += xm; //-blocked.x;
    y += ym; //-blocked.y;

    position.x = int(x);
    position.y = int(y);

    tankDirection += directionSpeed * timeStep ;
    towerDirection += directionSpeed * timeStep + towerSpeed * timeStep;

    if ( tankDirection > 360 ) tankDirection -= 360;
    if ( towerDirection > 360 ) towerDirection -= 360;

    if ( tankDirection < 0 ) tankDirection += 360;
    if ( towerDirection < 0 ) towerDirection += 360;

    iDirection = int(tankDirection);
    iTowerDirection = int(towerDirection);

    // SZCZELANIE

    if (!readyToShoot)
    {
        shootLoading += timeStep;
        if ( shootLoading >=1 )
        {
            readyToShoot=true;
            shootLoading=0;
        }
    }

    if (keys[6] && readyToShoot)
    {
        readyToShoot=false;
        Bullet * bullet = new Bullet(shootPosition(),towerDirection);
        bullets->push_back(bullet);

        // todo: DAWID BINKUS WEZ TO WYSLIJ
        //UdpConnection::udpSendAll( )
    }


}

float Client::accelerate(bool isPressed, float what , float from , float to , float timeStep )
{

    if (isPressed)
    {
        if ( from < to ? what < to : what > to )
        {
            what += to * timeStep * TANKACCELERATION ;
            if ( from < to ? what > to : what < to ) what = to;
        }
    }
    else
    {
        if ( from < to ? what > from : what < from )
        {
            what -= to * timeStep * TANKACCELERATION;
            if ( from < to ? what < from : what > from ) what = from;
        }
    }
    return what;
}

SDL_Point Client::shootPosition()
{
    SDL_Point punkt;
    punkt.x = (int)(position.x+(cos(double(iTowerDirection) *M_PI/180) * 60));
    punkt.y = (int)(position.y+(sin(double(iTowerDirection) *M_PI/180) * 60));
    return punkt;
}

void Client::setBulletsPointer( std::vector<Bullet *> *bullets )
{
    this->bullets = bullets;
}

void Client::setClientsPointer( std::vector<std::unique_ptr<Client>> *clients )
{
    this->clients = clients;
}
#include "Main.h"

Client::Client(Uint8 ID,TCPsocket tcpsock, UDPsocket udpsock) :
tcpSocket(tcpsock),
udpSocket(udpsock),
id(ID)
{
    this->collider = new Collider(x,y,85,65,iDirection);
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
    std::cout << "Player (" << int(getId()) << ")   position: [ " << position.x << " , " << position.y << " ]\n"
              <<"             directions: [ "<< iDirection << " , " << iTowerDirection << " ]\n"
              <<"                speed: [ " << int(tankSpeed) << " , " << int(rotationSpeed) << " , " << int(turretRotationSpeed) << " ]\n"
              <<"             keyboard: [ "
                << ( keys[0] ? "^" : " " ) << " , "
                << ( keys[1] ? "v" : " " ) << " , "
                << ( keys[2] ? "<" : " " ) << " , "
                << ( keys[3] ? ">" : " " ) << " , "
                << ( keys[4] ? "Z" : " " ) << " , "
                << ( keys[5] ? "X" : " " ) << " , "
                << ( keys[6] ? "_" : " " ) << " ]\n"
              << "            reloading: " << shootLoading << "\n"
              << "             nickname: " << nickname << "\n"
              << "            readyness: " << isPlayerReady << "\n"
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
        tankSpeed = accelerate(keys[0] , tankSpeed , 0 , TANKMAXSPEED , timeStep );
        tankSpeed = accelerate(keys[1] , tankSpeed , 0 , -TANKMAXSPEED , timeStep );
        rotationSpeed = accelerate(keys[3] , rotationSpeed , 0 , TANKMAXDIR , timeStep );
        rotationSpeed = accelerate(keys[2] , rotationSpeed , 0 , -TANKMAXDIR , timeStep );
        turretRotationSpeed = accelerate(keys[5] , turretRotationSpeed , 0 , TANKMAXDIR , timeStep );
        turretRotationSpeed = accelerate(keys[4] , turretRotationSpeed , 0 , -TANKMAXDIR , timeStep );

        double xm = cos((iDirection) *M_PI/180) * tankSpeed * timeStep;
        double ym = sin((iDirection) *M_PI/180) * tankSpeed * timeStep;


        x += xm; //-blocked.x;
        y += ym; //-blocked.y;

//    if (x<50)   x=50;
//    if (x>4046) x=4046;
//    if (y<50)   y=50;
//    if (y>4046) y=4046;

        position.x = int(x);
        position.y = int(y);

        tankDirection += rotationSpeed * timeStep ;
        towerDirection += rotationSpeed * timeStep + turretRotationSpeed * timeStep;

        if ( tankDirection > 360 ) tankDirection -= 360;
        if ( towerDirection > 360 ) towerDirection -= 360;

        if ( tankDirection < 0 ) tankDirection += 360;
        if ( towerDirection < 0 ) towerDirection += 360;

        iDirection = int(tankDirection);
        iTowerDirection = int(towerDirection);

        collider->update(x,y,85,65,iDirection);

        // SZCZELANIE

        if (!readyToShoot) {
            shootLoading += timeStep;
            if (shootLoading >= 1) {
                readyToShoot = true;
                shootLoading = 0;
            }
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
    punkt.x = (int)(position.x+(cos(double(iTowerDirection) *M_PI/180) * 70));
    punkt.y = (int)(position.y+(sin(double(iTowerDirection) *M_PI/180) * 70));
    return punkt;
}

void Client::setBulletsPointer( std::vector<Bullet *> *bullets )
{
    this->bullets = bullets;
}

int Client::getTankSpeed()
{
    return int(tankSpeed);
}

void Client::setTankSpeed(int tankSpeed)
{
    this->tankSpeed = tankSpeed;
}

int Client::getRotationSpeed()
{
    return int(rotationSpeed);
}

int Client::getTurretRotationSpeed()
{
    return int(turretRotationSpeed);
}

void Client::setNickname(std::string nickname)
{
    this->nickname = nickname;
}

std::string Client::getNickname()
{
    return nickname;
}

Uint8 Client::getActHp() const
{
    return uint8_t(actHp);
}

void Client::setActHp(Uint8 actHp)
{
    this->actHp = actHp;
}

void Client::doDamage(int damage)
{
    if (this->actHp > 0)
        this->actHp -= damage;
}

Collider* Client::getCollider()
{
    return collider;
}

bool Client::isReadyToShoot()
{
    return readyToShoot;
}

void Client::setUnableToShoot()
{
    this->readyToShoot=false;
}

bool Client::isIsPlayerReady() const {
    return isPlayerReady;
}

void Client::setIsPlayerReady(bool isPlayerReady) {
    Client::isPlayerReady = isPlayerReady;
}

int Client::getScore() const {
    return score;
}

void Client::setScore(int score) {
    Client::score = score;
}

int Client::getDeaths() const {
    return deaths;
}

void Client::setDeaths(int deaths) {
    Client::deaths = deaths;
}

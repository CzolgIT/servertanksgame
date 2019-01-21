#include "Main.h"

NetManager::NetManager()
{
    std::cout << "Starting TANKS server..."<< std::endl;
    SDL_Log("Server IP: %s",SERVERIP);

    if(SDLNet_Init() == -1){

        std::cout << "SDL_Init %s\n" << SDL_GetError() << std::endl;
        exit(2);
    }

    if( SDLNet_ResolveHost( &address, nullptr, SERVERPORT ) == -1 ) {
		printf( "SDLNet_ResolveHost: %s\n", SDLNet_GetError( ) );
		exit( 3 );
    }

    TCP_socket = SDLNet_TCP_Open(&address);
    if(!TCP_socket){

        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(4);

    }

    if( !(UDP_socket = SDLNet_UDP_Open( SERVERPORT )) ){
		fprintf( stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError( ) );
		exit( 5 );
	}

    std::cout << "Server listening on port: " << SERVERPORT << std::endl;

    UDP_packet.data = universalPacket.getData();
    UDP_packet.maxlen = universalPacket.getSize();

    //Allocate the socket set
    TCP_SocketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
    if (TCP_SocketSet == nullptr)
    {
        fprintf(stderr, "SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
        exit(6);
    }

    SDLNet_TCP_AddSocket(TCP_SocketSet,TCP_socket);
    SDLNet_CheckSockets(TCP_SocketSet,0);

    timer = new Timer();

    engineManager = new EngineManager( &clients , &bullets , &powerUps );
}


NetManager::~NetManager()
{
    SDLNet_FreeSocketSet( TCP_SocketSet );
	SDLNet_Quit();
	SDL_Quit();

}

void NetManager::acceptClient()
{
        TCPsocket new_socket;

    //try to accept a new connection
    // if there was no connection accept return null
    if(SDLNet_SocketReady(TCP_socket)){

        new_socket = SDLNet_TCP_Accept(TCP_socket);

    }
    else return;

    if(new_socket != nullptr)
    {
        JoinRequestPacket joinRequestPacket;

        if(SDLNet_TCP_Recv(new_socket, joinRequestPacket.getData(), joinRequestPacket.getSize()) <=0)
        {
            std::cout << "error\n";
            return;
        }
        if(clients.size() < MAX_CLIENTS)
        {
            JoinResponsePacket joinResponsePacket;
            joinResponsePacket.setResponse(JR_OK);
            joinResponsePacket.setId(getAvailableId());
            if (SDLNet_TCP_Send(new_socket, joinResponsePacket.getData(), joinResponsePacket.getSize()) < (int) joinResponsePacket.getSize()){

                std::cout << "error x2\n";
                return;

            }

            auto * acceptedClient = new Client(joinResponsePacket.getId(),new_socket,UDP_socket);

            clients.push_back(std::unique_ptr<Client>(acceptedClient));

            acceptedClient->setBulletsPointer( &bullets );

            SDLNet_TCP_AddSocket(TCP_SocketSet, clients.back()->getTcpSocket());
            SDLNet_CheckSockets(TCP_SocketSet,0);


            clients.back()->attachSocketSet(&TCP_SocketSet);
            clients.back()->setNickname(joinRequestPacket.getNickname());
            clients.back()->setIsPlayerReady(false);

            std::cout << "Client joined with ID: " << (int) clients.back()->getId() << " and nickname: "<< clients.back()->getNickname() << std::endl;

            //sending packet to another players
            PlayerJoinedPacket playerJoinedPacket;
            playerJoinedPacket.setId(clients.back()->getId());
            playerJoinedPacket.setNickname(clients.back()->getNickname());
            TcpConnection::tcpSendAllExcept(clients.back()->getId(),playerJoinedPacket,clients);
            //sending already joined players
            Uint8 requesterId = clients.back()->getId();
            for (auto &client : clients) {
                PlayerJoinedPacket currentPlayer;
                if(client->getId()!=requesterId){
                    currentPlayer.setId(client->getId());
                    currentPlayer.setNickname(client->getNickname());
                    getClient(requesterId)->tcpSend(currentPlayer);
                    currentPlayer.print();
                }
            }
        }
        else
        {

            JoinResponsePacket joinResponsePacket;
            joinResponsePacket.setResponse(JR_REJECT);

            if (SDLNet_TCP_Send(new_socket, joinResponsePacket.getData(), joinResponsePacket.getSize()) < (int) joinResponsePacket.getSize()){

                std::cout << "error x2\n";
                return;

            }

        }



    }
}


void NetManager::update( int argc )
{
    bool quit = false;

    while(!quit){

        // Check if any sockets are ready
        SDLNet_CheckSockets(TCP_SocketSet,0);

        acceptClient();
        processTcp();
        processUdp();

        engineManager->move(timer->getStepTime());
        engineManager->checkColliders();

        if (argc > 1)
            monitoring();

        timer->update();
    }
}

Uint8 NetManager::getAvailableId() {
    Uint8 id = 1;

    while(getClient(id))
    {
        id++;
        if(id == 0)
            return id;
    }
    return id;




}

Client *NetManager::getClient(Uint8 id) {
    for(auto& client: clients)
    {
        if(client->getId()==id){
            return client.get();
        }
    }
    return nullptr;
}

bool NetManager::disconnectClient(Uint8 id) {

    bool foundClient = false;
    for(auto it = clients.begin(); it != clients.end(); it++){
        if((*it)->getId()==id){
            clients.erase(it);
            foundClient = true;
            break;
        }
    }

    if(foundClient){
        PlayerDisconnectedPacket playerDisconnectedPacket(id);
        TcpConnection::tcpSendAll(playerDisconnectedPacket, clients);
    }

    return foundClient;

}

void NetManager::processTcp() {

    if(!clients.empty()){

        for(auto client = clients.begin(); client!=clients.end();){
            if(SDLNet_SocketReady((*client)->getTcpSocket())){
                //receive data directly into the universal packet
                if(SDLNet_TCP_Recv((*client)->getTcpSocket(),universalPacket.getData(), universalPacket.getSize())>0){
                    std::unique_ptr<BasePacket> recvd = universalPacket.createFromContents();

                    if(recvd)
                    {
                        if(recvd->getType() == PT_PLAYER_DISCONNECTED){
                            auto * packet = (PlayerDisconnectedPacket*)recvd.get();
                            disconnectClient(packet->getId());
                        }
                        else if(recvd->getType() == PT_INFO_REQUEST){
                            recvd->print();
                            auto * infoRequestPacket = (InfoRequestPacket*)recvd.get();
                            if(infoRequestPacket->getRequested() == RT_MAP_DATA)
                            {
                                MapDataPacket mapDataPacket;
                                char * map = new char[64 * 64];
                                Map::getMapFromFile(map);
                                mapDataPacket.setMapData(map);
                                (*client)->tcpSend(mapDataPacket);
                            }
                        }
                        else if(recvd->getType() == PT_PLAYER_READY){
                            auto * packet = (PlayerReadyPacket*)recvd.get();
                            Client * pClient = getClient(packet->getId());
                            pClient->setIsPlayerReady(true);
                            pClient->setActHp(100);
                            pClient->removePowerUps();
                            //spawn a player
                            SDL_Point spawnPoint = getSpawnPoint();
                            pClient->setX(spawnPoint.x);
                            pClient->setY(spawnPoint.y);
                            //send all powerups on the map
                            for (auto &powerup : powerUps){
                                PowerUpPacket powerUpPacket;
                                powerUpPacket.setFromPowerUp(powerup);
                                powerUpPacket.setToShow(true);
                                pClient->udpSend(powerUpPacket);
                            }
                            return;
                        }
                    }
                }
            }
            else{
                client++;
            }



        }


    }

}

void NetManager::processUdp()
{

    // receive all pending udp packets
    while(SDLNet_UDP_Recv(UDP_socket, &UDP_packet))
    {
        auto recvd = universalPacket.createFromContents();

        if(recvd){

            //here will be all possibilities of received packets

            switch (recvd->getType()){
                case PT_HEARTBEAT:
                {
                    auto * heartbeatPacket = (HeartbeatPacket*)recvd.get();
                    //recvd->print();
                    Client* sender = getClient(heartbeatPacket->getId());
                    if(sender){
                        sender->setUdpAddress(UDP_packet.address);
                    }
                    //send the server time to client
                    SyncPacket syncPacket;
                    syncPacket.setMode(SYNC_RETURN);
                    syncPacket.setId(heartbeatPacket->getId());
                    syncPacket.setTime(SDL_GetTicks());
                    sender->udpSend(syncPacket);
                    break;
                }

                case PT_SYNC:
                {
                    auto * syncPacket = (SyncPacket*)recvd.get();

                    if(syncPacket->getMode() == SYNC_RETURN){
                        Uint32 sendTime = (SDL_GetTicks()-syncPacket->getTime())/2;
                        SyncPacket responseSyncPacket;
                        responseSyncPacket.setMode(SYNC_SET);
                        responseSyncPacket.setId(syncPacket->getId());
                        Client* sender = getClient(syncPacket->getId());
                        responseSyncPacket.setTime(SDL_GetTicks()+sendTime);
                        if(sender){
                            sender->udpSend(responseSyncPacket);
                        }
                        else{
                            std::cout << "An unknown client tried to sync" << std::endl;
                        }
                    }
                    break;
                }
                case PT_EVENT:
                {
                    auto * eventPacket = (EventPacket*)recvd.get();
                    Client* sender = getClient(eventPacket->getId());
                    if(sender!= nullptr) {
                        for (int i = 0; i < 7; i++) {
                            sender->setKeys(i, eventPacket->getKeys(i));
                        }
                    }
                }
                break;
                default:
                {
                    recvd->print();
                    std::cout<< "UDP packet type not recognised" << std::endl;
                }
                break;
            }
        }
    }
}

SDL_Point NetManager::getSpawnPoint()
{
    float sum = 1;
    while(sum != 0)
    {
        auto* spawn = Map::getSpawnPoints()[random()%int(Map::getSpawnPoints().size())];
        sum=0;
        for (auto &other: clients)
        {
            Collider *col1 = other->getCollider();
            Vector2D col = Collider::areColliding(col1, spawn);

            if (col.x != 0 || col.y != 0)
            {
                sum+=abs(col.x);
                sum+=abs(col.y);
            }
        }
        for (auto &powerUp: powerUps)
        {
            Collider *col1 = powerUp->getCollider();
            Vector2D col = Collider::areColliding(col1, spawn);

            if (col.x != 0 || col.y != 0)
            {
                sum+=abs(col.x);
                sum+=abs(col.y);
            }
        }
        if (sum == 0)
        {
            return { int(spawn->center->x) , int(spawn->center->y) };
        }
    }
    return {0,0};
}


void NetManager::monitoring()
{
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Server            fps: " << timer->getFps() << "     IP: " << SERVERIP << " : " << SERVERPORT << "   powerups: " << powerUps.size() << "\n";
    std::cout << "-----------------------------------------------------------\n";
    for (auto &client : clients) client->print();

    for(auto* bullet : bullets )
    {
        bullet->print();
        std::cout << "-----------------------------------------------------------\n";
    }

}
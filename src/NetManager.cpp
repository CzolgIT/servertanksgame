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

    engineManager = new EngineManager( &clients , &bullets );
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
            //if you are first player
            if(clients.size()==1){
                joinResponsePacket.setIsHost(true);
            }
            if (SDLNet_TCP_Send(new_socket, joinResponsePacket.getData(), joinResponsePacket.getSize()) < (int) joinResponsePacket.getSize()){

                std::cout << "error x2\n";
                return;

            }

            Client * klient = new Client(joinResponsePacket.getId(),new_socket,UDP_socket);

            clients.push_back(std::unique_ptr<Client>(klient));

            klient->setBulletsPointer( &bullets );

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

            for (auto &spawn: Map::getSpawnPoints())
            {
                float sum = 0;
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
                if (sum == 0)
                {
                    clients.back()->setX(spawn->center->x);
                    clients.back()->setY(spawn->center->y);
                    return;
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
        //int numready =
        SDLNet_CheckSockets(TCP_SocketSet,0);

        acceptClient();
        processTcp();
        processUdp();

        engineManager->move(timer->getStepTime());
        engineManager->checkColliders();

        if (argc > 1)
            monitoring();

        SDL_Delay(10);
        timer->update();
    }
}

Uint8 NetManager::getAvailableId() {
    //todo: randomize id bo andrzej tak chce xd
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
    std::cout << "Before: " << clients.size() << std::endl;
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
        std::cout << "After: " << clients.size() << std::endl;
        //if only one player stays in the room, give him the host role
//        tutaj sprawdzic debilu
//        czy vector nie jest pusty XDDD
//        this->setHostId(clients.back()->getId());
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
//                        recvd->print();

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
                                char * map = new char[32 * 32];
                                Map::getMapFromFile(map);
                                std::cout << map <<  std::endl;
                                mapDataPacket.setMapData(map);
                                (*client)->tcpSend(mapDataPacket);
                                std::cout << "Map send " << std::endl;
                            }
                            else if(infoRequestPacket->getRequested() == RT_PLAYER_LIST){
                                //send player joined packets with players id
//                                Uint8 requesterId = infoRequestPacket->getId();
//                                for(size_t i = 0; i<clients.size(); i++){
//                                    PlayerJoinedPacket currentPlayer;
//                                    if(clients[i]->getId()!=requesterId){
//                                        currentPlayer.setId(clients[i]->getId());
//                                        getClient(requesterId)->tcpSend(currentPlayer);
//                                        currentPlayer.print();
//                                    }
//                                }
//                                LastPlayerSentPacket lastPlayerSentPacket;
//                                getClient(requesterId)->tcpSend(lastPlayerSentPacket);
                            }

                        }
                        else if(recvd->getType() == PT_PLAYER_READY){
                            auto * packet = (PlayerReadyPacket*)recvd.get();
                            std::cout << "pakiet o gotowości od gracza: "<< (int)packet->getId() << std::endl;
                            getClient(packet->getId())->setIsPlayerReady(true);
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
//temporary disabled - we will operate on one room only so who Room class is useless
void NetManager::createRoom(Uint8 hostId, int maxClients) {
    rooms.push_back(std::unique_ptr<Room>(new Room()));

    rooms.back()->setRoomId(getAvailableRoomId());
    rooms.back()->setMaxClients(maxClients);
    rooms.back()->setHostId(hostId);
}

void NetManager::deleteRoom(Uint8 id) {
    bool foundRoom = false;
    std::cout << "Before: " << rooms.size() << std::endl;
    for(auto it = rooms.begin(); it != rooms.end(); it++){
        if((*it)->getRoomId()==id){
            rooms.erase(it);
            foundRoom = true;
            break;
        }
    }

    if(foundRoom){
        //todo: send packet about destroying a room (optional!)
        std::cout << "After: " << clients.size() << std::endl;
    }
}

Room *NetManager::getRoom(Uint8 id) {
    for(auto& room: rooms)
    {
        if(room->getRoomId()==id){
            return room.get();
        }
    }
    return nullptr;
}

Uint8 NetManager::getAvailableRoomId() {
    Uint8 id = 1;

    while(getRoom(id))
    {
        id++;
        if(id == 0)
            return id;
    }
    return id;
}

//---------------------------------------------

void NetManager::processUdp()
{

    // receive all pending udp packets
    while(SDLNet_UDP_Recv(UDP_socket, &UDP_packet))
    {
        auto recvd = universalPacket.createFromContents();

        if(recvd){

            //recvd->print();
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

Uint8 NetManager::getHostId() {
    return this->hostId;
}

void NetManager::setHostId(Uint8 hostId) {
    this->hostId = hostId;
}

void NetManager::setMapId(Uint8 mapId) {
    this->mapId = mapId;
}

Uint8 NetManager::getMapId() {
    return this->mapId;
}

void NetManager::monitoring()
{
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Server            fps: " << timer->getFps() << "     IP: " << SERVERIP << " : " << SERVERPORT << "\n";
    std::cout << "-----------------------------------------------------------\n";
    for (auto &client : clients) client->print();

    for(auto* bullet : bullets )
    {
        bullet->print();
        std::cout << "-----------------------------------------------------------\n";
    }

}
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

            clients.push_back(std::unique_ptr<Client>(new Client(joinResponsePacket.getId(),new_socket,UDP_socket)));

            SDLNet_TCP_AddSocket(TCP_SocketSet, clients.back()->getTcpSocket());
            SDLNet_CheckSockets(TCP_SocketSet,0);
            clients.back()->attachSocketSet(&TCP_SocketSet);

            std::cout << "Client joined with ID: " << (int) clients.back()->getId() << std::endl;


            
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


void NetManager::update()
{
        bool quit = false;

    while(!quit){
    
        // Check if any sockets are ready
        int numready = SDLNet_CheckSockets(TCP_SocketSet,0);
        acceptClient();
        processTcp();
        processUdp();
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
                        recvd->print();

                        if(recvd->getType() == PT_PLAYER_DISCONNECTED){
                            auto * packet = (PlayerDisconnectedPacket*)recvd.get();
                            disconnectClient(packet->getId());
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

void NetManager::processUdp() {

    // receive all pending udp packets
    while(SDLNet_UDP_Recv(UDP_socket, &UDP_packet))
    {
        auto recvd = universalPacket.createFromContents();

        if(recvd){

            recvd->print();
            //here will be all possibilities of received packets

            switch (recvd->getType()){
                case PT_HEARTBEAT:
                {
                    auto * heartbeatPacket = (HeartbeatPacket*)recvd.get();
                    recvd->print();
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
                default:
                {
                    recvd->print();
                    std::cout<< "UDP packet type not recognised" << std::endl;
                }
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


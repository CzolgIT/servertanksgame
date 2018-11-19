#include "Main.h"

NetManager::NetManager()
{

    tcpConnection = TcpConnection();

    std::cout << "Starting TANKS server..."<< std::endl;
    SDL_Log("Server IP: %s",SERVERIP);
    
    if(SDLNet_Init() == -1){
        
        std::cout << "SDL_Init %s\n" << SDL_GetError() << std::endl;
        exit(2);
    }
    
    if( SDLNet_ResolveHost( &address, NULL, SERVERPORT ) == -1 ) {
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
    
    //Allocate the socket set
    TCP_SocketSet = SDLNet_AllocSocketSet(MAX_CLIENTS+1);
    if (TCP_SocketSet == NULL)
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
    
    if(new_socket !=NULL)
    {
        std::cout << "lol" << std::endl;
        SDL_Log("Connected to client %s:%i", SDLNet_ResolveIP(&address), SDLNet_Read16(&address.port));
        std::cout << "XD" << clients.size() << std::endl;

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
            //todo: add new player and do some stuff

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
        SDLNet_CheckSockets(TCP_SocketSet,0);
        acceptClient();
        processTcp();
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

void NetManager::disconnectClient(Uint8 id) {

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
        tcpConnection.tcp_send_all(playerDisconnectedPacket,clients);
    }

}

void NetManager::processTcp() {

    if(clients.size() > 0){

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



        }


    }

}


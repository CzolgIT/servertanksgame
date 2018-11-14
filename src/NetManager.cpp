
#include <NetManager.h>

#include "Main.h"

NetManager::NetManager()
{
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

void NetManager::AcceptClient()
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
        
        SDL_Log("Connected to client %s:%i", SDLNet_ResolveIP(&address), SDLNet_Read16(&address.port));
        
        JoinRequestPacket joinRequestPacket;
        
        if(SDLNet_TCP_Recv(new_socket, joinRequestPacket.GetData(), joinRequestPacket.GetSize()) <=0)
        {
            std::cout << "zjebalo sie\n";
            return;
        }
        std::cout << clients.size() << std::endl;
        if(clients.size() < MAX_CLIENTS)
        {
            
            JoinResponsePacket joinResponsePacket;
            joinResponsePacket.SetResponse(JR_OK);
            joinResponsePacket.SetId(getAvailableId());
            if (SDLNet_TCP_Send(new_socket, joinResponsePacket.GetData(), joinResponsePacket.GetSize()) < (int) joinResponsePacket.GetSize()){
            
                std::cout << "zjebalo sie x2\n";
                return;
                
            }
            //todo: add new player and do some stuff

            clients.push_back(std::unique_ptr<Client>(new Client(joinResponsePacket.GetId(),new_socket,UDP_socket)));

            SDLNet_TCP_AddSocket(TCP_SocketSet,clients.back()->GetTCPSocket());
            SDLNet_CheckSockets(TCP_SocketSet,0);
            clients.back()->AttachSocketSet(&TCP_SocketSet);

            std::cout << "Client joined with ID: " << (int)clients.back()->GetID() << std::endl;


            
        }
        else
        {
            
            JoinResponsePacket joinResponsePacket;
            joinResponsePacket.SetResponse(JR_REJECT);
            
            if (SDLNet_TCP_Send(new_socket, joinResponsePacket.GetData(), joinResponsePacket.GetSize()) < (int) joinResponsePacket.GetSize()){
            
                std::cout << "zjebalo sie x2\n";
                return;
                
            }
            
        }
        
        
        
    }
}


void NetManager::Update()
{
        bool quit = false;

    while(!quit){
    
        // Check if any sockets are ready
        SDLNet_CheckSockets(TCP_SocketSet,0);
        AcceptClient();
    }
    
    
}

Uint8 NetManager::getAvailableId() {
    //todo: randomize id bo andrzej tak chce xd
    Uint8 id = 100;

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
        if(client->GetID()==id){
            return client.get();
        }
    }
    return nullptr;
}

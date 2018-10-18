#include <iostream>
#include <vector>
#include <SDL2/SDL_net.h>

#define SERVERIP "127.0.0.1" //temporary for testing
#define SERVERPORT 1177 //temporary for testing
#define MAX_CLIENTS 2 //lol

IPaddress address;
TCPsocket TCP_socket; //for connectivity
UDPsocket UDP_socket; //for gameplay
SDLNet_SocketSet UDP_SocketSet;
UDPpacket UDP_packet;

void init();

void accept_client();

int main(int argc, char* argv[])
{
    bool quit = false;
    
    while(!quit){
    
        // Check if any sockets are ready
        SDLNet_CheckSockets(UDP_SocketSet,0);
        
        
        
    }
}

void init(){

    std::cout << "Starting TANKS server..."<< std::endl;
    SDL_Log("Server IP: %s",SERVERIP);
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    
        std::cout << "SDL_Init %s\n" << SDL_GetError() << std::endl;
        exit(1);
        
    }
    
    if(SDLNet_Init() == -1){
        
        std::cout << "SDL_Init %s\n" << SDL_GetError() << std::endl;
        exit(2);
    }
    
    
}

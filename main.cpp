#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_net/SDL_net.h>
#else
#include <SDL2/SDL_net.h>
#endif

#define IP "153.19.7.230"
#define SERVERPORT 1616
#define min(val1, val2) (val1 > val2 ? val2 : val1)

#define DELAY 3


int main()
{
    
    SDLNet_Init();

    
    // Open the desired port for communicating of UDP
    UDPsocket socket = SDLNet_UDP_Open( SERVERPORT );
    if( socket == NULL )
    {
        SDL_Log("Failed SDLNet_UDP_Open: %s", SDLNet_GetError());
    }

    
    // Ask SDLNet to allocate a packet structure which we will later receive data into
    const int PACKET_SIZE = 9;
    UDPpacket* packet = SDLNet_AllocPacket(PACKET_SIZE);
    if( packet == NULL )
    {
        SDL_Log("Failed SDLNet_AllockPacket: %s", SDLNet_GetError());
        return 3;
    }
    
    bool quit = false;
    SDL_Event event;
    
    while( !quit )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        // Check the socket for incoming packets
        int recv_result = SDLNet_UDP_Recv( socket, packet );
        if( recv_result > 0 )
        {
            // The address field of the packet contains the source address
            printf("Received data from %s:%i", SDLNet_ResolveIP(&packet->address), SDLNet_Read16(&packet->address.port));
            
            // Ensure the data is null terminated so someone doesn't hack us!
            //packet->data[ packet->maxlen-1 ] = 0;
            
            int paczka[5];
            
            paczka[0] = (int)packet->data[0] + (int)packet->data[1]*256 ;
            paczka[1] = (int)packet->data[2] + (int)packet->data[3]*256 ;
            paczka[2] = (int)packet->data[4] + (int)packet->data[5]*256 ;
            paczka[3] = (int)packet->data[6] + (int)packet->data[7]*256 ;
            paczka[4] = (int)packet->data[8];
            
            printf( "Player: x=%d y=%d dir=%d towdir=%d move=%d\n", paczka[0] , paczka[1] , paczka[2]%360 , paczka[3]%360 , paczka[4]);

        }
        else if( recv_result < 0 )
        {
            SDL_Log( "Failed SDLNet_UDP_Recv" );
            return 5;
        }
        
        // If we didn't receive anything, wait so we don't max out the CPU
        SDL_Delay(DELAY);
    }
    
    // Cleanup
    SDLNet_FreePacket(packet); // Don't forget to free the packet!
    SDLNet_Quit();
    return 0;
}

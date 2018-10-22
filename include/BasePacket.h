#ifndef BASEPACKET_H
#define BASEPACKET_H

#include<iostream>
#include<memory>
#include<SDL2/SDL_net.h>

// First byte of a packed should always be the type
enum PacketType : Uint8{
    //todo: packettype list
    PT_BASE = 0,
    PT_UNKNOWN = 0xff
};

//ucze sie : ( przepraszam

class BasePacket
{
protected:
    BasePacket( PacketType type, unsigned int size ):
        size_((size > 1) ? size : 1) // size should be always 1 or greater

        {
            data_ = std::unique_ptr<Uint8[]>(new Uint8[size_]()); //allocate
            
            data_[0] = type;
            
        }
        
        // Content of the packet 
        std::unique_ptr<Uint8[]> data_;
        
        unsigned int size_;
    
        
public:
    virtual ~BasePacket(){}
    
    //return the type of the packet
    
    virtual PacketType GetType() const final {return (PacketType)data_[0];}
    
    virtual Uint8* GetData() const final {return data_.get();}
    
    virtual unsigned int GetSize() const final {return size_;}
    
    virtual void Print() const { std::cout << "Not defined - this is a base packet" << std::endl;}
};

#endif

# tankgameserver


## Prerequirements

### Linux
Installed packages:
```
libsdl2-dev
libsdl2-net-dev
```
### Windows
mingw64 libraries installed in:
```
C:\tools\mingw64
```
### Mac OS
Installed frameworks:
```
/Library/Frameworks/SDL2
/Library/Frameworks/SDL2_net
```

## Building

### Linux & MacOS
Simply enter the project folder and type
```
make
```
### Windows
CLI
```
make
```
## Running
Run the server by typing
```
./Server
```
in the console.
Default server ip is 127.0.0.1 (*localhost*).
Default server port is 1177


## Current progress
- [x] Make server operational
- [x] Prepare some basic packets
- [x] Enable TCP connection on the server
- [ ] Enable UDP connection on the server
- [ ] Implement main alorithm to send data between server and client
- [ ] Add more packet types based on sent data
- [ ] Synchronization stuff
- [ ] Make server initialization possible from client side (not sure of it)
- [ ] Fix some bugs...

@CzolgIT if you have any ideas what to do with server - just let me know :+1:

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
cmake .
```
(temporary - have to set proper arguments to move cmake files)
after that:
```$xslt
make
```
### Windows
CLI
```
idk how lol
```
## Running
Run the server by typing
```
./Server
```
or
```$xslt
./Server &
```
to run in the background

Default server ip is 127.0.0.1 (*localhost*).
Default server port is 1177

Just worth mentioning - to kill the server process you have to send SIGKILL. That means Ctrl+C doesnt work :poop:

Short review of ps command
```
ps -aux | grep ./Server
```
then find ./Server process and his PID number
next step is:
```
kill -9 PID
```

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
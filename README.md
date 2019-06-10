# tankgameserver


## Prerequirements

### Linux
Installed packages:
```
libsdl2-dev
libsdl2-net-dev
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
after that:
```$xslt
make
```
## Running
Run the server by typing
```
./servertanksgame
```
or
```$xslt
./servertanksgame &
```
to run in the background
or
```
./servertanksgame > logs.txt
```
to store data into logs.txt

## Additional parameters
Running server with parameter:
```
./servertanksgame debug
```
will enable debug mode and show current server status and all data in console.

Default server ip is 127.0.0.1 (*localhost*).
Default server port is 7777

To change server ip or port, edit include/Main.h defines called:
```
SERVER_IP
SERVER_PORT
```

Short review of ps command
```
ps -aux | grep ./servertanksgame
```
then find ./Server process and his PID number
next step is:
```
kill -9 PID
```

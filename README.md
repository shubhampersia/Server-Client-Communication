# Server-Client-Communication
This is a self developed basic working model of TCP and UDP server-client communication protocals.

## How To Run
Step 1. Download the source code to system in zip format or clone repo.

Step 2. On linux shell navigate to 
```
"Download-Location"/Server-Client-Communication-main/Server-Client-Communication-main/ServerClientTCP
```
Or
```
"Download-Location"/Server-Client-Communication-main/Server-Client-Communication-main/ServerClientUDP
```
Step 3. compile the server and client codes using command 
```
gcc My-Server.c -o Server
```
```
gcc My-Client.c -o Client
```
Step 4. run Server with a server port using command 
```
./Server 2000
```
Step 4. run Client with name of server and server port using command 
```
./Client localhost 2000
```
## Tech Stack Used
All the functionalities are programmed in C language with the help of socket programming libraries.

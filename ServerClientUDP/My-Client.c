// -------Include Necessary Headers-------
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFF_SIZE 2000

int main(int argc, char *argv[])
{
    // get the arguments
    if (argc != 3)
    {
        perror("Missing hostname and portnumber\n");
        exit(EXIT_FAILURE);
    }
    char *serverName = argv[1];
    int port = atoi(argv[2]);
    // buffer to store sent and recieved messages
    char message[BUFF_SIZE];

    // declare client socket and retrieve details of host
    struct hostent *host = gethostbyname(serverName);
    struct sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(port);
    clientSocket.sin_addr = **(struct in_addr **)host->h_addr_list;

    // socket() call to get file descriptor
    int clientSocketID = socket(AF_INET, SOCK_DGRAM, 0);

    // connect() to the remote address (the server)
    int status = connect(clientSocketID, (struct sockaddr *)&clientSocket, sizeof(clientSocket));
    if (status == -1)
    {
        perror("Connection failure\n");
        exit(EXIT_FAILURE);
    }
    printf("Connected successfully\nClient: ");
    socklen_t addrlen = sizeof(clientSocket);

    // start communication (sending and receiving messages)
    while (true)
    {
        scanf("%s", message);
        sendto(clientSocketID, message, sizeof(message), 0, (struct sockaddr *)&clientSocket, sizeof(clientSocket));
        if (!strcmp(message, "EXIT"))
        {
            printf("Session terminated\n");
            break;
        }
        recvfrom(clientSocketID, (char *)&message, sizeof(message), 0, (struct sockaddr *)&clientSocket, &addrlen);
        if (!strcmp(message, "EXIT"))
        {
            printf("Session terminated\n");
            break;
        }
        printf("Host: %s\nClient: ", message);
    }

    // close() the socket
    close(clientSocketID);
}
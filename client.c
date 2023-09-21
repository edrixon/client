#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.h"

int clientConnect()
{
    int sock;
    struct sockaddr_in serverAddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        perror("socket");
        return -1;
    }

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(SRVPORT);

    if(connect(sock, (const struct sockaddr *)&serverAddr,
                                        sizeof(serverAddr)) == -1)
    {
        perror("connect");
        return -1;
    }

    return sock;
}

int clientSend(int sock, unsigned char *msg)
{
    int written;

    written = write(sock, &msg[1], msg[0]);
    if(written == -1)
    {
        perror("write");
        return -1;
    }

    return written;
}

int clientReceive(int sock, unsigned char *msg)
{
    msg[0] = read(sock, &msg[1], MAXMSG);
    if(msg[0] == -1)
    {
        perror("read");
        return -1;
    }

    return msg[0];
}

void clientDisconnect(int sock)
{
    close(sock);
}


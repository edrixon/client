#ifndef __GOT_CLIENT
#define __GOT_CLIENT

#define MAXMSG  64
#define SRVPORT 4500

int clientConnect(void);
int clientSend(int sock, unsigned char *msg);
int clientReceive(int sock, unsigned char *msg);
void clientDisconnect(int sock);

#endif

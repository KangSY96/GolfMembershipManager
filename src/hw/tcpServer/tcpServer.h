#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class tcpServer
{
private:
    int serverSock_fd;
    int clientSock_fd;
    int portNum;
    bool clientState;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t clnt_addr_size;

public:
    tcpServer(int port);
    virtual ~tcpServer();
    int getServerSocket();
    int getClientSocket();
    bool getClientState();
    void setClientState(bool state);
    void createSocket();
    int waitAccept();
    int recvData(char *recvBuff, size_t size);
    int sendData(char *sendBuff, size_t size);
    void closeSocket(int socket);
};

#endif /* __TCPSERVER_H__ */
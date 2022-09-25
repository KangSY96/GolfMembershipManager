#ifndef __COMDEV_H__
#define __COMDEV_H__
#include "tcpServer.h"

class ComDev
{
private:
    tcpServer *cardTcpServer;

public:
    ComDev(tcpServer *server);
    virtual ~ComDev();
    void sendData(int *cardNum);
};

#endif /* __COMDEV_H__ */
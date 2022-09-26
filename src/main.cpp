#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>
#include "GolfMembershipManager.h"
#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "MembersEntity.h"
#include "tcpServer.h"
#include "ComDev.h"
#include "I2C.h"
#include "LCD.h"


void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    LCD lcd(new I2C("/dev/i2c-1", 0x27));
    tcpServer *cardTcpServer = new tcpServer(5100);
    ComDev *comDev = new ComDev(cardTcpServer);
    MembersManageService * membersManageSerivce = new MembersManageService(comDev, &lcd);
    Controller *controller = new Controller(membersManageSerivce);
    Listener *listener = new Listener(controller);
    std::thread threadFunc(serverThread, cardTcpServer);


    while(1)
    {
        listener->checkEvent();
        delay(50);
    }
    
    return 0;
}

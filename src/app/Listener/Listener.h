#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "CardReader.h"
#include "Monitor.h"
#include "Controller.h"
#include "ManageButton.h"

class Listener
{
private:
    CardReader *rfid;
    ManageButton *modeButton;
    ManageButton *searchButton;
    Controller *controller;
    uint8_t rfidData[16];
public:
    Listener(Controller *controller);
    virtual ~Listener();
    void checkEvent();
    bool checkRfid();
};

#endif /* __LISTENER_H__ */

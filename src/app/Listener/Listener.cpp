#include "Listener.h"
#include <string.h>

Listener::Listener(Controller *controller)
{
    rfid = new CardReader(new SPI(10, 3000000));
    modeButton = new ManageButton(27, "ModeButton");
    //controller = new Controller();
    this->controller = controller;
}

Listener::~Listener()
{
}

void Listener::checkEvent()
{
    if (checkRfid()) {
        controller->updateEvent(rfid->getCardNumber());
    }
    if (modeButton->checkButton()) {
        controller->updateEvent(modeButton->getButtonData());
    }
}

bool Listener::checkRfid()
{
    static unsigned int prevCheckTime = 0;
    
    if (millis() - prevCheckTime < 1000) {
        return false;
    }
    prevCheckTime = millis();

    if (rfid->isCard()) return true;

    return false;
}
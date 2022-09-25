#ifndef __MANAGEBUTTON_H__
#define __MANAGEBUTTON_H__

#include "Button.h"
#include "DeviceData.h"
#include <string>

class ManageButton : public Button
{
private:
    DeviceData buttonData;

public:
    ManageButton(int pin, std::string name);
    virtual ~ManageButton();
    bool checkButton();
    DeviceData getButtonData();
};

#endif /* __MANAGEBUTTON_H__ */
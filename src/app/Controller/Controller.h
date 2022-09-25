#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Monitor.h"
#include "DeviceData.h"
#include "MembersManageService.h"

class Controller
{
private:
    Monitor *monitor;
    MembersManageService *membersManageService;

public:
    Controller(MembersManageService *membersManageService);
    virtual ~Controller();
    void updateEvent(DeviceData data);
    
};

#endif /* __CONTROLLER_H__ */

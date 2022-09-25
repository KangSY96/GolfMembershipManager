#ifndef __GOLFMEMBERSHIPMANAGER_H__
#define __GOLFMEMBERSHIPMANAGER_H__

#include "Listener.h"

class GolfMembershipManager
{
private:
    Listener *listener;

public:
    GolfMembershipManager();
    virtual ~GolfMembershipManager();
    void run();
    
};

#endif /* __GOLFMEMBERSHIPMANAGER_H__ */

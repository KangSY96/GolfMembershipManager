#ifndef __MEMBERSMANAGESERVICE_H__
#define __MEMBERSMANAGESERVICE_H__
#include <string>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "ComDev.h"

enum {CARD_READER, CARD_REGISTER};

class MembersManageService
{
private:
    int membersManagerState;
    MembersEntity *membersEntity;
    ComDev  *comDev;

public:
    MembersManageService(ComDev *comDev);
    virtual ~MembersManageService();
    void setComDev(ComDev *comDev);
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
};

#endif /* __MEMBERSMANAGESERVICE_H__ */
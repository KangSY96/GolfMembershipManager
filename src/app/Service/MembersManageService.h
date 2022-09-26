#ifndef __MEMBERSMANAGESERVICE_H__
#define __MEMBERSMANAGESERVICE_H__
#include <string>
#include "MembersEntity.h"
#include "MemberInfo.h"
#include "ComDev.h"
#include "LCD.h"

enum {CARD_READER, CARD_REGISTER, CARD_DELETE, SEARCH_NAME};

class MembersManageService
{
private:
    int membersManagerState;
    int memberSearchState;
    MembersEntity *membersEntity;
    ComDev  *comDev;
    int count;
    LCD *lcd;

public:
    MembersManageService(ComDev *comDev, LCD *lcd);
    virtual ~MembersManageService();
    void setComDev(ComDev *comDev);
    void updateStateEvent(std::string devName);
    void updateSearchStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
    void memberStateLcd();
};

#endif /* __MEMBERSMANAGESERVICE_H__ */
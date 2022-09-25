#include "MembersManageService.h"
#include <cstring>

MembersManageService::MembersManageService(ComDev *comDev)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    this->comDev = comDev;
}

MembersManageService::~MembersManageService()
{
}

void MembersManageService::setComDev(ComDev *comDev)
{
    this->comDev = comDev;
}

void MembersManageService::updateStateEvent(std::string devName)
{
    switch (membersManagerState)
    {
        case CARD_READER :
            if (devName == "ModeButton") {
                membersManagerState = CARD_REGISTER;
                printf("changed to CARD_REGISTER State\n");
            }
        break;
        case CARD_REGISTER :
            if (devName == "ModeButton") {
                membersManagerState = CARD_READER;
                printf("changed to CARD_READER State\n");
            }
        break;
    }
}

void MembersManageService::checkCardNumber(int *cardNum)
{
    switch (membersManagerState)
    {
        case CARD_READER :
            if (membersEntity->findMemberInfo(cardNum)) {
                printf("Registered Member!\n");
                membersEntity->printMemberInfo(cardNum);
                comDev->sendData(cardNum);
            }
            else {
                printf("Not Registered Member!\n");
            }
        break;
        case CARD_REGISTER :
            MemberInfo tempMember;
            tempMember.id = 100001;
            strcpy(tempMember.name, "LeeSoonShin");
            strcpy(tempMember.address, "101Dong 123Ho");
            strcpy(tempMember.phoneNumber, "010-1234-5678");
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            
            membersEntity->addMemberInfo(tempMember);
            printf("Member Registered!\n");
        break;
    }
}
#include "MembersManageService.h"
#include <cstring>

MembersManageService::MembersManageService(ComDev *comDev, LCD *lcd)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    count = 1;
    this->comDev = comDev;
    this->lcd = lcd;
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
                printf("CARD REGISTER MODE!\n");
                memberStateLcd();
            }
        break;

        case CARD_REGISTER :
            if (devName == "ModeButton") {
                membersManagerState = CARD_DELETE;
                printf("CARD DELETE MODE!\n");
                memberStateLcd();
            }
        break;

        case CARD_DELETE :
            if (devName == "ModeButton") {
                membersManagerState = SEARCH_NAME;
                printf("SEARCH NAME MODE!\n");
                memberStateLcd();
            }
        break;

        case SEARCH_NAME :
            if (devName == "ModeButton") {
                membersManagerState = CARD_READER;
                printf("CARD READER MODE!\n");
                memberStateLcd();
            }
        break;

    }
}

void MembersManageService::updateSearchStateEvent(std::string devName)
{
    char memberName[20];
    MemberInfo tempMember;
    
    switch (membersManagerState)
    {
        case SEARCH_NAME :
            if (devName == "SearchButton") {
                printf("Please Input Member's Name\n");
                fgets(memberName, 20, stdin);
                strcpy(tempMember.name, memberName);
                if(membersEntity->findMemberInfo(tempMember.name))
                {
                    printf("Registered Member!\n");
                    membersEntity->printMemberInfo(tempMember.name);
                }
                else 
                {
                    printf("Not Registered Member!\n");
                }
            }
        break;
    }
}


void MembersManageService::checkCardNumber(int *cardNum)
{
    char memberName[20];
    char memberAddress[40];
    char memberPhoneNumber[15];
    char memberDelQuestion[2];

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
            tempMember.id = count;
            printf("Input New Member's Name.\n");
            fgets(memberName, 20, stdin);
            strcpy(tempMember.name, memberName);

            printf("Input New Member's Address.\n");
            fgets(memberAddress, 40, stdin);
            strcpy(tempMember.address, memberAddress);
            
            printf("Input New Member's PhoneNumber.\n");
            fgets(memberPhoneNumber, 15, stdin);
            strcpy(tempMember.phoneNumber, memberPhoneNumber);
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            
            membersEntity->addMemberInfo(tempMember);
            printf("Member Registered!\n");
            count++;
        break;

        case CARD_DELETE :
            if (membersEntity->findMemberInfo(cardNum)) {
                printf("Registered Member! Do you want to delete this information?\n");
                fgets(memberDelQuestion, 2, stdin);
                if(!strcmp(memberDelQuestion, "Y"))
                {
                    membersEntity->delMemberInfo(cardNum);
                    printf("Successfully Deleted Information.\n");
                }
                else if(!strcmp(memberDelQuestion, "N"))
                {
                    printf("Deleting information has been cancled!\n");
                }
                else
                {
                    printf("Input Error!\n");
                }
            }
            else {
                printf("Not Registered Member! There is no Data to Delete!\n");
            }
        break;
    }
}

void MembersManageService::memberStateLcd()
{
    char buff[30];

    switch (membersManagerState)
    {
            case CARD_READER :
                sprintf(buff, "READER MODE!          ");
                lcd->WriteStringXY(0, 0, buff);                
            break;

            case CARD_REGISTER :
                sprintf(buff, "REGISTER MODE!        ");
                lcd->WriteStringXY(0, 0, buff);
            break;

            case CARD_DELETE :
                sprintf(buff, "DELETE MODE!          ");
                lcd->WriteStringXY(0, 0, buff);
            break;

            case SEARCH_NAME :
                sprintf(buff, "SEARCH MODE!          ");
                lcd->WriteStringXY(0, 0, buff);
            break;
    }
}
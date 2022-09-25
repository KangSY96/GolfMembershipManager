#include "MembersEntity.h"
#include <cstring>

MembersEntity::MembersEntity()
{
    loadMembersInfo();
}

MembersEntity::~MembersEntity()
{
}

void MembersEntity::loadMembersInfo()
{
    fpDBData = fopen("memberLists.bin", "r"); //NULL
    if (fpDBData == NULL) {
        fprintf(stderr, "file open error!\n");
        return;
    }
    while (fread(&memberInfo, sizeof(MemberInfo), 1, fpDBData))
    {
        vecMembersList.push_back(memberInfo);
    }
    fclose(fpDBData);
}

void MembersEntity::printMemberInfo(int index)
{
    if (index > (int)vecMembersList.size()) {
        fprintf(stderr, "Out of range member count!\n");
        return;
    }

    printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n",
           vecMembersList[index].id,
           vecMembersList[index].name,
           vecMembersList[index].address,
           vecMembersList[index].phoneNumber,
           vecMembersList[index].cardNum[0],
           vecMembersList[index].cardNum[1],
           vecMembersList[index].cardNum[2],
           vecMembersList[index].cardNum[3],
           vecMembersList[index].cardNum[4]
           );
}

void MembersEntity::printMemberInfo(std::string name)
{
    for (const auto &member : vecMembersList) {
        if (strcmp(member.name, name.c_str()) == 0) {
            printMemberInfo(member.id);
            return;
        }
    }
}

void MembersEntity::printMemberInfo(int *cardNum)
{
    for (const auto &member : vecMembersList)
    {
        if (memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n",
                   member.id,
                   member.name,
                   member.address,
                   member.phoneNumber,
                   member.cardNum[0],
                   member.cardNum[1],
                   member.cardNum[2],
                   member.cardNum[3],
                   member.cardNum[4]);
            return;
        }
    }
}

bool MembersEntity::findMemberInfo(std::string name)
{
    for (const auto &member : vecMembersList) {
        if (strcmp(member.name, name.c_str()) == 0) {
            printMemberInfo(member.id);
            return true;
        }
    }
    return false;
}

bool MembersEntity::findMemberInfo(int *cardNum)
{
    for (const auto &member : vecMembersList) {
        if ( memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0) {
            return true;
        }
    }
    return false;
}

void MembersEntity::addMemberInfo(MemberInfo member)
{
    vecMembersList.push_back(member);
}

bool MembersEntity::delMemberInfo(int *cardNum)
{
    std::vector<MemberInfo>::iterator itrMember;
    //itrMember = vecMembersList.begin();

    for (itrMember = vecMembersList.begin(); itrMember != vecMembersList.end(); itrMember++) {
        if (memcmp(itrMember->cardNum, cardNum, sizeof(itrMember->cardNum)) == 0) {
            vecMembersList.erase(itrMember);
            return true;
        }
    }
    return false;
}

void MembersEntity::memoryToDB()
{
    fpDBData = fopen("memberLists.bin", "w"); //NULL
    FILE *fpDBData2 = fopen("memberLists.txt", "w"); //NULL
    if (fpDBData == NULL) {
        fprintf(stderr, "file open error!\n");
        return;
    }

    for (const auto &member : vecMembersList) {
        fwrite(&member, sizeof(member), 1, fpDBData);
        fprintf(fpDBData2, "%05d, %s\n", member.id, member.name);
    }
    fclose(fpDBData);
    fclose(fpDBData2);
}
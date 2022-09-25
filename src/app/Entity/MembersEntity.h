#ifndef __MEMBERSENTITY_H__
#define __MEMBERSENTITY_H__

#include <iostream>
#include <vector>
#include <string>
#include "MemberInfo.h"

class MembersEntity
{
private:
    std::vector<MemberInfo> vecMembersList;
    MemberInfo memberInfo;
    FILE *fpDBData;
    
public:
    MembersEntity();
    virtual ~MembersEntity();
    void loadMembersInfo();
    void addMemberInfo(MemberInfo member);
    bool delMemberInfo(int *cardNum);
    void memoryToDB();
    void printMemberInfo(int index);
    void printMemberInfo(std::string name);
    void printMemberInfo(int *cardNum);
    bool findMemberInfo(int *cardNum);
    bool findMemberInfo(std::string name);
};

#endif /* __MEMBERSENTITY_H__ */
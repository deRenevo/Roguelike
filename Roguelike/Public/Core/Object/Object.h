// Copyright deRenevo. All rights reserved.

#pragma once 

#include <string>
#include <vector>

class OObject
{
    static int GenerateUniqueId()
    {
        static int NextId = 1;
        return NextId++;
    }

    static std::vector<OObject*> AllObjects;

    std::string ObjectName = "None";
    int UniqueId;
    bool bIsPendingKill = false;

public:
    OObject(std::string name);
    OObject();
    virtual ~OObject();

    void SetIsPendingKill();
    std::string GetObjectName() const;
    int GetUniqueId() const;
    bool GetIsPendingKill() const;
};
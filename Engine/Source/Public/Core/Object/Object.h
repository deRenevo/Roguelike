// Copyright deRenevo. All rights reserved.

#pragma once 

#include <string>
#include <vector>

#include "Core/Math/BasicTypes.h"

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

    //setters
    void SetIsPendingKill()
    {
        bIsPendingKill = true;
    }
    
    //getters
    std::string GetName() const
    {
        return ObjectName;    
    }
    
    int32 GetUniqueId() const
    {
        return UniqueId;
    }
    
    bool GetIsPendingKill() const
    {
        return bIsPendingKill;
    }
};

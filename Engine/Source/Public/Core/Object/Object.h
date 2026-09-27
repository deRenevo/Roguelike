// Copyright deRenevo. All rights reserved.

#pragma once 

#include <string>
#include <vector>

#include "Core/Math/BasicTypes.h"

class OObject
{
    static int GenerateUniqueId()
    {
        static uint32 NextId = 1;
        return NextId++;
    }

    static inline std::vector<OObject*> AllObjects;

    std::string ObjectName = "None";
    int UniqueId;
    bool bIsPendingKill = false;
    uint32 RegistryIndex; //Index in vector for fast ears in destructor 

public:
    OObject(const std::string& objectName);
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

// Copyright deRenevo. All rights reserved.

#pragma once 

#include <string>

class OObject
{
    std::string ObjectName;
    int UniquedId;
    bool bIsPendingKill = false;

protected:
    void SetIsPendingKill();

public:
    std::string GetObjectName();
    int GetUniquedId();
    bool GetIsPendingKill();
};
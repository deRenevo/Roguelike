// Copyright deRenevo. All rights reserved.

#include <Core/Object/Object.h>

void OObject::SetIsPendingKill()
{
    bIsPendingKill = true;
}

std::string OObject::GetObjectName()
{
    return ObjectName;
}

int OObject::GetUniquedId()
{
    return UniquedId;
}

bool OObject::GetIsPendingKill()
{
    return bIsPendingKill;
}

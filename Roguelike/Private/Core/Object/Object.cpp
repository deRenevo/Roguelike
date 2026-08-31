// Copyright deRenevo. All rights reserved.

#include <Core/Object/Object.h>

std::vector<OObject *> OObject::AllObjects;

void OObject::SetIsPendingKill()
{
	bIsPendingKill = true;
}

OObject::OObject(std::string objectName) : UniqueId(GenerateUniqueId()), ObjectName(objectName)
{
	AllObjects.push_back(this);
}

OObject::OObject() : UniqueId(GenerateUniqueId())
{
	AllObjects.push_back(this);
}

OObject::~OObject()
{
	std::erase(AllObjects, this);
}

std::string OObject::GetObjectName() const
{
	return ObjectName;
}

int OObject::GetUniqueId() const
{
	return UniqueId;
}

bool OObject::GetIsPendingKill() const
{
	return bIsPendingKill;
}

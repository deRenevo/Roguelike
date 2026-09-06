// Copyright deRenevo. All rights reserved.

#include "Core/Object/Object.h"

std::vector<OObject*> OObject::AllObjects;


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

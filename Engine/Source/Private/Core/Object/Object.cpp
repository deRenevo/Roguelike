// Copyright deRenevo. All rights reserved.

#include "Core/Object/Object.h"

#include <ostream>

OObject::OObject(const std::string& objectName) : ObjectName(objectName), UniqueId(GenerateUniqueId())
{
	RegistryIndex = AllObjects.size();
	AllObjects.push_back(this);
}

OObject::OObject() : OObject("Object")
{

}

OObject::~OObject()
{
	uint32 Last = AllObjects.size() - 1;
	if (RegistryIndex != Last)
	{
		AllObjects[RegistryIndex] = AllObjects[Last];
		AllObjects[RegistryIndex]->RegistryIndex = RegistryIndex;
	}
	AllObjects.pop_back();
}

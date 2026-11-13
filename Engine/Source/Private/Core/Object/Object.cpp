// Copyright deRenevo. All rights reserved.

#include "Core/Object/Object.h"

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
	if (const uint32 Last = AllObjects.size() - 1; RegistryIndex != Last)
	{
		AllObjects[RegistryIndex] = AllObjects[Last];
		AllObjects[RegistryIndex]->RegistryIndex = RegistryIndex;
	}
	AllObjects.pop_back();
}

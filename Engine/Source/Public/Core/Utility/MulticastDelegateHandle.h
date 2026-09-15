// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Math/BasicTypes.h"

struct FMulticastDelegateHandle
{
	uint64 Id = 0;
	void* MulticastDelegate = nullptr;
	
	constexpr bool operator==(const FMulticastDelegateHandle& other) const
	{
		return Id == other.Id && MulticastDelegate == other.MulticastDelegate;
	}
	
	constexpr bool operator!=(const FMulticastDelegateHandle& other) const
	{
		return !(*this == other);
	}
	 
	constexpr  bool IsValid() const
	{
		return Id != 0 && MulticastDelegate != nullptr;
	}
};

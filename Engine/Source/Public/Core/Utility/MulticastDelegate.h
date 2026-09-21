#pragma once

#include "Core/Utility/MulticastDelegateHandle.h"

#include <functional>
#include <vector>

template <typename... Args>
class MulticastDelegate
{
	uint64 UId = 0;

	struct FIdCallBack
	{
		uint64 Id = 0;
		std::function<void(Args...)> Callback;
	};

	std::vector<FIdCallBack> DelegateCallbacks;

public:
	FMulticastDelegateHandle Add(std::function<void(Args...)> callback)
	{
		uint64 Id = ++UId;
		DelegateCallbacks.push_back({Id, callback});
		return {Id, this};
	}

	void Remove(const FMulticastDelegateHandle& handle)
	{
		if (!handle.IsValid() || handle.MulticastDelegate != this)
		{
			return;
		}

		std::erase_if(DelegateCallbacks,
			[id = handle.Id](const FIdCallBack& cb)
			{
				return cb.Id == id;
			});
	}

	void Broadcast(Args... args)
	{
		auto callbacks = DelegateCallbacks;
		for (const FIdCallBack& cb : callbacks)
		{
			if (cb.Callback)
			{
				cb.Callback(args...);
			}
		}
	}

	void Clear()
	{
		DelegateCallbacks.clear();
	}

	bool IsEmpty() const
	{
		return DelegateCallbacks.empty();
	}
};

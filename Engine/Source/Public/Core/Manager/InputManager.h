// Copyright deRenevo. All rights reserved.

#pragma once

#include <raylib.h>
#include <functional>
#include <vector>

#include "Core/Object/Object.h"
#include "Core/Utility/MulticastDelegate.h"

enum class EInputType
{
	Pressed,
	Released,
	Held
};

struct FKeyAction
{
	KeyboardKey Key;
	MulticastDelegate<> Callback;
	EInputType InputType;
};

class OInputManager : public OObject
{
	std::vector<FKeyAction> KeyActions;
	std::vector<KeyboardKey> OldKeyInput;

	OInputManager() = default;
	virtual ~OInputManager() override = default;

public:
	
	OInputManager(const OInputManager&) = delete;
	OInputManager& operator=(const OInputManager&) = delete;
	OInputManager(OInputManager&) = delete;
	OInputManager& operator=(OInputManager&&) = delete;
	
	void UpdateKeyInput();
	static OInputManager& GetInstance()
	{
		static OInputManager InputManager;
		return InputManager;
	}
	
	FMulticastDelegateHandle SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback);
	void ClearSubscribedKeys()
	{
		KeyActions.clear();
	}
};

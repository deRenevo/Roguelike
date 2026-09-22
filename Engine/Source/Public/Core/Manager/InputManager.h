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

class InputManager : public OObject
{
	std::vector<FKeyAction> KeyActions;
	std::vector<KeyboardKey> OldKeyInput;

	InputManager() = default;
	virtual ~InputManager() override = default;

public:
	
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;
	
	void UpdateKeyInput();
	static InputManager& GetInstance()
	{
		static InputManager IM;
		return IM;
	}
	
	FMulticastDelegateHandle SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback);
	void ClearSubscribedKeys()
	{
		KeyActions.clear();
	}
	
	void UnsubscribeKey(FMulticastDelegateHandle keyDelegateHandle);
};

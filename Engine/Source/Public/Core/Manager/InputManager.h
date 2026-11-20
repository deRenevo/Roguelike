// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Utility/MulticastDelegate.h"

#include "raylib.h"

#include <list>

enum class EInputType
{
	Pressed,
	Released,
	Held
};

struct FKeyAction
{
	EInputType InputType;
	KeyboardKey Key;
	MulticastDelegate<> Callback;
};

class InputManager
{
	std::list<FKeyAction> KeyActions;
	std::vector<KeyboardKey> OldKeyInput;

	InputManager() = default;
	virtual ~InputManager() = default;

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

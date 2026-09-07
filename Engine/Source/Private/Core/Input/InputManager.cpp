// Copyright deRenevo. All rights reserved.

#include "Core/Input/InputManager.h"

#include <algorithm>

#include "Core/Math/BasicTypes.h"

InputManager& InputManager::GetInstance()
{
	static InputManager IM;
	return IM;
}

void InputManager::Tick()
{
	std::vector<KeyboardKey> CurrentFrameKeys;
	for (uint16 key = 0; key < 512; ++key)
	{
		if (IsKeyDown(key))
			CurrentFrameKeys.push_back(static_cast<KeyboardKey>(key));
	}

	for (FKeyAction& KeyAction : SubscribedKey)
	{
		bool WasDown = std::ranges::find(OldKeyInput, KeyAction.Key) != OldKeyInput.end();
		bool isDown = std::ranges::find(CurrentFrameKeys, KeyAction.Key) != CurrentFrameKeys.end();

		switch (KeyAction.InputType)
		{
		case EInputType::Pressed:
			if (!WasDown && isDown)
				KeyAction.Function();
			break;
		case EInputType::Released:
			if (WasDown && !isDown)
				KeyAction.Function();
			break;
		case EInputType::Held:
			if (isDown)
				KeyAction.Function();
			break;
		}
	}

	OldKeyInput = CurrentFrameKeys;
}

void InputManager::SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void(void)>& function)
{
	if (key == KeyboardKey::KEY_NULL) return;

	FKeyAction Action = FKeyAction(key, inputType, function);
	SubscribedKey.push_back(Action);
}

void InputManager::ClearSubscriptionKey()
{
	SubscribedKey.clear();
}

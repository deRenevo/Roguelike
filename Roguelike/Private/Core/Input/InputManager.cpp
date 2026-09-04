// Copyright deRenevo. All rights reserved.

#include "Core/Input/InputManager.h"

#include <algorithm>

InputManager& InputManager::GetInstance()
{
	static InputManager IM;
	return IM;
}

void InputManager::Tick()
{
	std::vector<KeyboardKey> CurrentFrameKeys;
	for (int key = 0; key < 512; ++key)
	{
		if (IsKeyDown(key))
			CurrentFrameKeys.push_back(static_cast<KeyboardKey>(key));
	}

	for (FKeyAction& KeyAction : SubscribedKey)
	{
		bool WasDown = std::find(OldKeyInput.begin(), OldKeyInput.end(), KeyAction.Key) != OldKeyInput.end();
		bool isDown = std::find(CurrentFrameKeys.begin(), CurrentFrameKeys.end(), KeyAction.Key) != CurrentFrameKeys.end();

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

void InputManager::SubscribeKey(KeyboardKey key, EInputType inputType, std::function<void(void)> function)
{
	if (key == KeyboardKey::KEY_NULL) return;

	FKeyAction Action = FKeyAction(key, inputType, function);
	SubscribedKey.push_back(Action);
}

void InputManager::ClearSubscriptionKey()
{
	SubscribedKey.clear();
}

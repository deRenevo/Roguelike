// Copyright deRenevo. All rights reserved.

#include "Core/Manager/InputManager.h"

#include "Core/Math/BasicTypes.h"

#include <algorithm>
#include <ostream>

void InputManager::UpdateKeyInput()
{
	std::vector<KeyboardKey> KeysInput;

	for (uint16 Key = 0; Key < 512; ++Key)
	{
		if (IsKeyDown(Key))
			KeysInput.push_back(static_cast<KeyboardKey>(Key));
	}

	for (FKeyAction& KeyAction : KeyActions)
	{
		const bool WasDown = std::ranges::find(OldKeyInput, KeyAction.Key) != OldKeyInput.end();
		const bool IsDown = std::ranges::find(KeysInput, KeyAction.Key) != KeysInput.end();

		switch (KeyAction.InputType)
		{
		case EInputType::Pressed:
			if (!WasDown && IsDown)
				KeyAction.Callback.Broadcast();
			break;
		case EInputType::Released:
			if (WasDown && !IsDown)
				KeyAction.Callback.Broadcast();
			break;
		case EInputType::Held:
			if (IsDown)
				KeyAction.Callback.Broadcast();
			break;
		}
	}
	OldKeyInput = KeysInput;
}

FMulticastDelegateHandle InputManager::SubscribeKey(const KeyboardKey key, const EInputType inputType, const std::function<void()>& callback)
{
	if (key == KeyboardKey::KEY_NULL) return FMulticastDelegateHandle();

	auto It = std::ranges::find_if(KeyActions, [&](const FKeyAction& keyAction)
	{
		return keyAction.Key == key && keyAction.InputType == inputType;
	});

	if (It != KeyActions.end())
	{
		FKeyAction& FoundAction = *It;
		return FoundAction.Callback.Add(callback);
	}

	KeyActions.push_back({});
	FKeyAction& NewAction = KeyActions.back(); 
	NewAction.Key = key;
	NewAction.InputType = inputType;
	return NewAction.Callback.Add(callback);
}

void InputManager::UnsubscribeKey(const FMulticastDelegateHandle keyDelegateHandle)
{
	if (!keyDelegateHandle.IsValid())
		return;

	for (auto It = KeyActions.begin(); It != KeyActions.end(); ++It)
	{
		const void* DelegatePtr = static_cast<void*>(&It->Callback);
		
		if (DelegatePtr == keyDelegateHandle.MulticastDelegate)
		{
			It->Callback.Remove(keyDelegateHandle);
			if (It->Callback.IsEmpty())
			{
				KeyActions.erase(It);
			}
			return;
		}
	}
}

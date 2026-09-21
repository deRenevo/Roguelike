// Copyright deRenevo. All rights reserved.

#include "Core/Manager/InputManager.h"

#include <algorithm>
#include <ostream>

#include "Core/Math/BasicTypes.h"

void OInputManager::UpdateKeyInput()
{
	std::vector<KeyboardKey> KeysInput;

	for (uint16 key = 0; key < 512; ++key)
	{
		if (IsKeyDown(key))
			KeysInput.push_back(static_cast<KeyboardKey>(key));
	}

	for (FKeyAction& KeyAction : KeyActions)
	{
		bool WasDown = std::ranges::find(OldKeyInput, KeyAction.Key) != OldKeyInput.end();
		bool isDown = std::ranges::find(KeysInput, KeyAction.Key) != KeysInput.end();

		switch (KeyAction.InputType)
		{
		case EInputType::Pressed:
			if (!WasDown && isDown)
				KeyAction.Callback.Broadcast();
			break;
		case EInputType::Released:
			if (WasDown && !isDown)
				KeyAction.Callback.Broadcast();
			break;
		case EInputType::Held:
			if (isDown)
				KeyAction.Callback.Broadcast();
			break;
		}
	}
	OldKeyInput = KeysInput;
}

FMulticastDelegateHandle OInputManager::SubscribeKey(KeyboardKey key, EInputType inputType, const std::function<void()>& callback)
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

void OInputManager::UnsubscribeKey(const FMulticastDelegateHandle keyDelegateHandle)
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

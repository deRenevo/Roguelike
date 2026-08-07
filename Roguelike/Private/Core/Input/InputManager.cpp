// Copyright deRenevo. All rights reserved.

#include <Core/Input/InputManager.h>

InputManager &InputManager::GetInstance()
{
    static InputManager IM;
    return IM;
}

void InputManager::KeyInput(KeyboardKey key)
{
    if (key == KeyboardKey::KEY_NULL) return;

    for (FKeyAction& KeyAction : SubscribedKey)
    {
        if (KeyAction.Key == key)
        {
            KeyAction.Function();
        }
    }
}

void InputManager::SubscribeKey(KeyboardKey key, std::function<void(void)> function)
{
    if (key == KeyboardKey::KEY_NULL) return;

    FKeyAction Action = FKeyAction(key, function);
    SubscribedKey.push_back(Action);
}

void InputManager::ClearSubscribtionKey()
{
    SubscribedKey.clear();
}
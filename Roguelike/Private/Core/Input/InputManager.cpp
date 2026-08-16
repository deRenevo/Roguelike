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
        if (KeyAction.InputType == EInputType::Pressed && KeyAction.Key == key)
        {
            KeyAction.Function();
        }
    }
}

void InputManager::Tick()
{
    //for Input down
    for (FKeyAction& KeyAction : SubscribedKey)
    {
        if (KeyAction.InputType == EInputType::Held && IsKeyDown(KeyAction.Key))
        {
            KeyAction.Function();
        }
    }
}

void InputManager::SubscribeKey(KeyboardKey key, EInputType inputType, std::function<void(void)> function)
{

    FKeyAction Action = FKeyAction(key, inputType, function);
    SubscribedKey.push_back(Action);
}

void InputManager::ClearSubscribtionKey()
{
    SubscribedKey.clear();
}
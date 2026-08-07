#include <Core/Input/InputMenager.h>

InputMenager &InputMenager::GetInstance()
{
    static InputMenager IM;
    return IM;
}

void InputMenager::KeyInput(KeyboardKey key)
{
    if (key == KeyboardKey::KEY_NULL) return;

    for (FKeyAction& KeyAction : SubscripbedKey)
    {
        if (KeyAction.Key == key)
        {
            KeyAction.Function();
        }
    }
}

void InputMenager::SubscriptionKey(KeyboardKey key, std::function<void(void)> function)
{
    if (key == KeyboardKey::KEY_NULL) return;

    FKeyAction Action = FKeyAction(key, function);
    SubscripbedKey.push_back(Action);
}

void InputMenager::ClearSubscriptionKey()
{
    SubscripbedKey.clear();
}
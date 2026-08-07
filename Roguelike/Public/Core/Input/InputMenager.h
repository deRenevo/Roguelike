#pragma once

#include <functional>
#include <vector>
#include "raylib.h"

struct FKeyAction
{
    KeyboardKey Key;
    std::function<void(void)> Function;
    FKeyAction(KeyboardKey key, std::function<void(void)> function) : Key(key), Function(function){};
};

class InputMenager
{
    std::vector<FKeyAction> SubscripbedKey;

public:
    static InputMenager& GetInstance();
    void KeyInput(KeyboardKey key);

    void SubscriptionKey(KeyboardKey key, std::function<void(void)> function);
    void ClearSubscriptionKey();
};
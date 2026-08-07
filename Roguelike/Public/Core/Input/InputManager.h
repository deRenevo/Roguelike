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

class InputManager
{
    std::vector<FKeyAction> SubscribedKey;

public:
    static InputManager& GetInstance();
    void KeyInput(KeyboardKey key);

    void SubscribeKey(KeyboardKey key, std::function<void(void)> function);
    void ClearSubscribtionKey();
};
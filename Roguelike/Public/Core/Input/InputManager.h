// Copyright deRenevo. All rights reserved.

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

    InputManager() = default;
    ~InputManager() = default;

public:
    static InputManager& GetInstance();

    InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

    void KeyInput(KeyboardKey key);

    void SubscribeKey(KeyboardKey key, std::function<void(void)> function);
    void ClearSubscribtionKey();
};
// Copyright deRenevo. All rights reserved.

#pragma once

#include <raylib.h>
#include <functional>
#include <vector>

enum EInputType
{
    Pressed,
    Released,
    Held
};

struct FKeyAction
{
    KeyboardKey Key;
    std::function<void(void)> Function;
    EInputType InputType;

    FKeyAction(KeyboardKey key, EInputType inputType, std::function<void(void)> function) : Key(key), 
        InputType(inputType), Function(function){};
};

class InputManager
{
    std::vector<FKeyAction> SubscribedKey;
    std::vector<KeyboardKey> OldKeyInput;

    InputManager() = default;
    ~InputManager() = default;

public:
    static InputManager& GetInstance();

    InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

    void KeyInput(KeyboardKey key);
    void Tick();

    void SubscribeKey(KeyboardKey key, EInputType inputType, std::function<void(void)> function);
    void ClearSubscribtionKey();
};
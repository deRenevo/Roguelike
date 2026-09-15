// Copyright deRenevo. All rights reserved.

#pragma once


#include "Core/Widget/Widget.h"
#include "Core/Utility/Struct.h"

#include <raylib.h>
#include <functional>

#include "Core/Utility/MulticastDelegate.h"


class WButton : public WWidget
{
	enum class EButtonStatus
	{
		Normal,
		Hovered,
		Clicked
	};

	const char* Text;
	FButtonStyle ButtonStyle;

	EButtonStatus BtState = EButtonStatus::Normal;

public:
	WButton(const char* text = "Hello Roguelike",
			Rectangle bound = Rectangle(0, 0, 100, 40),
			std::function<void()> callback = nullptr
	);

	MulticastDelegate<> OnClickDelegate;

protected:
	virtual void Construction() override; //-> processed when changing priced
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override; //-> every frame is processed

/*
 * => setter and getter
*/

public:
	void SetStyle(const FButtonStyle& buttonStyle);
};

// Copyright deRenevo. All rights reserved.

#pragma once



#include "Core/Widgets/WidgetsElements/Widget.h"
#include "Core/Utility/Struct.h"

#include <raylib.h>
#include <functional>


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
	std::function<void()> OnClickCallback;

	EButtonStatus BtState = EButtonStatus::Normal;

public:

	WButton(const char* text = "Hello Rogalice",
		Rectangle bound = Rectangle(0, 0, 100, 40),
		std::function<void()> callback = nullptr
		);

protected:
	virtual void Construction() override; //-> processed when changing priced
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override; //-> every frame is processed

/*
 * => setter and getter
*/

public:
	void SetOnClick(std::function<void()> callback);
	void SetStyle(const FButtonStyle& buttonStyle);
};
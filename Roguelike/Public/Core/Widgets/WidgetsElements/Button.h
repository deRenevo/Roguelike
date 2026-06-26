#pragma once

#include "Raylib.h"

#include <Core/Widgets/WidgetsElements/Widget.h>
#include <Core/Utility/Struct.h>
#include <functional>
#include <memory>


class Button : public Widget
{
	enum class EButtonStatus
	{
		Normal,
		Hovered,
		Clicked
	};

	const char* Text;
	FButtonStyle ButtonStyle;
	bool bIsCenter;
	std::function<void()> OnClickCallback;

	EButtonStatus BtState = EButtonStatus::Normal;

public:

	Button(const char* text = "Hello Rogalice",
		Rectangle bound = Rectangle(0, 0, 100, 40),
		bool IsCenter = false,
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
// Copyright deRenevo. All rights reserved.

#include <Core/Widgets/WidgetsElements/Button.h>
#include <Core/Utility/Draw/DrawUtility.h>

#include <iostream>

WButton::WButton(const char* text, Rectangle bound, std::function<void()> callback) :
	Text(text), OnClickCallback(callback)
{
	SetBound(bound);
}

void WButton::Construction()
{
	
}

void WButton::Draw()
{
	Rectangle Bound = GetWorldBoundWithAlignment();

	switch (BtState)
	{
	case WButton::EButtonStatus::Normal:
		DrawRectangleRec(Bound, ButtonStyle.Normal.BaseColor);

		DrawRectangleLinesEx(Bound, ButtonStyle.Normal.BorderWidth, ButtonStyle.Normal.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, Bound.x + Bound.width / 2, Bound.y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case WButton::EButtonStatus::Hovered:
		DrawRectangleRec(Bound, ButtonStyle.Hovered.BaseColor);

		DrawRectangleLinesEx(Bound, ButtonStyle.Hovered.BorderWidth, ButtonStyle.Hovered.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, Bound.x + Bound.width / 2, Bound.y
			+ Bound.height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case WButton::EButtonStatus::Clicked:
		DrawRectangleRec(Bound, ButtonStyle.Clicked.BaseColor);

		DrawRectangleLinesEx(Bound, ButtonStyle.Clicked.BorderWidth, ButtonStyle.Clicked.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, Bound.x + Bound.width / 2, Bound.y
			+ Bound.height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	default:
		break;
	}
}

void WButton::Tick(float DeltaTime)
{
	Rectangle WorldBound = GetWorldBoundWithAlignment();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), WorldBound))
	{
		BtState = EButtonStatus::Clicked;

		if (OnClickCallback)
		{
			OnClickCallback();
		}
	}
	else if (CheckCollisionPointRec(GetMousePosition(), WorldBound))
	{
		BtState = EButtonStatus::Hovered;
	}
	else
	{
		BtState = EButtonStatus::Normal;
	}
}

void WButton::SetOnClick(std::function<void()> callback)
{
	OnClickCallback = callback;
}

void WButton::SetStyle(const FButtonStyle& buttonStyle)
{
	ButtonStyle = buttonStyle;
}

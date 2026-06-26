#include <Core/Widgets/WidgetsElements/Button.h>
#include <Core/Utility/Draw/DrawUtility.h>

#include <iostream>

Button::Button(const char* text, Rectangle bound, bool IsCenter, std::function<void()> callback) :
	Text(text), OnClickCallback(callback)
{
	if (bIsCenter)
	{
		bound.x -= bound.width / 2;
		bound.y -= bound.height / 2;
	}

	SetBound(bound);
}

void Button::Construction()
{
}

void Button::Draw()
{
	switch (BtState)
	{
	case Button::EButtonStatus::Normal:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Normal.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Normal.BorderWidth, ButtonStyle.Normal.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case Button::EButtonStatus::Hovered:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Hovered.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Hovered.BorderWidth, ButtonStyle.Hovered.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case Button::EButtonStatus::Clicked:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Clicked.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Clicked.BorderWidth, ButtonStyle.Clicked.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	default:
		break;
	}
}

void Button::Tick(float DeltaTime)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), GetLocalBound()))
	{
		BtState = EButtonStatus::Clicked;

		if (OnClickCallback)
		{
			OnClickCallback();
		}
	}
	else if (CheckCollisionPointRec(GetMousePosition(), GetLocalBound()))
	{
		BtState = EButtonStatus::Hovered;
	}
	else
	{
		BtState = EButtonStatus::Normal;
	}
}

void Button::SetOnClick(std::function<void()> callback)
{
	OnClickCallback = callback;
}

void Button::SetStyle(const FButtonStyle& buttonStyle)
{
	ButtonStyle = buttonStyle;
}

#include <Core/Widgets/WidgetsElements/Button.h>
#include <Core/Utility/Draw/DrawUtility.h>

#include <iostream>

WButton::WButton(const char* text, Rectangle bound, bool IsCenter, std::function<void()> callback) :
	Text(text), OnClickCallback(callback)
{
	if (bIsCenter)
	{
		bound.x -= bound.width / 2;
		bound.y -= bound.height / 2;
	}

	SetBound(bound);
}

void WButton::Construction()
{
}

void WButton::Draw()
{
	switch (BtState)
	{
	case WButton::EButtonStatus::Normal:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Normal.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Normal.BorderWidth, ButtonStyle.Normal.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case WButton::EButtonStatus::Hovered:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Hovered.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Hovered.BorderWidth, ButtonStyle.Hovered.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	case WButton::EButtonStatus::Clicked:
		DrawRectangleRec(GetLocalBound(), ButtonStyle.Clicked.BaseColor);

		DrawRectangleLinesEx(GetLocalBound(), ButtonStyle.Clicked.BorderWidth, ButtonStyle.Clicked.BorderColor);

		DrawUtility::DrawTextWithOneColor(Text, GetLocalBound().x + GetLocalBound().width / 2, GetLocalBound().y
			+ GetLocalBound().height / 2, ButtonStyle.TextStyle.FontSize, ButtonStyle.TextStyle.TextColor, true);

		break;

	default:
		break;
	}
}

void WButton::Tick(float DeltaTime)
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

void WButton::SetOnClick(std::function<void()> callback)
{
	OnClickCallback = callback;
}

void WButton::SetStyle(const FButtonStyle& buttonStyle)
{
	ButtonStyle = buttonStyle;
}

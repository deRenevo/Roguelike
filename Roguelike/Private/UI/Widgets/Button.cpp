#include <UI/Widgets/Button.h>
#include <Utility/Draw/DrawUtility.h>


Button::Button(const char* text, Rectangle bounds, int fontSize, Color textColor, Color normalButtonColor, Color normalBorderColor, float borderWidth, bool IsCenter)
{
	Bounds = bounds;
	BorderWidth = borderWidth;
	NormalButtonColor = normalButtonColor;
	NormalBorderColor = normalBorderColor;

	Text = text;
	FontSize = fontSize;
	TextColor = textColor;


	if (IsCenter)
	{
		Bounds.x -= Bounds.width / 2;
		Bounds.y -= Bounds.height / 2;
	}
}

void Button::Draw(ButtonStatus Stat)
{


	switch (Stat)
	{
	case Button::NONE:
		DrawRectangleRec(Bounds, NormalButtonColor);
		DrawRectangleLinesEx(Bounds, BorderWidth, NormalBorderColor);
		DrawUtility::DrawTextWithOneColor(Text, Bounds.x + Bounds.width / 2, Bounds.y + Bounds.height / 2, FontSize, TextColor, true);
		break;
	case Button::Hovered:
		DrawRectangleRec(Bounds, WHITE);
		DrawRectangleLinesEx(Bounds, BorderWidth, NormalBorderColor);
		DrawUtility::DrawTextWithOneColor(Text, Bounds.x + Bounds.width / 2, Bounds.y + Bounds.height / 2, FontSize, TextColor, true);
		break;
	case Button::Clicked:
		DrawRectangleRec(Bounds, DARKGRAY);
		DrawRectangleLinesEx(Bounds, BorderWidth, NormalBorderColor);
		DrawUtility::DrawTextWithOneColor(Text, Bounds.x + Bounds.width / 2, Bounds.y + Bounds.height / 2, FontSize, TextColor, true);
		break;
	default:
		break;
	}


}

void Button::Update()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Bounds))
	{
		BtStatus = ButtonStatus::Clicked;
	}
	else if (CheckCollisionPointRec(GetMousePosition(), Bounds))
	{
		BtStatus = ButtonStatus::Hovered;
	}
	else
	{
		BtStatus = ButtonStatus::NONE;
	}

	Draw(BtStatus);
}
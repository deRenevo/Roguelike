#include "Raylib.h"

class Button
{
	enum ButtonStatus
	{
		NONE,
		Hovered,
		Clicked
	};
	Rectangle Bounds;

	Color NormalButtonColor;
	Color NormalBorderColor;
	float BorderWidth;
	const char* Text;
	int FontSize;
	Color TextColor;


	ButtonStatus BtStatus = ButtonStatus::NONE;
public:
	Button(const char* text = "Hello Rogalice",
		Rectangle bounds = { 0 , 0, 100, 40 },
		int fontSize = 24, Color textColor = RAYWHITE,
		Color normalButtonColor = SKYBLUE, Color normalBorderColor = BLUE,
		float borderWidth = 2, bool IsCenter = false);

	void Draw(ButtonStatus Stat);
	void Update();
};
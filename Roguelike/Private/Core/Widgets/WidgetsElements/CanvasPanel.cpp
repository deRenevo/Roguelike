#include <Core/Widgets/WidgetsElements/CanvasPanel.h>
#include <iostream>

void WCanvasPanel::Construction()
{
	std::cout << "CanvasPanel::Construction" << std::endl;
	Rectangle bound =
	{
		0,
		0,
		GetScreenWidth(),
		GetScreenHeight()
	};
	SetBound(bound);
}

void WCanvasPanel::Draw()
{
	WContainer::Draw();
}

Vector2 WCanvasPanel::GetSize()
{
    return Vector2(GetScreenWidth(), GetScreenHeight());
}

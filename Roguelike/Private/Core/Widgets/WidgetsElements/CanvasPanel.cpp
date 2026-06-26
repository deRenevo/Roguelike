#include <Core/Widgets/WidgetsElements/CanvasPanel.h>
#include <iostream>

void CanvasPanel::Construction()
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

void CanvasPanel::Draw()
{
	Container::Draw();
}

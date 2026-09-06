// Copyright deRenevo. All rights reserved.

#include "Core/Widget/CanvasPanel.h"
#include <iostream>

void WCanvasPanel::Construction()
{
	std::cout << "CanvasPanel::Construction" << std::endl;
	Rectangle Bound = Rectangle(0, 0, GetScreenWidth(), GetScreenHeight());
	SetBound(Bound);
}

void WCanvasPanel::Draw()
{
	WContainer::Draw();
}

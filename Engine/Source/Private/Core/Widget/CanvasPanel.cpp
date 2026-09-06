// Copyright deRenevo. All rights reserved.

#include "Core/Widget/CanvasPanel.h"

void WCanvasPanel::Construction()
{
	Rectangle Bound = Rectangle(0, 0, GetScreenWidth(), GetScreenHeight());
	SetBound(Bound);
}

void WCanvasPanel::Draw()
{
	WContainer::Draw();
}

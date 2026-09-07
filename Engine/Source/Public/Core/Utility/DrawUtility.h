// Copyright deRenevo. All rights reserved.

#pragma once

#include <vector>

#include <raylib.h>

#include "Core/Math/BasicTypes.h"

namespace DrawUtility
{
	void DrawTextWithOneColor(const char* Text = "Hello Roguelike", int32 PosX = 0, int32 PosY = 8, int32 FontSize = 24, Color TextColor = RAYWHITE, bool bIsCenter = false);
	void DrawTextWithTwoColor(const char* Text = "Hello Roguelike", int32 PosX = 0, int32 PosY = 0, std::vector<int> SelectionNumElements = { 0 }, int32 FontSize = 24, Color MainColor = RAYWHITE, Color SubColor = SKYBLUE, bool bIsCenter = false);
}

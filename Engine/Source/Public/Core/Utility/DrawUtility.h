// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Math/BasicTypes.h"

#include "raylib.h"

#include <vector>

namespace DrawUtility
{
	auto DrawTextWithOneColor(const char* text = "Hello Roguelike", int32 posX = 0, int32 posY = 8, int32 fontSize = 24, Color textColor = RAYWHITE, bool bIsCenter = false) -> void;
	void DrawTextWithTwoColor(const char* text = "Hello Roguelike", int32 posX = 0, int32 posY = 0, const std::vector<int>& selectionNumElements = { 0 }, int32 fontSize = 24, Color mainColor = RAYWHITE, Color subColor = SKYBLUE, bool bIsCenter = false);
}

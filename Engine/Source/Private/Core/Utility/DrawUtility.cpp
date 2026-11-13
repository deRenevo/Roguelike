// Copyright deRenevo. All rights reserved.

#include "Core/Utility/DrawUtility.h"

#include <ios>
#include <sstream>

void DrawUtility::DrawTextWithOneColor(const char* text, int32 posX, int32 posY, const int32 fontSize, Color const textColor, const bool bIsCenter)
{
	if (bIsCenter)
	{
		posX -= MeasureText(text, fontSize) / 2;
		posY -= fontSize / 2;
	}

	DrawText(text, posX, posY, fontSize, textColor);
}

void DrawUtility::DrawTextWithTwoColor(const char* text, int32 posX, int32 posY, const std::vector<int32>& selectionNumElements, const int32 fontSize, const Color mainColor, const Color subColor, const bool bIsCenter)
{
	std::vector<std::string> Words;

	{
		std::string Word;
		std::istringstream ISS(text);
		
		if (bIsCenter)
		{
			posX -= MeasureText(text, fontSize) / 2;
			posY -= fontSize / 2;
		}

		while (ISS >> Word)
		{
			Words.push_back(Word);
		}
	}

	std::vector<int32> WordWidths;
	for (const auto& Word : Words)
	{
		WordWidths.push_back(MeasureText(Word.c_str(), fontSize));
	}

	int32 CurrentX = posX;
	for (size_t i = 0; i < Words.size(); ++i)
	{
		bool bIsHighlighted = false;
		for (const int32 El : selectionNumElements)
		{
			if (El == static_cast<int>(i))
			{
				bIsHighlighted = true;
				break;
			}
		}

		const Color Color = bIsHighlighted ? subColor : mainColor;

		DrawText(Words[i].c_str(), CurrentX, posY, fontSize, Color);

		CurrentX += WordWidths[i] + MeasureText(" ", fontSize);
	}
}

#include "raylib.h"
#include <ios>
#include <sstream>

#include <Core/Utility/Draw/DrawUtility.h>

void DrawUtility::DrawTextWithOneColor(const char* Text, int PosX, int PosY, int FontSize, Color TextColor, bool bIsCenter)
{
    if (bIsCenter)
    {
        PosX -= MeasureText(Text, FontSize) / 2;
        PosY -= FontSize / 2;
    }

    DrawText(Text, PosX, PosY, FontSize, TextColor);
}

void DrawUtility::DrawTextWithTwoColor(const char* Text, int PosX, int PosY, std::vector<int> SelectionNumElements, int FontSize, Color MainColor, Color SubColor, bool bIsCenter)
{
    std::vector<std::string> Words;
    std::istringstream ISS(Text);
    std::string word;

    if (bIsCenter)
    {
        PosX -= MeasureText(Text, FontSize) / 2;
        PosY -= FontSize / 2;
    }

    while (ISS >> word) {
        Words.push_back(word);
    }

    std::vector<int> wordWidths;
    for (const auto& W : Words) {
        wordWidths.push_back(MeasureText(W.c_str(), FontSize));
    }

    int currentX = PosX;
    for (size_t i = 0; i < Words.size(); ++i)
    {
        bool isHighlighted = false;
        for (int index : SelectionNumElements) {
            if (index == static_cast<int>(i)) {
                isHighlighted = true;
                break;
            }
        }

        Color color = isHighlighted ? SubColor : MainColor;

        DrawText(Words[i].c_str(), currentX, PosY, FontSize, color);

        currentX += wordWidths[i] + MeasureText(" ", FontSize);
    }
}

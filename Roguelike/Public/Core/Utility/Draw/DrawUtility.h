#include <vector>

namespace DrawUtility
{
	void DrawTextWithOneColor(const char* Text = "Hello Roguelike", int PosX = 0, int PosY = 8, int FontSize = 24, Color TextColor = RAYWHITE, bool bIsCenter = false);
	void DrawTextWithTwoColor(const char* Text = "Hello Roguelike", int PosX = 0, int PosY = 0, std::vector<int> SelectionNumElements = { 0 }, int FontSize = 24, Color MainColor = RAYWHITE, Color SubColor = SKYBLUE, bool bIsCenter = false);


}
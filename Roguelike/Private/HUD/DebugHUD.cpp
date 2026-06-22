#include <HUD/DebugHUD.h>

#include <Core/Utility/Draw/DrawUtility.h>
#include <string>

void DebugHUD::Draw()
{

	//int fps = GetFPS();

	
	DrawUtility::DrawTextWithTwoColor(
		std::string("FPS: " + std::to_string(GetFPS())).c_str(),
		15,
		50,
		{1},
		20,
		RAYWHITE,
		GREEN);
}

void DebugHUD::Tick(float DeltaTime)
{

}

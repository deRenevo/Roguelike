// Copyright deRenevo. All rights reserved.

#pragma once

#include <memory>

class HUD;

class HUDFactory
{
	HUDFactory() = delete;

public:
	enum class EHUDList //-> All lists scene. Adding  to switch case in function class 
	{
		None,
		Debug
	};
	static std::unique_ptr<HUD> CreateHUD(EHUDList HUDId);
};
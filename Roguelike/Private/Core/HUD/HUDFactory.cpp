#pragma once

#include <Core/HUD/HUDFactory.h>
#include <Core/HUD/HUD.h>
#include <HUD/DebugHUD.h>

std::unique_ptr<HUD> HUDFactory::CreateHUD(EHUDList HUDId)
{
	switch (HUDId)
	{
	case EHUDList::None:
		return nullptr;
	case EHUDList::Debug:
		return std::make_unique<DebugHUD>();
	default:
		return nullptr;
	}
}

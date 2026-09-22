// Copyright deRenevo. All rights reserved.

#include "Core/Manager/TextureManager.h"

#include <memory>
#include <ranges>

Texture* TextureManager::LoadTexture(const std::string& texturePath)
{
	if (std::unordered_map<std::string, FTextureLoadState>::iterator It = TextureLoadMap.find(texturePath); It != TextureLoadMap.end())
	{
		++It->second.CountUsing;
		return It->second.Texture2D.get();
	}
	
	Texture Texture2D = ::LoadTexture(texturePath.c_str());
	if (!IsTextureValid(Texture2D))
	{
		return nullptr;
	}
	
	FTextureLoadState& TextureLoadState = TextureLoadMap[texturePath];
	TextureLoadState.Texture2D = std::make_unique<Texture>(Texture2D);
	++TextureLoadState.CountUsing;
	
	return TextureLoadState.Texture2D.get();
}

void TextureManager::UnloadTexture(const Texture* texture)
{
	if (!texture)
	{
		return;
	}
	
	for (std::unordered_map<std::string, FTextureLoadState>::iterator It = TextureLoadMap.begin(); It != TextureLoadMap.end(); ++It)
	{
		if (It->second.Texture2D.get() == texture)
		{
			--It->second.CountUsing;
			
			if (It->second.CountUsing <= 0)
			{
				::UnloadTexture(*It->second.Texture2D.get());
				TextureLoadMap.erase(It);
			}
			break;
		}
	}
}

void TextureManager::ClearTextureMap()
{
	for (FTextureLoadState& state : TextureLoadMap | std::views::values)
	{
		if (state.Texture2D)
		{
			::UnloadTexture(*state.Texture2D);
		}
	}
	TextureLoadMap.clear();
}

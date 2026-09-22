// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

#include <raylib.h>

#include <memory>
#include <unordered_map>

class TextureManager
{
	struct FTextureLoadState
	{
		std::unique_ptr<Texture> Texture2D = nullptr;
		uint32 CountUsing = 0;
	};
	
	std::unordered_map<std::string, FTextureLoadState> TextureLoadMap;

public:
	Texture* LoadTexture(const std::string& texturePath);
	void UnloadTexture(const Texture* texture);
	void ClearTextureMap();
	
	//getters and setters
	
	static TextureManager& GetInstance()
	{
		static TextureManager TM;
		return TM;
	}
};

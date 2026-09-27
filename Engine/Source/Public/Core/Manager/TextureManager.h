// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

#include <raylib.h>

#include <memory>
#include <atomic>
#include <unordered_map>

struct FTextureHandle
{
	uint32 Index = UINT32_MAX;
	uint32 Generation = 0;
	
	bool IsValid() const;
};

struct FTextureSlot
{
	std::unique_ptr<Texture> Texture2D;
	std::atomic<uint32> CountUsing = 0;
	uint32 Generation = 0;
	std::string TexturePath;
};

class TextureManager
{
	std::vector<std::unique_ptr<FTextureSlot>> TextureSlots;
	std::vector<uint32> FreeIndex;
	std::unordered_map<std::string, uint32> TextureIndexMap;
	
public:
	FTextureHandle LoadTexture(const std::string& texturePath);
	Texture* ResolveTexture(FTextureHandle textureHandle) const;
	void UnloadTexture(const FTextureHandle& textureHandle);
	void UnloadTextureAsync(const FTextureHandle& textureHandle);
	void FinalizeUnload(FTextureHandle textureHandle);
	void ClearTextureMap();
	
	bool IsHandleValid(const FTextureHandle& textureHandle) const
	{
		if (textureHandle.Index >= TextureSlots.size()) return false;
		return TextureSlots[textureHandle.Index]->Generation == textureHandle.Generation;
 	}
	
	//getters and setters
	
	static TextureManager& GetInstance()
	{
		static TextureManager TM;
		return TM;
	}
};

// Copyright deRenevo. All rights reserved.

#include "Core/Manager/TextureManager.h"

#include "Core/Manager/TaskQueueManager.h"

bool FTextureHandle::IsValid() const
{
	return TextureManager::GetInstance().IsHandleValid(*this);
}

FTextureHandle TextureManager::LoadTexture(const std::string& texturePath)
{
	if (const std::unordered_map<std::string, unsigned>::iterator& It = TextureIndexMap.find(texturePath); It != TextureIndexMap.end())
	{
		const uint32 Index = It->second;
		++TextureSlots[Index]->CountUsing;
		return {Index, TextureSlots[Index]->Generation};
	}

	uint32 Index;
	if (!FreeIndex.empty())
	{
		Index = FreeIndex.back();
		FreeIndex.pop_back();
	}
	else
	{
		TextureSlots.emplace_back(std::make_unique<FTextureSlot>());
		Index = static_cast<uint32>(TextureSlots.size() - 1);
	}

	Texture Texture2D = ::LoadTexture(texturePath.c_str());
	if (!IsTextureValid(Texture2D))
	{
		return {};
	}

	FTextureSlot* TextureSlot = TextureSlots[Index].get();
	TextureSlot->Texture2D = std::make_unique<Texture>(Texture2D);
	TextureSlot->CountUsing = 1;
	TextureIndexMap[texturePath] = Index;
	return {Index, TextureSlot->Generation};
}

Texture* TextureManager::ResolveTexture(const FTextureHandle textureHandle) const
{
	if (TextureSlots[textureHandle.Index]->Generation == textureHandle.Generation)
	{
		return TextureSlots[textureHandle.Index]->Texture2D.get();
	}
	return nullptr;
}

void TextureManager::UnloadTexture(const FTextureHandle& textureHandle)
{
	if (textureHandle.Index >= TextureSlots.size()) return;
	FTextureSlot* TextureSlot = TextureSlots[textureHandle.Index].get();
	if (TextureSlot->Generation != textureHandle.Generation) return;
	
	if (TextureSlot->CountUsing.fetch_sub(1) == 1)
	{
		TaskQueueManager::GetInstance().Enqueue(ETaskQueueType::Main, std::function<void()>([this, textureHandle](void)
		{
			FinalizeUnload(textureHandle);
		}));
	}
}

void TextureManager::UnloadTextureAsync(const FTextureHandle& textureHandle)
{
	TaskQueueManager::GetInstance().Enqueue(ETaskQueueType::Worker, [this, textureHandle](void)
	{
		UnloadTexture(textureHandle);
	});
}

void TextureManager::FinalizeUnload(FTextureHandle textureHandle)
{
	FTextureSlot* TextureSlot = TextureSlots[textureHandle.Index].get();
	if (TextureSlot->Generation != textureHandle.Generation) return;
	if (TextureSlot->CountUsing.load() > 0) return;

	::UnloadTexture(*TextureSlot->Texture2D);
	TextureSlot->Texture2D.reset();
	TextureIndexMap.erase(TextureSlot->TexturePath);
	TextureSlot->TexturePath.clear();

	++TextureSlot->Generation;
	FreeIndex.push_back(textureHandle.Index);
}

void TextureManager::ClearTextureMap()
{
	for (std::unique_ptr<FTextureSlot>& TextureSlot : TextureSlots)
	{
		if (TextureSlot->Texture2D)
		{
			::UnloadTexture(*TextureSlot->Texture2D);
		}
	}

	TextureSlots.clear();
	FreeIndex.clear();
	TextureIndexMap.clear();
}

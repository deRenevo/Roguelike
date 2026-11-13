// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

struct FBox2D;
class AActor;

class OComponent : public OObject
{
	bool bIsActive = true;
	bool bIsHasBeginPlay = false;
	AActor* Owner = nullptr;

protected:
	virtual void Tick(float deltaTime);

public:
	OComponent();
	explicit OComponent(AActor* owner);
	explicit OComponent(const std::string& name);
	OComponent(AActor* owner, const std::string& name);

	virtual ~OComponent() override = default;

	virtual void DoTick(float deltaTime);
	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void OnAttach();
	virtual void OnDetach();

	//setters
	virtual void SetOwner(AActor* owner)
	{
		Owner = owner;
	}

	void SetIsActive(const bool isActive)
	{
		bIsActive = isActive;
	}

	//getters
	AActor* GetOwner() const
	{
		return Owner;
	}

	bool IsActive() const
	{
		return bIsActive;
	}
};

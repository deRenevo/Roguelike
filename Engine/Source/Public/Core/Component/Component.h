// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"

struct FBox2D;
class AActor;

class OComponent : public OObject
{
	AActor* Owner = nullptr;
	bool bIsActive = true;
	bool bIsHasBeginPlay = false;

protected:
	virtual void Tick(float DeltaTime);
	virtual void Draw(const FBox2D& cameraViewportBounds);

public:
	OComponent();
	OComponent(AActor* owner);
	OComponent(const std::string& name);
	OComponent(AActor* owner, const std::string& name);

	virtual ~OComponent() override = default;

	virtual void DoTick(float DeltaTime);
	virtual void DoDraw(const FBox2D& cameraViewportBounds);
	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void OnAttach();
	virtual void OnDetach();

	//getters and setters
	virtual void SetOwner(AActor* owner)
	{
		Owner = owner;
	}

	void SetIsActive(const bool isActive)
	{
		bIsActive = isActive;
	}
	
	AActor* GetOwner() const
	{
		return Owner;
	}

	bool IsActive() const
	{
		return bIsActive;
	}


};

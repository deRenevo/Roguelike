// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Component/SceneComponent.h"
#include "Core/Math/Vector2D.h"

#include <memory>

struct FBox2D;

class AActor : public OObject
{
	bool bIsHasBeginPlay = false;
	std::unique_ptr<OSceneComponent> RootSceneComponent = nullptr;
	bool bIsTickable = true;

protected:
	virtual void PreInitializeComponents();
	virtual void InitializeComponent();
	virtual void PostInitializeComponents();

	virtual void Tick(float DeltaTime);
	virtual void Draw(const FBox2D& cameraViewportBounds);

public:
	AActor();
	AActor(const FVector2D& location);
	AActor(const std::string& name);
	AActor(const FVector2D& location, const std::string& name);

	virtual ~AActor() override;

	virtual void DoInitialize() final;

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void DoTick(float DeltaTime) final;
	virtual void DoDraw(const FBox2D& cameraViewportBounds) final;

	void SetRootSceneComponent(std::unique_ptr<OSceneComponent> rootSceneComponent);

	//setters
	void SetLocation(const FVector2D& location) const
	{
		RootSceneComponent->SetLocation(location);
	}
	
	void SetIsTickable(const bool isTickable)
	{
		bIsTickable = isTickable;
	}

	//getters
	FVector2D GetLocation() const
	{
		if (!RootSceneComponent)
		{
			return {0, 0};
		}

		return RootSceneComponent->GetWorldLocation();
	}

	OSceneComponent* GetRootSceneComponent() const
	{
		return RootSceneComponent.get();
	}
	
	bool GetIsTickable() const
	{
		return bIsTickable;
	}
};

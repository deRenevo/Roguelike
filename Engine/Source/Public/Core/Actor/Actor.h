// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Object/Object.h"
#include "Core/Component/SceneComponent.h"

#include <raylib.h>
#include <memory>

class AActor : public OObject
{
	bool bIsHasBeginPlay = false;
	std::unique_ptr<OSceneComponent> RootSceneComponent = nullptr;

protected:
	virtual void PreInitializeComponents();
	virtual void InitializeComponent();
	virtual void PostInitializeComponents();

	virtual void Tick(float DeltaTime);
	virtual void Draw();

public:
	AActor();
	AActor(const Vector2& location);
	AActor(const std::string& name);
	AActor(const Vector2& location, const std::string& name);

	virtual ~AActor() override;

	virtual void DoInitialize() final;

	virtual void BeginPlay();
	virtual void EndPlay();
	virtual void DoTick(float DeltaTime) final;
	virtual void DoDraw() final;

	void SetRootSceneComponent(std::unique_ptr<OSceneComponent> rootSceneComponent);

	//setters
	void SetLocation(const Vector2& location)
	{
		RootSceneComponent->SetLocation(location);
	}

	//getters
	Vector2 GetLocation() const
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
};

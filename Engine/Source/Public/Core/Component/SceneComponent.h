// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/Component.h"
#include "Core/Math/Vector2D.h"

#include <memory>

class OSceneComponent : public OComponent
{
	std::vector<std::unique_ptr<OComponent>> Children;
	OSceneComponent* Parent = nullptr;
	FVector2D Location = FVector2D(0, 0);

protected:
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void EndPlay() override;

	OSceneComponent();
	OSceneComponent(const std::string& name);
	OSceneComponent(AActor* owner);
	OSceneComponent(AActor* owner, const FVector2D& location);
	OSceneComponent(const FVector2D& location, const std::string& name);
	OSceneComponent(AActor* owner, const FVector2D& location, const std::string& name);

	virtual ~OSceneComponent() override;

	void SetLocation(const FVector2D& location);
	void AddChild(std::unique_ptr<OComponent> child);
	void RemoveChild(OComponent* child);

	//setters
	void SetParent(OSceneComponent* parent)
	{
		Parent = parent;
	}

	//getters
	FVector2D GetLocation() const
	{
		return Location;
	}

	FVector2D GetWorldLocation() const
	{
		if (Parent)
		{
			const FVector2D ParentLocation = Parent->GetWorldLocation();
			return {ParentLocation.X + Location.X, ParentLocation.Y + Location.Y};
		}

		return Location;
	}

	OSceneComponent* GetParent() const
	{
		return Parent;
	}
};

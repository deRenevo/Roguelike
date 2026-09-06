// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Component/Component.h"

#include <raylib.h>
#include <memory>


class OSceneComponent : public OComponent
{
	std::vector<std::unique_ptr<OComponent>> Children;
	OSceneComponent* Parent = nullptr;
	Vector2 Location = Vector2(0, 0);

protected:
	virtual void Draw() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void EndPlay() override;

	OSceneComponent();
	OSceneComponent(const std::string& name);
	OSceneComponent(AActor* owner);
	OSceneComponent(AActor* owner, const Vector2& location);
	OSceneComponent(const Vector2& location, const std::string& name);
	OSceneComponent(AActor* owner, const Vector2& location, const std::string& name);

	virtual ~OSceneComponent() override;

	void SetLocation(const Vector2& location);
	void AddChild(std::unique_ptr<OComponent> child);
	void RemoveChild(OComponent* child);

	//setters
	void SetParent(OSceneComponent* parent)
	{
		Parent = parent;
	}

	//getters
	Vector2 GetLocation() const
	{
		return Location;
	}

	Vector2 GetWorldLocation() const
	{
		if (Parent)
		{
			const Vector2 ParentLocation = Parent->GetWorldLocation();
			return {ParentLocation.x + Location.x, ParentLocation.y + Location.y};
		}

		return Location;
	}

	OSceneComponent* GetParent() const
	{
		return Parent;
	}
};

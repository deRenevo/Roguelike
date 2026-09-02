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

	OSceneComponent(const std::string& name);
	OSceneComponent();
	virtual  ~OSceneComponent() override;

	void SetLocation(const Vector2& location);
	void AddChild(std::unique_ptr<OComponent> child);
	void RemoveChild(OComponent* child);
	void SetParent(OSceneComponent* parent);

	Vector2 GetLocation() const;
	Vector2 GetWorldLocation() const;
	OSceneComponent* GetParent() const;
};

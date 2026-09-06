// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Widget/Widget.h"

#include <vector>
#include <memory>

class WContainer : public WWidget
{
	std::vector<std::unique_ptr<WWidget>> Children;

public:
	WContainer() = default;
	virtual ~WContainer() override = default;

	virtual void OnExit() override; // -> Cleaning up resources
	
protected:
	virtual void Construction() override;

	virtual void Tick(float DeltaTime) override; //-> every frame is processed
	virtual void Draw() override;

	virtual void OnChildAdded(WWidget* widget);

public:
	void AddChild(std::unique_ptr<WWidget> widget);
	void RemoveChild(WWidget* widget);
	void ClearChildren();
};

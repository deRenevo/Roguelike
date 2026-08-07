// Copyright deRenevo. All rights reserved.

#pragma once

#include <Core/Widgets/WidgetsElements/Widget.h>
#include <vector>
#include <memory>

class WContainer : public WWidget
{
	std::vector<std::unique_ptr<WWidget>> Children;
	
public:
	virtual ~WContainer() = default;
	WContainer() = default;


	virtual void OnExit() override; // -> Cleaning up resources
	virtual void Tick(float DeltaTime) override; //-> every frame is processed
	virtual void Draw() override;

protected:
	virtual void Construction() override;
	virtual void OnChildAdded(WWidget* widget);

public:
	/*
	 * =>getter and setter
	*/

	void AddChild(std::unique_ptr<WWidget> widget);
	void RemoveChild(WWidget* widget);
	void ClearChildren();
};
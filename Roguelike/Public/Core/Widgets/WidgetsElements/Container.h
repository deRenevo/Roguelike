#pragma once

#include <Core/Widgets/WidgetsElements/Widget.h>
#include <vector>
#include <memory>

class Container : public Widget
{
	std::vector<std::unique_ptr<Widget>> Children;
	
public:
	virtual ~Container() = default;
	Container() = default;


	virtual void OnExit() override; // -> Cleaning up resources
	virtual void Tick(float DeltaTime) override; //-> every frame is processed
	virtual void Draw() override;

protected:
	virtual void Construction() override;
	virtual void OnChildAdded(Widget* widget);

public:
	/*
	 * =>getter and setter
	*/

	void AddChild(std::unique_ptr<Widget> widget);
	void RemoveChild(Widget* widget);
	void ClearChildren();
};
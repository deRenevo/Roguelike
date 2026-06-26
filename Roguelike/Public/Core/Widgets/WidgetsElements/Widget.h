#pragma once

#include "raylib.h"

class Widget
{
	Rectangle Bound;
	Widget* Parent = nullptr;
	bool bIsVisible = true;

public:
	Widget() = default; 
	virtual ~Widget() = default;

	void OnEnter(); // -> Loading resources
	virtual void OnExit(); // -> Cleaning up resources
	virtual void DoTick(float DeltaTime) final; //-> every frame is processed
	virtual void DoDraw() final;

protected:
	virtual void Construction() = 0; //-> processed when changing priced
	virtual void Draw();
	virtual void Tick(float DeltaTime); //-> every frame is processed

	/*
	 * => getter and setter
	*/

public:
	void SetWorldLocation(Vector2 location);
	void SetLocalLocation(Vector2 location);
	void SetVisible(bool isVisible);
	void SetSize(Vector2 size);
	void SetParent(Widget* parent);
	void SetBound(Rectangle bound);
	
	
	Rectangle GetLocalBound();
	Rectangle GetWorldBound();
	Widget* GetParent();
	Vector2 GetWorldLocation();
	Vector2 GetLocalLocation();
	Vector2 GetSize();
	bool GetVisible();
};
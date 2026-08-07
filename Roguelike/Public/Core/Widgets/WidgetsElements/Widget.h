#pragma once

#include <Core/Utility/Struct.h>

#include "raylib.h"

struct FWidgetStyle
{
	EWidgetVerticalAlignment WidgetVerticalAlignment = EWidgetVerticalAlignment::Top;
	EWidgetHorizontalAlignment WidgetHorizontalAlignment = EWidgetHorizontalAlignment::Left;
};

class WWidget
{
	Rectangle Bound;
	WWidget* Parent = nullptr;
	bool bIsVisible = true;
	bool bIsAutoSize = false;

	FWidgetStyle WidgetStyle = FWidgetStyle();

public:
	WWidget() = default; 
	virtual ~WWidget() = default;

	void OnEnter(); // -> Loading resources
	virtual void OnExit(); // -> Cleaning up resources
	virtual void DoTick(float DeltaTime) final; //-> every frame is processed
	virtual void DoDraw() final;

protected:
	virtual void Construction() = 0; //-> processed when changing priced
	virtual void Draw();
	virtual void Tick(float DeltaTime); //-> every frame is processed
	virtual Vector2 AutoSize();

	/*
	 * => getter and setter
	*/

public:
	void SetWorldLocation(Vector2 location);
	void SetLocalLocation(Vector2 location);
	void SetVisible(bool isVisible);
	void SetSize(Vector2 size);
	void SetParent(WWidget* parent);
	void SetBound(Rectangle bound);
	void SetAutoSize(bool autoSize);
	void SetWidgetSyle(FWidgetStyle widgetStyle);
	
	
	Rectangle GetLocalBound();
	Rectangle GetWorldBound();
	WWidget* GetParent();
	Vector2 GetWorldLocation();
	Vector2 GetLocalLocation();
	virtual Vector2 GetSize();

	virtual Vector2 GetWorldWidgetLocationWithAlignment();
	virtual Rectangle GetWorldBoundWithAlignment();

	bool GetVisible();
};
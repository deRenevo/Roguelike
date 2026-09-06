// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Utility/Struct.h"
#include "Core/Object/Object.h"

struct FWidgetStyle
{
	EWidgetVerticalAlignment WidgetVerticalAlignment = EWidgetVerticalAlignment::Top;
	EWidgetHorizontalAlignment WidgetHorizontalAlignment = EWidgetHorizontalAlignment::Left;
};

class WWidget : public OObject
{
	Rectangle Bound;
	WWidget* Parent = nullptr;
	bool bIsVisible = true;
	bool bIsAutoSize = false;

	FWidgetStyle WidgetStyle = FWidgetStyle();

public:
	WWidget() = default;
	virtual ~WWidget() override = default;

	void OnEnter(); // -> Loading resources
	virtual void OnExit(); // -> Cleaning up resources
	virtual void DoTick(float DeltaTime) final; //-> every frame is processed
	virtual void DoDraw() final;

protected:
	virtual void Construction() = 0; //-> processed when changing priced
	virtual void Draw();
	virtual void Tick(float DeltaTime); //-> every frame is processed
	virtual Vector2 AutoSize();

public:
	//setters
	void SetWorldLocation(Vector2 location)
	{
		if (Parent)
		{
			Bound.x = location.x - Parent->GetWorldLocation().x;
			Bound.y = location.y - Parent->GetWorldLocation().y;
		}
		else
		{
			Bound.x = location.x;
			Bound.y = location.y;
		}
	}

	void SetLocalLocation(Vector2 location)
	{
		Bound.x = location.x;
		Bound.y = location.y;
	}

	void SetVisible(bool isVisible)
	{
		bIsVisible = isVisible;
	}

	void SetSize(Vector2 size)
	{
		bIsAutoSize = false;
		Bound.width = size.x;
		Bound.height = size.y;
	}

	void SetParent(WWidget* parent)
	{
		Parent = parent;
	}

	void SetBound(Rectangle bound)
	{
		Bound = bound;
	}

	void SetAutoSize(bool autoSize)
	{
		bIsAutoSize = autoSize;
		if (bIsAutoSize)
		{
			Vector2 Size = AutoSize();
			Bound.width = Size.x;
			Bound.height = Size.y;
		}
	}

	void SetWidgetStyle(FWidgetStyle widgetStyle)
	{
		WidgetStyle = widgetStyle;
	}

	//getters
	virtual Vector2 GetWorldWidgetLocationWithAlignment();

	Rectangle GetLocalBound() const
	{
		return Bound;
	}

	Rectangle GetWorldBound() const
	{
		return Rectangle(GetWorldLocation().x, GetWorldLocation().y, Bound.width, Bound.height);
	}

	WWidget* GetParent() const
	{
		return Parent;
	}

	Vector2 GetWorldLocation() const
	{
		if (Parent)
		{
			return Vector2(
				Parent->GetWorldLocation().x + Bound.x,
				Parent->GetWorldLocation().y + Bound.y
			);
		}
		return Vector2(Bound.x, Bound.y);
	}

	Vector2 GetLocalLocation() const
	{
		return Vector2(Bound.x, Bound.y);
	}

	virtual Vector2 GetSize()
	{
		return Vector2(Bound.width, Bound.height);
	}

	virtual Rectangle GetWorldBoundWithAlignment()
	{
		Rectangle Bound = GetWorldBound();
		Vector2 Location = GetWorldWidgetLocationWithAlignment();

		Bound.x = Location.x;
		Bound.y = Location.y;
		return Bound;
	}

	bool GetVisible() const
	{
		return bIsVisible;
	}
};

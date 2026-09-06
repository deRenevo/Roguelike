// Copyright deRenevo. All rights reserved.

#pragma once

#include "Core/Math/Vector2D.h"
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
	virtual FVector2D AutoSize();

public:
	//setters
	void SetWorldLocation(FVector2D location)
	{
		if (Parent)
		{
			Bound.x = location.X - Parent->GetWorldLocation().X;
			Bound.y = location.Y - Parent->GetWorldLocation().Y;
		}
		else
		{
			Bound.x = location.X;
			Bound.y = location.Y;
		}
	}

	void SetLocalLocation(FVector2D location)
	{
		Bound.x = location.X;
		Bound.y = location.Y;
	}

	void SetVisible(bool isVisible)
	{
		bIsVisible = isVisible;
	}

	void SetSize(FVector2D size)
	{
		bIsAutoSize = false;
		Bound.width = size.X;
		Bound.height = size.Y;
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
			FVector2D Size = AutoSize();
			Bound.width = Size.X;
			Bound.height = Size.Y;
		}
	}

	void SetWidgetStyle(FWidgetStyle widgetStyle)
	{
		WidgetStyle = widgetStyle;
	}

	//getters
	virtual FVector2D GetWorldWidgetLocationWithAlignment();

	Rectangle GetLocalBound() const
	{
		return Bound;
	}

	Rectangle GetWorldBound() const
	{
		return Rectangle(GetWorldLocation().X, GetWorldLocation().Y, Bound.width, Bound.height);
	}

	WWidget* GetParent() const
	{
		return Parent;
	}

	FVector2D GetWorldLocation() const
	{
		if (Parent)
		{
			return FVector2D(
				Parent->GetWorldLocation().X + Bound.x,
				Parent->GetWorldLocation().Y + Bound.y
			);
		}
		return FVector2D(Bound.x, Bound.y);
	}

	FVector2D GetLocalLocation() const
	{
		return FVector2D(Bound.x, Bound.y);
	}

	virtual FVector2D GetSize()
	{
		return FVector2D(Bound.width, Bound.height);
	}

	virtual Rectangle GetWorldBoundWithAlignment()
	{
		Rectangle Bound = GetWorldBound();
		FVector2D Location = GetWorldWidgetLocationWithAlignment();

		Bound.x = Location.X;
		Bound.y = Location.Y;
		return Bound;
	}

	bool GetVisible() const
	{
		return bIsVisible;
	}
};

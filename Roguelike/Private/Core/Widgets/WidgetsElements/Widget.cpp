// Copyright deRenevo. All rights reserved.

#include "Core/Widgets/WidgetsElements/Widget.h"

#include <iostream>

void WWidget::OnEnter()
{
	Construction();
}

void WWidget::OnExit()
{
	SetIsPendingKill();
}

void WWidget::Tick(float DeltaTime)
{

}

Vector2 WWidget::AutoSize()
{
	return Vector2(0, 0);
}

void WWidget::Draw()
{

}

void WWidget::DoTick(float DeltaTime)
{
	if (GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Tick(DeltaTime);
}

void WWidget::DoDraw()
{
	if (GetIsPendingKill()) return; // if sttarting process deleting object thet stop Function 
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Draw();
}

/*
 * => setter and getter
*/

void WWidget::SetWorldLocation(Vector2 location)
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

void WWidget::SetLocalLocation(Vector2 location)
{
	Bound.x = location.x;
	Bound.y = location.y;
}

void WWidget::SetVisible(bool isVisible)
{
	bIsVisible = isVisible;
}

void WWidget::SetSize(Vector2 size)
{
	bIsAutoSize = false;
	Bound.width = size.x;
	Bound.height = size.y;
}

void WWidget::SetParent(WWidget* parent)
{
	Parent = parent;
}

void WWidget::SetBound(Rectangle bound)
{
	std::cout << "SetBound called: x=" << bound.x
		<< " y=" << bound.y
		<< " w=" << bound.width
		<< " h=" << bound.height << std::endl;

	Bound = bound;
}

void WWidget::SetAutoSize(bool autoSize)
{
	bIsAutoSize = autoSize;
	if (bIsAutoSize)
	{
		Vector2 Size = AutoSize();
		Bound.width = Size.x;
		Bound.height = Size.y;
	}
}

void WWidget::SetWidgetSyle(FWidgetStyle widgetStyle)
{
	WidgetStyle = widgetStyle;
}


Rectangle WWidget::GetLocalBound()
{
	return Bound;
}

Rectangle WWidget::GetWorldBound()
{
	return Rectangle(GetWorldLocation().x, GetWorldLocation().y, Bound.width, Bound.height);
}

WWidget* WWidget::GetParent()
{
	return Parent;
}

Vector2 WWidget::GetWorldLocation()
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

Vector2 WWidget::GetLocalLocation()
{
	return Vector2(Bound.x, Bound.y);
}

Vector2 WWidget::GetSize()
{
	return Vector2(Bound.width, Bound.height);
}

Vector2 WWidget::GetWorldWidgetLocationWithAlignment()
{
	Vector2 Size = GetSize();
	Vector2 Location = GetWorldLocation();
	Vector2 AlignmentLocation;

	switch (WidgetStyle.WidgetVerticalAlignment)
	{
	case EWidgetVerticalAlignment::Top:
		AlignmentLocation.y = Location.y;
		break;
	case EWidgetVerticalAlignment::Center:
		AlignmentLocation.y = Location.y - Size.y / 2;
		break;
	case EWidgetVerticalAlignment::Bottom:
		AlignmentLocation.y = Location.y - Size.y;
		break;
	}

	switch (WidgetStyle.WidgetHorizontalAlignment)
	{
	case EWidgetHorizontalAlignment::Left:
		AlignmentLocation.x = Location.x;
		break;

	case EWidgetHorizontalAlignment::Center:
		AlignmentLocation.x = Location.x - Size.x / 2;
		break;

	case EWidgetHorizontalAlignment::Right:
		AlignmentLocation.x = Location.x - Size.x;
		break;
	}
	return AlignmentLocation;
}

Rectangle WWidget::GetWorldBoundWithAlignment()
{
	Rectangle Bound = GetWorldBound();
	Vector2 Location = GetWorldWidgetLocationWithAlignment();

	Bound.x = Location.x;
	Bound.y = Location.y;
	return Bound;
}


bool WWidget::GetVisible()
{
	return bIsVisible;
}

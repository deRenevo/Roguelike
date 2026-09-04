// Copyright deRenevo. All rights reserved.

#include "Core/Widgets/WidgetsElements/Widget.h"

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
	if (GetIsPendingKill()) return; // if starting process deleting object thet stop Function 
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Tick(DeltaTime);
}

void WWidget::DoDraw()
{
	if (GetIsPendingKill()) return; // if starting process deleting object thet stop Function 
	if (!bIsVisible) return; // then remove to Enum class with Widget state
	Draw();
}

Vector2 WWidget::GetWorldWidgetLocationWithAlignment()
{
	Vector2 Size = GetSize();
	Vector2 Location = GetWorldLocation();
	Vector2 AlignmentLocation = {};

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

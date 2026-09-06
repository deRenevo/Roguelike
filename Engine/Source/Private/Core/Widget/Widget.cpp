// Copyright deRenevo. All rights reserved.

#include "Core/Widget/Widget.h"

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

FVector2D WWidget::AutoSize()
{
	return FVector2D(0, 0);
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

FVector2D WWidget::GetWorldWidgetLocationWithAlignment()
{
	FVector2D Size = GetSize();
	FVector2D Location = GetWorldLocation();
	FVector2D AlignmentLocation = {};

	switch (WidgetStyle.WidgetVerticalAlignment)
	{
	case EWidgetVerticalAlignment::Top:
		AlignmentLocation.Y= Location.Y;
		break;
	case EWidgetVerticalAlignment::Center:
		AlignmentLocation.Y = Location.Y - Size.Y / 2;
		break;
	case EWidgetVerticalAlignment::Bottom:
		AlignmentLocation.Y = Location.Y - Size.Y;
		break;
	}

	switch (WidgetStyle.WidgetHorizontalAlignment)
	{
	case EWidgetHorizontalAlignment::Left:
		AlignmentLocation.X = Location.X;
		break;

	case EWidgetHorizontalAlignment::Center:
		AlignmentLocation.X = Location.X - Size.X / 2;
		break;

	case EWidgetHorizontalAlignment::Right:
		AlignmentLocation.X = Location.X - Size.X;
		break;
	}
	return AlignmentLocation;
}

// Copyright deRenevo. All rights reserved.

#pragma once
#include "Vector2D.h"


struct FBox2D
{
	FVector2D Location = FVector2D::ZeroVector; // Location is center
	FVector2D Size = FVector2D::ZeroVector; //X == Width Y == Height 

	constexpr FBox2D() = default;

	constexpr FBox2D(const FVector2D& location, const FVector2D& size)
		: Location(location), Size(size)
	{
	}

	constexpr FVector2D Max() const
	{
		return {Location.X + Size.X / 2, Location.Y + Size.Y / 2};
	}

	constexpr FVector2D Min() const
	{
		return {Location.X - Size.X / 2, Location.Y - Size.Y / 2};
	}

	constexpr FVector2D Extent() const
	{
		return {Size.X / 2, Size.Y / 2};
	}
	
	constexpr FVector2D Center() const
	{
		return Location;
	}

	constexpr void SetCenter(const FVector2D& center)
	{
		Location = center;
	}

	constexpr void SetExtent(const FVector2D& extent)
	{
		Size = {extent.X * 2, extent.Y * 2};
	}

	constexpr void SetSize(const FVector2D& size)
	{
		Size = {std::max(0.0f, size.X), std::max(0.0f, size.Y)};
	}
};

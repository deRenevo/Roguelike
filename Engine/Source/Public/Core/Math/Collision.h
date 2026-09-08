// Copyright deRenevo. All rights reserved.

#pragma once

#include <algorithm>

#include "Core/Math/Box2D.h"
#include "Core/Math/Vector2D.h"

namespace CollisionMath
{
	constexpr bool Intersect(const FBox2D& box2D1, const FBox2D& box2D2)
	{
		const FVector2D Delta = box2D2.Center() - box2D1.Center();
		const FVector2D SumExtent = box2D1.Extent() + box2D2.Extent();
		return std::abs(Delta.X) < SumExtent.X &&
			std::abs(Delta.Y) < SumExtent.Y;
	}

	constexpr bool Contain(const FBox2D& box2D, const FVector2D& point)
	{
		const FVector2D Delta = FVector2D::Abs(point - box2D.Center());
		const FVector2D Extent = box2D.Extent();
		return Delta.X <= Extent.X && Delta.Y <= Extent.Y;
	}

	constexpr FVector2D ClosestPoint(const FBox2D& box, const FVector2D& point)
	{
		const FVector2D min = box.Min();
		const FVector2D max = box.Max();

		return {
			std::clamp(point.X, min.X, max.X),
			std::clamp(point.Y, min.Y, max.Y)
		};
	}

	constexpr FVector2D MTV(const FBox2D& box2D1, const FBox2D& box2D2)
	{
		const FVector2D Delta = box2D2.Center() - box2D1.Center();
		const FVector2D SumExtent = box2D1.Extent() + box2D2.Extent();
		const FVector2D Overlap = SumExtent - FVector2D::Abs(Delta);

		if (Overlap.X <= 0.0f || Overlap.Y <= 0.0f)
		{
			return {0, 0};
		}

		if (Overlap.X < Overlap.Y)
		{
			const float Sign = (Delta.X > 0.0f) ? 1.0f : -1.0f;
			return {Overlap.X * Sign, 0.0};
		}
		else
		{
			const float Sign = (Delta.Y > 0.0f) ? 1.0f : -1.0f;
			return {0.f, Overlap.Y * Sign};
		}
	}
}

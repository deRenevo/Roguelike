// Copyright deRenevo. All rights reserved.

#pragma once

#include <cmath>
#include <limits>

#include "raylib.h"

struct FVector2D
{
	float X, Y;

	constexpr FVector2D(const float x, const float y) : X(x), Y(y)
	{
	}

	constexpr FVector2D() noexcept : X(0.0f), Y(0.0f)
	{
	}

	constexpr FVector2D(const Vector2& rayVector2) : X(rayVector2.x), Y(rayVector2.y)
	{
	}

	constexpr operator Vector2() const
	{
		return {X, Y};
	}

	static const FVector2D ZeroVector;
	static const FVector2D OneVector;
	static const FVector2D MaxVector;

	constexpr FVector2D operator+(const FVector2D& vector2D) const
	{
		return FVector2D(X + vector2D.X, Y + vector2D.Y);
	}

	constexpr FVector2D operator-(const FVector2D& vector2D) const
	{
		return FVector2D(X - vector2D.X, Y - vector2D.Y);
	}

	constexpr FVector2D operator*(const FVector2D& vector2D) const
	{
		return FVector2D(X * vector2D.X, Y * vector2D.Y);
	}

	constexpr FVector2D operator/(const FVector2D& vector2D) const
	{
		return FVector2D(X / vector2D.X, Y / vector2D.Y);
	}

	constexpr FVector2D& operator+=(const FVector2D& vector2D)
	{
		X += vector2D.X;
		Y += vector2D.Y;
		return *this;
	}

	constexpr FVector2D& operator-=(const FVector2D& vector2D)
	{
		X -= vector2D.X;
		Y -= vector2D.Y;
		return *this;
	}

	constexpr FVector2D& operator*=(const FVector2D& vector2D)
	{
		X *= vector2D.X;
		Y *= vector2D.Y;
		return *this;
	}

	constexpr FVector2D& operator/=(const FVector2D& vector2D)
	{
		X /= vector2D.X;
		Y /= vector2D.Y;
		return *this;
	}

	constexpr FVector2D operator+(const float& scalar) const
	{
		return FVector2D(X + scalar, Y + scalar);
	}

	constexpr FVector2D operator-(const float& scalar) const
	{
		return FVector2D(X - scalar, Y - scalar);
	}

	constexpr FVector2D operator*(const float& scalar) const
	{
		return FVector2D(X * scalar, Y * scalar);
	}

	constexpr FVector2D operator/(const float& scalar) const
	{
		return FVector2D(X / scalar, Y / scalar);
	}

	constexpr FVector2D& operator+=(const float& scalar)
	{
		X += scalar;
		Y += scalar;
		return *this;
	}

	constexpr FVector2D& operator-=(const float& scalar)
	{
		X -= scalar;
		Y -= scalar;
		return *this;
	}

	constexpr FVector2D& operator*=(const float& scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	constexpr FVector2D& operator/=(const float& scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	constexpr FVector2D operator-() const
	{
		return {-X, -Y};
	}

	constexpr bool operator==(const FVector2D& other) const
	{
		return X == other.X && Y == other.Y;
	}

	constexpr bool operator!=(const FVector2D& other) const
	{
		return !(*this == other);
	}

	static constexpr FVector2D Abs(const FVector2D& vector2D)
	{
		return {std::abs(vector2D.X), std::abs(vector2D.Y)};
	}

	static constexpr float Distance(const FVector2D& vector2D1, const FVector2D& vector2D2)
	{
		return std::hypot(vector2D1.X - vector2D2.X, vector2D1.Y - vector2D2.Y);
	}

	static constexpr float DistanceSquared(const FVector2D& vector2D1, const FVector2D& vector2D2)
	{
		float DX = vector2D1.X - vector2D2.X;
		float DY = vector2D1.Y - vector2D2.Y;
		return DX * DX + DY * DY;
	}

	constexpr bool Equals(const FVector2D& other, float epsilon = 1e-6f) const
	{
		return std::abs(X - other.X) <= epsilon
			&& std::abs(Y - other.Y) <= epsilon;
	}

	constexpr float Length() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	constexpr float LengthSquared() const
	{
		return X * X + Y * Y;
	}

	constexpr FVector2D Normalized() const
	{
		const float Len = Length();
		if (Len < 1e-8f) return FVector2D::ZeroVector;
		return FVector2D(X / Len, Y / Len);
	}

	constexpr FVector2D GetSafeNormal(float tolerance = 1e-8f) const
	{
		const float Sqrt = LengthSquared();
		if (Sqrt < tolerance) return FVector2D::ZeroVector;
		const float inv = 1.0f / std::sqrt(Sqrt);
		return {X * inv, Y * inv};
	}

	static constexpr float Dot(const FVector2D& vector2D1, const FVector2D& vector2D2)
	{
		return vector2D1.X * vector2D2.X + vector2D1.Y * vector2D2.Y;
	}
	
	static constexpr float Cross(const FVector2D& vector2D1, const FVector2D& vector2D2)
	{
		return vector2D1.X * vector2D2.Y - vector2D1.Y * vector2D2.X;
	}
};

inline const FVector2D FVector2D::ZeroVector{0.f, 0.f};
inline const FVector2D FVector2D::OneVector{1.f, 1.f};
inline const FVector2D FVector2D::MaxVector{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

constexpr FVector2D operator+(const float scalar, const FVector2D& vector2D)
{
	return vector2D + scalar;
}

constexpr FVector2D operator*(const float scalar, const FVector2D& vector2D)
{
	return vector2D * scalar;
}

constexpr FVector2D operator-(const float scalar, const FVector2D& vector2D)
{
	return FVector2D(scalar - vector2D.X, scalar - vector2D.Y);
}

constexpr FVector2D operator/(const float scalar, const FVector2D& vector2D)
{
	return FVector2D(scalar / vector2D.X, scalar / vector2D.Y);
}

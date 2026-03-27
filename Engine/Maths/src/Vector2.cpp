/*****************************************************************************
 * Vector2
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Vector2.h"

#include <cassert>
#include <format>

#include "CatalystMath.h"
#include "Vector3.h"
#include "Vector4.h"

#define VECTOR_2_SIZE 2

using std::runtime_error;

namespace Catalyst::Math
{
	const Vector2 Vector2::ZERO  = Vector2{ 0.f };
	const Vector2 Vector2::ONE   = Vector2{ 1.f };
	const Vector2 Vector2::HALF  = Vector2{ .5f };
	const Vector2 Vector2::UP    = Vector2{ 0.f, 1.f };
	const Vector2 Vector2::DOWN  = Vector2{ 0.f, -1.f };
	const Vector2 Vector2::LEFT  = Vector2{ -1.f, 0.f };
	const Vector2 Vector2::RIGHT = Vector2{ 1.f, 0.f };

	float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.Dot(rhs);
	}

	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, const float t)
	{
		return a * (1 - t) + b * t;
	}

	float Vector2::AngleBetween(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.AngleBetween(rhs);
	}

	float Vector2::Distance(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.Distance(rhs);
	}

	Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.Min(rhs);
	}

	Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.Max(rhs);
	}

	Vector2 Vector2::Abs(const Vector2& vec)
	{
		return vec.Abs();
	}

	Vector2 Vector2::Clamp(const Vector2& val, const Vector2& min, const Vector2& max)
	{
		return val.Clamp(min, max);
	}

	Vector2 Vector2::Reflect(const Vector2& vec, const Vector2& normal)
	{
		return vec.Reflect(normal);
	}

	Vector2 Vector2::Project(const Vector2& vec, const Vector2& onto)
	{
		return vec.Project(onto);
	}

	Vector2::Vector2()
		: x{ 0.f }, y{ 0.f } { }

	Vector2::Vector2(const float scalar)
		: x{ scalar }, y{ scalar } { }

	Vector2::Vector2(const Vector3& xyz)
		: x{ xyz.x }, y{ xyz.y } { }

	Vector2::Vector2(const Vector4& xyzw)
		: x{ xyzw.x }, y{ xyzw.y } { }

	Vector2::Vector2(const float x, const float y)
		: x{ x }, y{ y } { }

	Vector2::Vector2(const vec2& rhs)
		: x{ rhs.x }, y{ rhs.y } { }

	Vector2::Vector2(const Vector2& rhs) = default;

	float Vector2::Dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	float Vector2::Length() const
	{
		return CatalystMath::Sqrt(LengthSqr());
	}

	float Vector2::LengthSqr() const
	{
		return x * x + y * y;
	}

	void Vector2::Normalize()
	{
		float len = Length();

		if (CatalystMath::Approximately(len, 0.f))
		{
			x = 0.f;
			y = 0.f;
		}
		else
		{
			x /= len;
			y /= len;
		}
	}

	Vector2 Vector2::Normalized() const
	{
		const float len = Length();

		return CatalystMath::Approximately(len, 0.f) ? Vector2{ 0.f, 0.f } : Vector2{ x / len, y / len };
	}

	bool Vector2::IsApproximatelyEqual(const Vector2& rhs, const float e) const
	{
		for (int i = 0; i < VECTOR_2_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], rhs[i], e))
			{
				return false;
			}
		}

		return true;
	}

	float Vector2::AngleBetween(const Vector2& rhs) const
	{
		const float num = Dot(rhs);
		const float den = Length() * rhs.Length();

		return CatalystMath::Acos(num / den);
	}

	float Vector2::Distance(const Vector2& rhs) const
	{
		return (*this - rhs).Length();
	}

	Vector2 Vector2::Min(const Vector2& rhs) const
	{
		return
		{
			CatalystMath::Min(x, rhs.x),
			CatalystMath::Min(y, rhs.y)
		};
	}

	Vector2 Vector2::Max(const Vector2& rhs) const
	{
		return
		{
			CatalystMath::Max(x, rhs.x),
			CatalystMath::Max(y, rhs.y)
		};
	}

	Vector2 Vector2::Abs() const
	{
		return
		{
			CatalystMath::Abs(x),
			CatalystMath::Abs(y)
		};
	}

	Vector2 Vector2::Clamp(const Vector2& min, const Vector2& max) const
	{
		return
		{
			CatalystMath::Clamp(x, min.x, max.x),
			CatalystMath::Clamp(y, min.y, max.y)
		};
	}

	Vector2 Vector2::Reflect(const Vector2& normal) const
	{
		return *this - normal * (2.f * this->Dot(normal));
	}

	Vector2 Vector2::Project(const Vector2& onto) const
	{
		return onto * (this->Dot(onto) / onto.Dot(onto));
	}

	ostream& operator<<(ostream& stream, const Vector2& vec)
	{
		stream << std::format("({:.2f}, {:.2f})", vec.x, vec.y);

		return stream;
	}

	Vector2::operator vec2() const
	{
		return { x, y };
	}

	Vector2::operator Vector3() const
	{
		return { x, y, 0.f };
	}

	Vector2::operator Vector4() const
	{
		return { x, y, 0.f, 0.f };
	}

	Vector2& Vector2::operator=(const Vector2& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		x = rhs.x;
		y = rhs.y;

		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2{ -x, -y };
	}

	bool Vector2::operator==(const Vector2& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		return IsApproximatelyEqual(rhs);
	}

	bool Vector2::operator!=(const Vector2& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !IsApproximatelyEqual(rhs);
	}

	bool Vector2::operator<(const Vector2& rhs) const
	{
		return LengthSqr() < rhs.LengthSqr();
	}

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return Vector2{ x + rhs.x, y + rhs.y };
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return Vector2{ x - rhs.x, y - rhs.y };
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Vector2 Vector2::operator*(const Vector2& rhs) const
	{
		return Vector2{ x * rhs.x, y * rhs.y };
	}

	Vector2& Vector2::operator*=(const Vector2& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector2 Vector2::operator*(const float rhs) const
	{
		return Vector2{ x * rhs, y * rhs };
	}

	Vector2& Vector2::operator*=(const float rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector2 Vector2::operator/(const float rhs) const
	{
		return Vector2{ x / rhs, y / rhs };
	}

	Vector2& Vector2::operator/=(const float rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	float& Vector2::operator[](int index)
	{
		assert(index >= 0 && index < VECTOR_2_SIZE);

		switch (index)
		{
			case 0:
			{
				return x;
			}

			case 1:
			{
				return y;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}

	const float& Vector2::operator[](int index) const
	{
		assert(index >= 0 && index < VECTOR_2_SIZE);

		switch (index)
		{
			case 0:
			{
				return x;
			}

			case 1:
			{
				return y;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}
}

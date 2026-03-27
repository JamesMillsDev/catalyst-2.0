/*****************************************************************************
 * Vector3
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Vector3.h"

#include <cassert>
#include <format>

#include "CatalystMath.h"
#include "Vector2.h"
#include "Vector4.h"

#define VECTOR_3_SIZE 3

using std::runtime_error;

namespace Catalyst::Math
{
	const Vector3 Vector3::ZERO    = Vector3{ 0.f };
	const Vector3 Vector3::ONE     = Vector3{ 1.f };
	const Vector3 Vector3::HALF    = Vector3{ .5f };
	const Vector3 Vector3::UP      = Vector3{ 0.f, 1.f, 0.f };
	const Vector3 Vector3::DOWN    = Vector3{ 0.f, -1.f, 0.f };
	const Vector3 Vector3::LEFT    = Vector3{ -1.f, 0.f, 0.f };
	const Vector3 Vector3::RIGHT   = Vector3{ 1.f, 0.f, 0.f };
	const Vector3 Vector3::FORWARD = Vector3{ 0.f, 0.f, 1.f };
	const Vector3 Vector3::BACK    = Vector3{ 0.f, 0.f, -1.f };

	float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.Dot(rhs);
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.Cross(rhs);
	}

	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, const float t)
	{
		return a * (1 - t) + b * t;
	}

	float Vector3::AngleBetween(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.AngleBetween(rhs);
	}

	float Vector3::Distance(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.Distance(rhs);
	}

	Vector3 Vector3::Min(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.Min(rhs);
	}

	Vector3 Vector3::Max(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.Max(rhs);
	}

	Vector3 Vector3::Abs(const Vector3& vec)
	{
		return vec.Abs();
	}

	Vector3 Vector3::Clamp(const Vector3& val, const Vector3& min, const Vector3& max)
	{
		return val.Clamp(min, max);
	}

	Vector3 Vector3::Reflect(const Vector3& vec, const Vector3& normal)
	{
		return vec.Reflect(normal);
	}

	Vector3 Vector3::Project(const Vector3& vec, const Vector3& onto)
	{
		return vec.Project(onto);
	}

	Vector3::Vector3()
		: x{ 0.f }, y{ 0.f }, z{ 0.f } { }

	Vector3::Vector3(const float scalar)
		: x{ scalar }, y{ scalar }, z{ scalar } { }

	Vector3::Vector3(const Vector2& xy, const float z)
		: x{ xy.x }, y{ xy.y }, z{ z } { }

	Vector3::Vector3(const Vector4& xyzw)
		: x{ xyzw.x }, y{ xyzw.y }, z{ xyzw.z } { }

	Vector3::Vector3(const float x, const float y, const float z)
		: x{ x }, y{ y }, z{ z } { }

	Vector3::Vector3(const vec3& rhs)
		: x{ rhs.x }, y{ rhs.y }, z{ rhs.z } { }

	Vector3::Vector3(const Vector3& rhs) = default;

	float Vector3::Dot(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3 Vector3::Cross(const Vector3& rhs) const
	{
		return
		{
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		};
	}

	float Vector3::Length() const
	{
		return CatalystMath::Sqrt(LengthSqr());
	}

	float Vector3::LengthSqr() const
	{
		return x * x + y * y + z * z;
	}

	void Vector3::Normalize()
	{
		float len = Length();

		if (CatalystMath::Approximately(len, 0.f))
		{
			x = 0.f;
			y = 0.f;
			z = 0.f;
		}
		else
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	Vector3 Vector3::Normalized() const
	{
		const float len = Length();

		return CatalystMath::Approximately(len, 0.f) ? Vector3{ 0.f, 0.f, 0.f } : Vector3{ x / len, y / len, z / len };
	}

	bool Vector3::IsApproximatelyEqual(const Vector3& rhs, const float e) const
	{
		for (int i = 0; i < VECTOR_3_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], rhs[i], e))
			{
				return false;
			}
		}

		return true;
	}

	float Vector3::AngleBetween(const Vector3& rhs) const
	{
		const float num = Dot(rhs);
		const float den = Length() * rhs.Length();

		return CatalystMath::Acos(num / den);
	}

	float Vector3::Distance(const Vector3& rhs) const
	{
		return (*this - rhs).Length();
	}

	Vector3 Vector3::Min(const Vector3& rhs) const
	{
		return
		{
			CatalystMath::Min(x, rhs.x),
			CatalystMath::Min(y, rhs.y),
			CatalystMath::Min(z, rhs.z)
		};
	}

	Vector3 Vector3::Max(const Vector3& rhs) const
	{
		return
		{
			CatalystMath::Max(x, rhs.x),
			CatalystMath::Max(y, rhs.y),
			CatalystMath::Max(z, rhs.z)
		};
	}

	Vector3 Vector3::Abs() const
	{
		return
		{
			CatalystMath::Abs(x),
			CatalystMath::Abs(y),
			CatalystMath::Abs(z)
		};
	}

	Vector3 Vector3::Clamp(const Vector3& min, const Vector3& max) const
	{
		return
		{
			CatalystMath::Clamp(x, min.x, max.x),
			CatalystMath::Clamp(y, min.y, max.y),
			CatalystMath::Clamp(z, min.z, max.z)
		};
	}

	Vector3 Vector3::Reflect(const Vector3& normal) const
	{
		return *this - normal * (2.f * this->Dot(normal));
	}

	Vector3 Vector3::Project(const Vector3& onto) const
	{
		return onto * (this->Dot(onto) / onto.Dot(onto));
	}

	ostream& operator<<(ostream& stream, const Vector3& vec)
	{
		stream << std::format("({:.2f}, {:.2f}, {:.2f})", vec.x, vec.y, vec.z);

		return stream;
	}

	Vector3::operator vec3() const
	{
		return { x, y, z };
	}

	Vector3::operator Vector2() const
	{
		return { x, y };
	}

	Vector3::operator Vector4() const
	{
		return { x, y, z, 0.f };
	}

	Vector3& Vector3::operator=(const Vector3& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3{ -x, -y, -z };
	}

	bool Vector3::operator==(const Vector3& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		return IsApproximatelyEqual(rhs);
	}

	bool Vector3::operator!=(const Vector3& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !IsApproximatelyEqual(rhs);
	}

	bool Vector3::operator<(const Vector3& rhs) const
	{
		return LengthSqr() < rhs.LengthSqr();
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3{ x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3{ x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Vector3 Vector3::operator*(const Vector3& rhs) const
	{
		return Vector3{ x * rhs.x, y * rhs.y, z * rhs.z };
	}

	Vector3& Vector3::operator*=(const Vector3& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector3 Vector3::operator*(const float rhs) const
	{
		return Vector3{ x * rhs, y * rhs, z * rhs };
	}

	Vector3& Vector3::operator*=(const float rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector3 Vector3::operator/(const float rhs) const
	{
		return Vector3{ x / rhs, y / rhs, z / rhs };
	}

	Vector3& Vector3::operator/=(const float rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	float& Vector3::operator[](int index)
	{
		assert(index >= 0 && index < VECTOR_3_SIZE);

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

			case 2:
			{
				return z;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}

	const float& Vector3::operator[](int index) const
	{
		assert(index >= 0 && index < VECTOR_3_SIZE);

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

			case 2:
			{
				return z;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}
}

/*****************************************************************************
 * Vector4
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Vector4.h"

#include <cassert>
#include <format>
#include <stdexcept>

#include "CatalystMath.h"
#include "Vector2.h"
#include "Vector3.h"

#define VECTOR_4_SIZE 4

using std::runtime_error;

namespace Catalyst::Math
{
	const Vector4 Vector4::ZERO    = Vector4{ 0.f };
	const Vector4 Vector4::ONE     = Vector4{ 1.f };
	const Vector4 Vector4::HALF    = Vector4{ .5f };
	const Vector4 Vector4::UP      = Vector4{ 0.f, 1.f, 0.f, 0.f };
	const Vector4 Vector4::DOWN    = Vector4{ 0.f, -1.f, 0.f, 0.f };
	const Vector4 Vector4::LEFT    = Vector4{ -1.f, 0.f, 0.f, 0.f };
	const Vector4 Vector4::RIGHT   = Vector4{ 1.f, 0.f, 0.f, 0.f };
	const Vector4 Vector4::FORWARD = Vector4{ 0.f, 0.f, 1.f, 0.f };
	const Vector4 Vector4::BACK    = Vector4{ 0.f, 0.f, -1.f, 0.f };

	float Vector4::Dot(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.Dot(rhs);
	}

	Vector4 Vector4::Cross(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.Cross(rhs);
	}

	Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, const float t)
	{
		return a * (1 - t) + b * t;
	}

	float Vector4::AngleBetween(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.AngleBetween(rhs);
	}

	float Vector4::Distance(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.Distance(rhs);
	}

	Vector4 Vector4::Min(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.Min(rhs);
	}

	Vector4 Vector4::Max(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.Max(rhs);
	}

	Vector4 Vector4::Abs(const Vector4& vec)
	{
		return vec.Abs();
	}

	Vector4 Vector4::Clamp(const Vector4& val, const Vector4& min, const Vector4& max)
	{
		return val.Clamp(min, max);
	}

	Vector4 Vector4::Reflect(const Vector4& vec, const Vector4& normal)
	{
		return vec.Reflect(normal);
	}

	Vector4 Vector4::Project(const Vector4& vec, const Vector4& onto)
	{
		return vec.Project(onto);
	}

	Vector4::Vector4()
		: x{ 0.f }, y{ 0.f }, z{ 0.f }, w{ 0.f } { }

	Vector4::Vector4(const float scalar)
		: x{ scalar }, y{ scalar }, z{ scalar }, w{ scalar } { }

	Vector4::Vector4(const Vector2& xy, const float z, const float w)
		: x{ xy.x }, y{ xy.y }, z{ z }, w{ w } { }

	Vector4::Vector4(const Vector3& xyz, const float w)
		: x{ xyz.x }, y{ xyz.y }, z{ xyz.z }, w{ w } { }

	Vector4::Vector4(const float x, const float y, const float z, const float w)
		: x{ x }, y{ y }, z{ z }, w{ w } { }

	Vector4::Vector4(const vec4& rhs)
		: x{ rhs.x }, y{ rhs.y }, z{ rhs.z }, w{ rhs.w } { }

	Vector4::Vector4(const Vector4& rhs) = default;

	float Vector4::Dot(const Vector4& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector4 Vector4::Cross(const Vector4& rhs) const
	{
		return
		{
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x,
			0.f
		};
	}

	float Vector4::Length() const
	{
		return CatalystMath::Sqrt(LengthSqr());
	}

	float Vector4::LengthSqr() const
	{
		return x * x + y * y + z * z;
	}

	void Vector4::Normalize()
	{
		float len = Length();

		if (CatalystMath::Approximately(len, 0.f))
		{
			x = 0.f;
			y = 0.f;
			z = 0.f;
			w = 0.f;
		}
		else
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	Vector4 Vector4::Normalized() const
	{
		const float len = Length();

		return CatalystMath::Approximately(len, 0.f) ? Vector4{ 0.f, 0.f, 0.f, 0.f } : Vector4{ x / len, y / len, z / len, w };
	}

	bool Vector4::IsApproximatelyEqual(const Vector4& rhs, const float e) const
	{
		for (int i = 0; i < VECTOR_4_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], rhs[i], e))
			{
				return false;
			}
		}

		return true;
	}

	float Vector4::AngleBetween(const Vector4& rhs) const
	{
		const float num = Dot(rhs);
		const float den = Length() * rhs.Length();

		return CatalystMath::Acos(num / den);
	}

	float Vector4::Distance(const Vector4& rhs) const
	{
		return (*this - rhs).Length();
	}

	Vector4 Vector4::Min(const Vector4& rhs) const
	{
		return
		{
			CatalystMath::Min(x, rhs.x),
			CatalystMath::Min(y, rhs.y),
			CatalystMath::Min(z, rhs.z),
			CatalystMath::Min(w, rhs.w)
		};
	}

	Vector4 Vector4::Max(const Vector4& rhs) const
	{
		return
		{
			CatalystMath::Max(x, rhs.x),
			CatalystMath::Max(y, rhs.y),
			CatalystMath::Max(z, rhs.z),
			CatalystMath::Max(w, rhs.w)
		};
	}

	Vector4 Vector4::Abs() const
	{
		return
		{
			CatalystMath::Abs(x),
			CatalystMath::Abs(y),
			CatalystMath::Abs(z),
			CatalystMath::Abs(w)
		};
	}

	Vector4 Vector4::Clamp(const Vector4& min, const Vector4& max) const
	{
		return
		{
			CatalystMath::Clamp(x, min.x, max.x),
			CatalystMath::Clamp(y, min.y, max.y),
			CatalystMath::Clamp(z, min.z, max.z),
			CatalystMath::Clamp(w, min.w, max.w)
		};
	}

	Vector4 Vector4::Reflect(const Vector4& normal) const
	{
		return *this - normal * (2.f * this->Dot(normal));
	}

	Vector4 Vector4::Project(const Vector4& onto) const
	{
		return onto * (this->Dot(onto) / onto.Dot(onto));
	}

	ostream& operator<<(ostream& stream, const Vector4& vec)
	{
		stream << std::format("({:.2f}, {:.2f}, {:.2f}, {:.2f})", vec.x, vec.y, vec.z, vec.w);

		return stream;
	}

	Vector4::operator vec4() const
	{
		return { x, y, z, w };
	}

	Vector4::operator Vector2() const
	{
		return { x, y };
	}

	Vector4::operator Vector3() const
	{
		return { x, y, z };
	}

	Vector4& Vector4::operator=(const Vector4& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *this;
	}

	Vector4 Vector4::operator-() const
	{
        return Vector4{ -x, -y, -z, -w };
	}

	bool Vector4::operator==(const Vector4& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

        return IsApproximatelyEqual(rhs);
	}

	bool Vector4::operator!=(const Vector4& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !IsApproximatelyEqual(rhs);
	}

	bool Vector4::operator<(const Vector4& rhs) const
	{
		return LengthSqr() < rhs.LengthSqr();
	}

	Vector4 Vector4::operator+(const Vector4& rhs) const
	{
        return Vector4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
	}

	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector4 Vector4::operator-(const Vector4& rhs) const
	{
		return Vector4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
	}

	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Vector4 Vector4::operator*(const Vector4& rhs) const
	{
		return Vector4{ x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
	}

	Vector4& Vector4::operator*=(const Vector4& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector4 Vector4::operator*(const float rhs) const
	{
		return Vector4{ x * rhs, y * rhs, z * rhs, w * rhs };
	}

	Vector4& Vector4::operator*=(const float rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector4 Vector4::operator/(const float rhs) const
	{
		return Vector4{ x / rhs, y / rhs, z / rhs, w / rhs };
	}

	Vector4& Vector4::operator/=(const float rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	float& Vector4::operator[](int index)
	{
		assert(index >= 0 && index < VECTOR_4_SIZE);

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

			case 3:
			{
				return w;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}

	const float& Vector4::operator[](int index) const
	{
		assert(index >= 0 && index < VECTOR_4_SIZE);

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

			case 3:
			{
				return w;
			}

			default:
			{
				throw runtime_error(std::format("Index {} out of bounds!", index));
			}
		}
	}
}

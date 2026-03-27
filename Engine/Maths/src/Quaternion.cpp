/*****************************************************************************
 * Quaternion
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Quaternion.h"

#include <cassert>
#include <format>

#include "CatalystMath.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"

#define QUATERNION_SIZE 4

using std::runtime_error;

namespace Catalyst::Math
{
	const Quat Quat::IDENTITY = { 0.f, 0.f, 0.f, 1.f };

	float Quat::Dot(const Quat& lhs, const Quat& rhs)
	{
		return lhs.Dot(rhs);
	}

	Quat Quat::Slerp(const Quat& a, const Quat& b, const float t)
	{
		const float theta = AngleBetween(a, b);

		if (CatalystMath::Approximately(theta, 0.f))
		{
			return Lerp(a, b, t);
		}

		return a * (CatalystMath::Sin((1.f - t) * theta) / CatalystMath::Sin(theta)) + b * (CatalystMath::Sin(t * theta) / CatalystMath::Sin(theta));
	}

	Quat Quat::Lerp(const Quat& a, const Quat& b, const float t)
	{
		return (a * (1 - t) + b * t).Normalised();
	}

	Quat Quat::Normalised(const Quat& rhs)
	{
		return rhs.Normalised();
	}

	float Quat::AngleBetween(const Quat& lhs, const Quat& rhs)
	{
		return lhs.AngleBetween(rhs);
	}

	Quat Quat::FromAxisAngle(const Vector3& axis, const float rad)
	{
		const float halfRad = rad * 0.5f;

		return
		{
			axis.x * CatalystMath::Sin(halfRad),
			axis.y * CatalystMath::Sin(halfRad),
			axis.z * CatalystMath::Sin(halfRad),
			CatalystMath::Cos(halfRad)
		};
	}

	Quat Quat::FromEuler(const Vector3& euler)
	{
		// θ
		const float theta    = CatalystMath::Radians(euler.x) * .5f;
		const float sinTheta = CatalystMath::Sin(theta);
		const float cosTheta = CatalystMath::Cos(theta);
		// Φ
		const float phi    = CatalystMath::Radians(euler.y) * .5f;
		const float sinPhi = CatalystMath::Sin(phi);
		const float cosPhi = CatalystMath::Cos(phi);
		// Ψ
		const float psi    = CatalystMath::Radians(euler.z) * .5f;
		const float sinPsi = CatalystMath::Sin(psi);
		const float cosPsi = CatalystMath::Cos(psi);

		return
		{
			sinPhi * cosTheta * cosPsi - cosPhi * sinTheta * sinPsi,
			cosPhi * sinTheta * cosPsi + sinPhi * cosTheta * sinPsi,
			cosPhi * cosTheta * sinPsi - sinPhi * sinTheta * cosPsi,
			cosPhi * cosTheta * cosPsi + sinPhi * sinTheta * sinPsi
		};
	}

	Quat Quat::FromEuler(const float pitch, const float yaw, const float roll)
	{
		return FromEuler(Vector3{ pitch, yaw, roll });
	}

	Quat Quat::FromMatrix3(const Matrix3& mat)
	{
		const float trace = mat.Trace();
		const Vector3 row0 = mat.Row(0);
		const Vector3 row1 = mat.Row(1);
		const Vector3 row2 = mat.Row(2);

		if (trace > 0)
		{
			const float s = .5f / CatalystMath::Sqrt(trace + 1.f);
			return
			{
				(row2[1] - row1[2]) * s,
				(row0[2] - row2[0]) * s,
				(row1[0] - row0[1]) * s,
				.25f / s
			};
		}

		if (row0[0] > row1[1] && row0[0] > row2[2])
		{
			const float s = 2.f * CatalystMath::Sqrt(1.f + row0[0] - row1[1] - row2[2]);
			return
			{
				.25f * s,
				(row0[1] + row1[0]) / s,
				(row0[2] + row2[0]) / s,
				(row2[1] - row1[2]) / s
			};
		}

		if (row1[1] > row2[2])
		{
			const float s = 2.f * CatalystMath::Sqrt(1.f + row1[1] - row0[0] - row2[2]);

			return
			{
				(row0[1] + row1[0]) / s,
				.25f * s,
				(row1[2] + row2[1]) / s,
				(row0[2] - row2[0]) / s
			};
		}

		const float s = 2.f * CatalystMath::Sqrt(1.f + row2[2] - row0[0] - row1[1]);
		return
		{
			(row1[0] - row0[1]) / s,
			(row0[2] + row2[0]) / s,
			(row1[2] + row2[1]) / s,
			.25f * s
		};
	}

	Quat Quat::FromToRotation(const Vector3& from, const Vector3& to)
	{
		const Vector3 a = from.Normalized();
		const Vector3 b = to.Normalized();

		Vector3 axis = a.Cross(b);
		if (axis == Vector3::ZERO)
		{
			if (CatalystMath::Approximately(a.Dot(b), -1.f))
			{
				// 180-degree rotation — pick arbitrary perpendicular axis
				axis = Vector3::UP.Cross(a);
				if (axis == Vector3::ZERO)
				{
					axis = Vector3::RIGHT.Cross(a);
				}

				axis.Normalize();
				return { axis.x, axis.y, axis.z, 0.f };
			}

			return IDENTITY;
		}

		axis.Normalize();

		const float theta = CatalystMath::Acos(a.Dot(b)) * .5f;

		return
		{
			axis.x * CatalystMath::Sin(theta),
			axis.y * CatalystMath::Sin(theta),
			axis.z * CatalystMath::Sin(theta),
			CatalystMath::Cos(theta)
		 };
	}

	Quat Quat::LookRotation(const Vector3& forward, const Vector3& up)
	{
		const Vector3 f = forward.Normalized();
		const Vector3 r = up.Cross(f).Normalized();
		const Vector3 u = r.Cross(f);

		return FromMatrix3(
			{
				r.x, r.y, r.z,
				u.x, u.y, u.z,
				f.x, f.y, f.z
			}
		);
	}

	Quat::Quat()
		: x{ 0.f }, y{ 0.f }, z{ 0.f }, w{ 1.f } { }

	Quat::Quat(const float x, const float y, const float z, const float w)
		: x{ x }, y{ y }, z{ z }, w{ w } { }

	Quat::Quat(const Vector4& vec)
		: x{ vec.x }, y{ vec.y }, z{ vec.z }, w{ vec.w } { }

	Quat::Quat(const quat& rhs)
		: x{ rhs.x }, y{ rhs.y }, z{ rhs.z }, w{ rhs.w } { }

	Quat::Quat(const Quat& rhs) = default;

	float Quat::Dot(const Quat& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	float Quat::Length() const
	{
		return CatalystMath::Sqrt(LengthSqr());
	}

	float Quat::LengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Quat::Normalise()
	{
		const float len = Length();

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
			w /= len;
		}
	}

	Quat Quat::Normalised() const
	{
		const float len = Length();

		return CatalystMath::Approximately(len, 0.f) ? Quat{ 0.f, 0.f, 0.f, 1.f } : Quat{ x / len, y / len, z / len, w / len };
	}

	Quat Quat::Conjugate() const
	{
		return { -x, -y, -z, w };
	}

	Quat Quat::Inverse() const
	{
		const Quat conj    = Conjugate();
		const float length = LengthSqr();

		return { conj.x / length, conj.y / length, conj.z / length, conj.w / length };
	}

	bool Quat::IsApproximatelyEqual(const Quat& rhs, const float e) const
	{
		for (int i = 0; i < QUATERNION_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], rhs[i], e))
			{
				return false;
			}
		}

		return true;
	}

	float Quat::AngleBetween(const Quat& rhs) const
	{
		return 2.f * CatalystMath::Acos(CatalystMath::Abs(this->Dot(rhs)));
	}

	Vector3 Quat::Axis() const
	{
		return Vector3{ x, y, z }.Normalized();
	}

	float Quat::Angle() const
	{
		return 2.f * CatalystMath::Acos(w);
	}

	Vector3 Quat::ToEuler() const
	{
		return
		{
			CatalystMath::Degrees(CatalystMath::Atan2(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y))),
			CatalystMath::Degrees(CatalystMath::Asin(2.f * (w * y - z * x))),
			CatalystMath::Degrees(CatalystMath::Atan2(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z)))
		};
	}

	Matrix3 Quat::ToMatrix3() const
	{
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;

		const float xy = x * y;
		const float yz = y * z;
		const float xz = x * z;

		const float xw = x * w;
		const float yw = y * w;
		const float zw = z * w;

		return
		{
			1.f - 2.f * (y2 + z2), 2.f * (xy - zw), 2.f * (xz + yw),
			2.f * (xy + zw), 1.f - 2.f * (x2 + z2), 2.f * (yz - xw),
			2.f * (xz - yw), 2.f * (yz + xw), 1.f - 2.f * (x2 + y2)
		};
	}

	Matrix4 Quat::ToMat4() const
	{
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;

		const float xy = x * y;
		const float yz = y * z;
		const float xz = x * z;

		const float xw = x * w;
		const float yw = y * w;
		const float zw = z * w;

		return
		{
			1.f - 2.f * (y2 + z2), 2.f * (xy - zw), 2.f * (xz + yw), 0.f,
			2.f * (xy + zw), 1.f - 2.f * (x2 + z2), 2.f * (yz - xw), 0.f,
			2.f * (xz - yw), 2.f * (yz + xw), 1.f - 2.f * (x2 + y2), 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Vector3 Quat::Rotate(const Vector3& vec) const
	{
		return *this * vec;
	}

	Vector3 Quat::GetForward() const
	{
		return Vector3{ ToMatrix3().Column(2) };
	}

	Vector3 Quat::GetUp() const
	{
		return Vector3{ ToMatrix3().Column(1) };
	}

	Vector3 Quat::GetRight() const
	{
		return Vector3{ ToMatrix3().Column(0) };
	}

	ostream& operator<<(ostream& stream, const Quat& q)
	{
		stream << std::format("({:.2f}, {:.2f}, {:.2f}, {:.2f})", q.x, q.y, q.z, q.w);

		return stream;
	}

	Quat::operator quat() const
	{
		return { w, x, y, z };
	}

	Quat::operator Vector4() const
	{
		return { x, y, z, w };
	}

	Quat& Quat::operator=(const Quat& rhs) = default;

	Quat Quat::operator-() const
	{
		return { -x, -y, -z, w };
	}

	bool Quat::operator==(const Quat& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		return this->IsApproximatelyEqual(rhs);
	}

	bool Quat::operator!=(const Quat& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !this->IsApproximatelyEqual(rhs);
	}

	Quat Quat::operator*(const Quat& rhs) const
	{
		return
		{
			w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
			w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
		};
	}

	Quat& Quat::operator*=(const Quat& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector3 Quat::operator*(const Vector3& rhs) const
	{
		const Vector3 vec   = { x, y, z };
		const Vector3 cross = vec.Cross(rhs);
		return rhs + cross * (2.f * w) + vec.Cross(cross) * 2.f;
	}

	Quat Quat::operator*(const float rhs) const
	{
		return { x * rhs, y * rhs, z * rhs, w * rhs };
	}

	Quat& Quat::operator*=(const float rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Quat Quat::operator+(const Quat& rhs) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
	}

	Quat& Quat::operator+=(const Quat& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	float& Quat::operator[](int index)
	{
		assert(index >= 0 && index < QUATERNION_SIZE);

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

	const float& Quat::operator[](int index) const
	{
		assert(index >= 0 && index < QUATERNION_SIZE);

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

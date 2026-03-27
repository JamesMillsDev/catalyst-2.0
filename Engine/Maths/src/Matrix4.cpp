/*****************************************************************************
 * Matrix4
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Matrix4.h"

#include <cassert>
#include <stdexcept>

#include "CatalystMath.h"
#include "Matrix3.h"
#include "Vector3.h"
#include "Vector4.h"

#define MATRIX_4_ROWS 4
#define MATRIX_4_COLS 4
#define MATRIX_4_SIZE MATRIX_4_ROWS * MATRIX_4_COLS

using std::runtime_error;

namespace Catalyst::Math
{
	Matrix4 Matrix4::MakeTranslate(const Vector3& trans)
	{
		return MakeTranslate(trans.x, trans.y, trans.z);
	}

	Matrix4 Matrix4::MakeTranslate(float x, float y, float z)
	{
		return
		{
			1.f, 0.f, 0.f, x,
			0.f, 1.f, 0.f, y,
			0.f, 0.f, 1.f, z,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeRotateX(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, cos, sin, 0.f,
			0.f, -sin, cos, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeRotateY(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			cos, 0.f, -sin, 0.f,
			0.f, 1.f, 0.f, 0.f,
			sin, 0.f, cos, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeRotateZ(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			cos, sin, 0.f, 0.f,
			-sin, cos, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeRotate(const Vector3& euler)
	{
		return MakeRotateX(CatalystMath::Radians(euler.x)) *
		       MakeRotateY(CatalystMath::Radians(euler.y)) *
		       MakeRotateZ(CatalystMath::Radians(euler.z));
	}

	Matrix4 Matrix4::MakeScale(const Vector3& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	Matrix4 Matrix4::MakeScale(float x, float y, float z)
	{
		return
		{
			x, 0.f, 0.f, 0.f,
			0.f, y, 0.f, 0.f,
			0.f, 0.f, z, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeTransform(const Vector3& trans, const Vector3& euler, const Vector3& scale)
	{
		return MakeTranslate(trans) * MakeRotate(euler) * MakeScale(scale);
	}

	Matrix4 Matrix4::MakePerspective(const float fovY, const float aspect, const float near, const float far)
	{
		const float tanFov = CatalystMath::Tan(fovY / 2.f);

		return
		{
			1 / (aspect * tanFov), 0.f, 0.f, 0.f,
			0.f, 1 / tanFov, 0.f, 0.f,
			0.f, 0.f, -((far + near) / (far - near)), -(2.f * far * near / (far - near)),
			0.f, 0.f, -1.f, 0.f
		};
	}

	Matrix4 Matrix4::MakeOrthographic(const float left, const float right, const float bottom, const float top,
	                                  const float near, const float far)
	{
		return
		{
			2.f / (right - left), 0.f, 0.f, -((right + left) / (right - left)),
			0.f, 2.f / (top - bottom), 0.f, -((top + bottom) / (top - bottom)),
			0.f, 0.f, -2.f / (far - near), -((far + near) / (far - near)),
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::MakeLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		const Vector3 zAxis = (eye - target).Normalized();
		const Vector3 xAxis = Vector3::Cross(up, zAxis).Normalized();
		const Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

		return
		{
			xAxis.x, yAxis.x, zAxis.x, -Vector3::Dot(xAxis, eye),
			xAxis.y, yAxis.y, zAxis.y, -Vector3::Dot(yAxis, eye),
			xAxis.z, yAxis.z, zAxis.z, -Vector3::Dot(zAxis, eye),
			0.f, 0.f, 0.f, 1.f
		};
	}

	Matrix4 Matrix4::Identity()
	{
		return Matrix4{ 1.f };
	}

	Matrix4 Matrix4::FromRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
	{
		return
		{
			{ row1.x, row2.x, row3.x, row4.x },
			{ row1.y, row2.y, row3.y, row4.y },
			{ row1.z, row2.z, row3.z, row4.z },
			{ row1.w, row2.w, row3.w, row4.w }
		};
	}

	Matrix4 Matrix4::FromCols(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4)
	{
		return { col1, col2, col3, col4 };
	}

	Matrix4::Matrix4()
		: m1{ 1.f }, m2{ 0.f }, m3{ 0.f }, m4{ 0.f },
		  m5{ 0.f }, m6{ 1.f }, m7{ 0.f }, m8{ 0.f },
		  m9{ 0.f }, m10{ 0.f }, m11{ 1.f }, m12{ 0.f },
		  m13{ 0.f }, m14{ 0.f }, m15{ 0.f }, m16{ 1.f } { }

	Matrix4::Matrix4(const float scalar)
		: m1{ scalar }, m2{ 0.f }, m3{ 0.f }, m4{ 0.f },
		  m5{ 0.f }, m6{ scalar }, m7{ 0.f }, m8{ 0.f },
		  m9{ 0.f }, m10{ 0.f }, m11{ scalar }, m12{ 0.f },
		  m13{ 0.f }, m14{ 0.f }, m15{ 0.f }, m16{ scalar } { }

	Matrix4::Matrix4(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4)
		: m1{ col1.x }, m2{ col1.y }, m3{ col1.z }, m4{ col1.w },
		  m5{ col2.x }, m6{ col2.y }, m7{ col2.z }, m8{ col2.w },
		  m9{ col3.x }, m10{ col3.y }, m11{ col3.z }, m12{ col3.w },
		  m13{ col4.x }, m14{ col4.y }, m15{ col4.z }, m16{ col4.w } { }

	Matrix4::Matrix4(const Matrix3& mat)
		: m1{ mat.m1 }, m2{ mat.m2 }, m3{ mat.m3 }, m4{ 0.f },
		  m5{ mat.m4 }, m6{ mat.m5 }, m7{ mat.m6 }, m8{ 0.f },
		  m9{ mat.m7 }, m10{ mat.m8 }, m11{ mat.m9 }, m12{ 0.f },
		  m13{ 0.f }, m14{ 0.f }, m15{ 0.f }, m16{ 1.f } { }

	Matrix4::Matrix4(const float m1, const float m5, const float m9, const float m13,
	                 const float m2, const float m6, const float m10, const float m14,
	                 const float m3, const float m7, const float m11, const float m15,
	                 const float m4, const float m8, const float m12, const float m16)
		: m1{ m1 }, m2{ m2 }, m3{ m3 }, m4{ m4 },
		  m5{ m5 }, m6{ m6 }, m7{ m7 }, m8{ m8 },
		  m9{ m9 }, m10{ m10 }, m11{ m11 }, m12{ m12 },
		  m13{ m13 }, m14{ m14 }, m15{ m15 }, m16{ m16 } { }

	Matrix4::Matrix4(const Matrix4& rhs) = default;

	Matrix4::Matrix4(const mat4& rhs)
		: m1{ 0.f }, m2{ 0.f }, m3{ 0.f }, m4{ 0.f },
		  m5{ 0.f }, m6{ 0.f }, m7{ 0.f }, m8{ 0.f },
		  m9{ 0.f }, m10{ 0.f }, m11{ 0.f }, m12{ 0.f },
		  m13{ 0.f }, m14{ 0.f }, m15{ 0.f }, m16{ 0.f }
	{
		memcpy(&m1, &rhs, sizeof(float) * MATRIX_4_SIZE);
	}

	Vector3 Matrix4::GetRight() const
	{
		return { Column(0) };
	}

	Vector3 Matrix4::GetUp() const
	{
		return { Column(1) };
	}

	Vector3 Matrix4::GetForward() const
	{
		return { Column(2) };
	}

	Vector3 Matrix4::Translation() const
	{
		return { m13, m14, m15 };
	}

	Vector3 Matrix4::Scale() const
	{
		return { Column(0).Length(), Column(1).Length(), Column(2).Length() };
	}

	float Matrix4::RotationX() const
	{
		return CatalystMath::Atan2(m2, m1);
	}

	float Matrix4::RotationY() const
	{
		return CatalystMath::Atan2(-m4, m5);
	}

	float Matrix4::RotationZ() const
	{
		return CatalystMath::Atan2(m7, m9);
	}

	Vector3 Matrix4::Euler() const
	{
		return
		{
			CatalystMath::Degrees(RotationX()),
			CatalystMath::Degrees(RotationY()),
			CatalystMath::Degrees(RotationZ())
		};
	}

	Matrix3 Matrix4::ToMat3() const
	{
		return
		{
			m1, m5, m9,
			m2, m6, m10,
			m3, m7, m11
		};
	}

	bool Matrix4::IsApproximatelyEqual(const Matrix4& matrix, const float e) const
	{
		for (int i = 0; i < MATRIX_4_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], matrix[i], e))
			{
				return false;
			}
		}

		return true;
	}

	Matrix4 Matrix4::Transposed() const
	{
		return
		{
			m1, m2, m3, m4,
			m5, m6, m7, m8,
			m9, m10, m11, m12,
			m13, m14, m15, m16
		};
	}

	Matrix4 Matrix4::Inverse() const
	{
		// inverse = adjugate / determinant
		const Matrix4 adj = Adjugate();
		const float det   = Determinant();
		const float detO1 = 1.f / det;

		return
		{
			detO1 * adj.m1, detO1 * adj.m5, detO1 * adj.m9, detO1 * adj.m13,
			detO1 * adj.m2, detO1 * adj.m6, detO1 * adj.m10, detO1 * adj.m14,
			detO1 * adj.m3, detO1 * adj.m7, detO1 * adj.m11, detO1 * adj.m15,
			detO1 * adj.m4, detO1 * adj.m8, detO1 * adj.m12, detO1 * adj.m16
		};
	}

	Matrix4 Matrix4::Minor() const
	{
		return
		{
			Matrix3{ m6, m7, m8, m10, m11, m12, m14, m15, m16 }.Determinant(),
			Matrix3{ m2, m3, m4, m10, m11, m12, m14, m15, m16 }.Determinant(),
			Matrix3{ m2, m3, m4, m6, m7, m8, m14, m15, m16 }.Determinant(),
			Matrix3{ m2, m3, m4, m6, m7, m8, m10, m11, m12 }.Determinant(),
			Matrix3{ m5, m7, m8, m9, m11, m12, m13, m15, m16 }.Determinant(),
			Matrix3{ m1, m3, m4, m9, m11, m12, m13, m15, m16 }.Determinant(),
			Matrix3{ m1, m3, m4, m5, m7, m8, m13, m15, m16 }.Determinant(),
			Matrix3{ m1, m3, m4, m5, m7, m8, m9, m11, m12 }.Determinant(),
			Matrix3{ m5, m6, m8, m9, m10, m12, m13, m14, m16 }.Determinant(),
			Matrix3{ m1, m2, m4, m9, m11, m12, m13, m14, m16 }.Determinant(),
			Matrix3{ m1, m5, m13, m2, m6, m14, m4, m8, m16 }.Determinant(),
			Matrix3{ m1, m5, m9, m2, m6, m10, m4, m8, m12 }.Determinant(),
			Matrix3{ m5, m6, m7, m9, m10, m11, m13, m14, m15 }.Determinant(),
			Matrix3{ m1, m2, m3, m9, m10, m11, m13, m14, m15 }.Determinant(),
			Matrix3{ m1, m5, m13, m2, m6, m14, m3, m7, m15 }.Determinant(),
			Matrix3{ m1, m5, m9, m2, m6, m10, m3, m7, m11 }.Determinant(),
		};
	}

	Matrix4 Matrix4::Cofactor() const
	{
		// apply the checkerboard sign pattern (+ - + - / - + - + / + - + - / - + - +) to the minor matrix
		const Matrix4 minor = Minor();
		return
		{
			+minor.m1, -minor.m5, +minor.m9, -minor.m13,
			-minor.m2, +minor.m6, -minor.m10, +minor.m14,
			+minor.m3, -minor.m7, +minor.m11, -minor.m15,
			-minor.m4, +minor.m8, -minor.m12, +minor.m16,
		};
	}

	Matrix4 Matrix4::Adjugate() const
	{
		// the adjugate is the transpose of the cofactor matrix
		const Matrix4 cofactor = Cofactor();
		return cofactor.Transposed();
	}

	float Matrix4::Determinant() const
	{
		// expand along the first column
		const Matrix4 cofactor = Cofactor();
		return m1 * cofactor.m1 + m2 * cofactor.m2 + m3 * cofactor.m3 + m4 * cofactor.m4;
	}

	bool Matrix4::IsOrthogonal(const float e) const
	{
		const Matrix4 qT = Transposed() * *this;
		return qT.IsApproximatelyEqual(Identity(), e);
	}

	bool Matrix4::IsIdentity(const float e) const
	{
		return IsApproximatelyEqual(Identity(), e);
	}

	Vector4 Matrix4::Row(const int index) const
	{
		assert(index >= 0 && index < MATRIX_4_ROWS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				return { m1, m5, m9, m13 };
			}

			case 1:
			{
				return { m2, m6, m10, m14 };
			}

			case 2:
			{
				return { m3, m7, m11, m15 };
			}

			case 3:
			{
				return { m4, m8, m12, m16 };
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	Vector4 Matrix4::Column(const int index) const
	{
		assert(index >= 0 && index < MATRIX_4_COLS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				return { m1, m2, m3, m4 };
			}

			case 1:
			{
				return { m5, m6, m7, m8 };
			}

			case 2:
			{
				return { m9, m10, m11, m12 };
			}

			case 3:
			{
				return { m13, m14, m15, m16 };
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix4::SetRow(const int index, const Vector4& newRow)
	{
		assert(index >= 0 && index < MATRIX_4_ROWS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				m1  = newRow.x;
				m5  = newRow.y;
				m9  = newRow.z;
				m13 = newRow.w;
				break;
			}

			case 1:
			{
				m2  = newRow.x;
				m6  = newRow.y;
				m10 = newRow.z;
				m14 = newRow.w;
				break;
			}

			case 2:
			{
				m3  = newRow.x;
				m7  = newRow.y;
				m11 = newRow.z;
				m15 = newRow.w;
				break;
			}

			case 3:
			{
				m4  = newRow.x;
				m8  = newRow.y;
				m12 = newRow.z;
				m16 = newRow.w;
				break;
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix4::SetColumn(const int index, const Vector4& newCol)
	{
		assert(index >= 0 && index < MATRIX_4_COLS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				m1 = newCol.x;
				m2 = newCol.y;
				m3 = newCol.z;
				m4 = newCol.w;
				break;
			}

			case 1:
			{
				m5 = newCol.x;
				m6 = newCol.y;
				m7 = newCol.z;
				m8 = newCol.w;
				break;
			}

			case 2:
			{
				m9  = newCol.x;
				m10 = newCol.y;
				m11 = newCol.z;
				m12 = newCol.w;
				break;
			}

			case 3:
			{
				m13 = newCol.x;
				m14 = newCol.y;
				m15 = newCol.z;
				m16 = newCol.w;
				break;
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix4::Orthogonalize()
	{
		// Gram-Schmidt process — make each column perpendicular to all previous columns
		// by subtracting the projection of the column onto each prior basis vector
		const Vector4 u1 = Column(0);
		const Vector4 u2 = Column(1);
		const Vector4 u3 = Column(2);
		const Vector4 u4 = Column(3);

		// remove the component of u2 that points along u1
		const Vector4 prj = u1 * (Vector4::Dot(u2, u1) / Vector4::Dot(u1, u1));
		const Vector4 e2  = u2 - prj;

		// remove the components of u3 that point along u1 and e2
		Vector4 prj1     = u1 * (Vector4::Dot(u3, u1) / Vector4::Dot(u1, u1));
		Vector4 prj2     = e2 * (Vector4::Dot(u3, e2) / Vector4::Dot(e2, e2));
		const Vector4 e3 = u3 - prj1 - prj2;

		// remove the components of u4 that point along u1, e2 and e3
		prj1               = u1 * (Vector4::Dot(u4, u1) / Vector4::Dot(u1, u1));
		prj2               = e2 * (Vector4::Dot(u4, e2) / Vector4::Dot(e2, e2));
		const Vector4 prj3 = e3 * (Vector4::Dot(u4, e3) / Vector4::Dot(e3, e3));
		const Vector4 e4   = u4 - prj1 - prj2 - prj3;

		SetColumn(0, u1);
		SetColumn(1, e2);
		SetColumn(2, e3);
		SetColumn(3, e4);
	}

	void Matrix4::Orthonormalize()
	{
		Orthogonalize();

		for (int i = 0; i < MATRIX_4_COLS; ++i)
		{
			SetColumn(i, Column(i).Normalized());
		}
	}

	float Matrix4::Trace() const
	{
		return m1 + m6 + m11 + m16;
	}

	Matrix4::operator mat4() const
	{
		return { Column(0), Column(1), Column(2), Column(3) };
	}

	float* Matrix4::operator*()
	{
		return &m1;
	}

	Matrix4& Matrix4::operator=(const Matrix4& rhs) = default;

	Vector4 Matrix4::operator*(const Vector4& rhs) const
	{
		return
		{
			m1 * rhs.x + m5 * rhs.y + m9 * rhs.z + m13 * rhs.w,
			m2 * rhs.x + m6 * rhs.y + m10 * rhs.z + m14 * rhs.w,
			m3 * rhs.x + m7 * rhs.y + m11 * rhs.z + m16 * rhs.w,
			m4 * rhs.x + m8 * rhs.y + m12 * rhs.z + m16 * rhs.w,
		};
	}

	Matrix4 Matrix4::operator*(const Matrix4& rhs) const
	{
		return
		{
			// Column 0 of result
			m1 * rhs.m1 + m2 * rhs.m5 + m3 * rhs.m9 + m4 * rhs.m13,
			m5 * rhs.m1 + m6 * rhs.m5 + m7 * rhs.m9 + m8 * rhs.m13,
			m9 * rhs.m1 + m10 * rhs.m5 + m11 * rhs.m9 + m12 * rhs.m13,
			m13 * rhs.m1 + m14 * rhs.m5 + m15 * rhs.m9 + m16 * rhs.m13,
			// Column 1 of result
			m1 * rhs.m2 + m2 * rhs.m6 + m3 * rhs.m10 + m4 * rhs.m14,
			m5 * rhs.m2 + m6 * rhs.m6 + m7 * rhs.m10 + m8 * rhs.m14,
			m9 * rhs.m2 + m10 * rhs.m6 + m11 * rhs.m10 + m12 * rhs.m14,
			m13 * rhs.m2 + m14 * rhs.m6 + m15 * rhs.m10 + m16 * rhs.m14,
			// Column 2 of result
			m1 * rhs.m3 + m2 * rhs.m7 + m3 * rhs.m11 + m4 * rhs.m15,
			m5 * rhs.m3 + m6 * rhs.m7 + m7 * rhs.m11 + m8 * rhs.m15,
			m9 * rhs.m3 + m10 * rhs.m7 + m11 * rhs.m11 + m12 * rhs.m15,
			m13 * rhs.m3 + m14 * rhs.m7 + m15 * rhs.m11 + m16 * rhs.m15,
			// Column 3 of result
			m1 * rhs.m4 + m2 * rhs.m8 + m3 * rhs.m12 + m4 * rhs.m16,
			m5 * rhs.m4 + m6 * rhs.m8 + m7 * rhs.m12 + m8 * rhs.m16,
			m9 * rhs.m4 + m10 * rhs.m8 + m11 * rhs.m12 + m12 * rhs.m16,
			m13 * rhs.m4 + m14 * rhs.m8 + m15 * rhs.m12 + m16 * rhs.m16
		};
	}

	Matrix4& Matrix4::operator*=(const Matrix4& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	bool Matrix4::operator==(const Matrix4& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		return IsApproximatelyEqual(rhs);
	}

	bool Matrix4::operator!=(const Matrix4& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !IsApproximatelyEqual(rhs);
	}

	float& Matrix4::operator[](const int index)
	{
		assert(index >= 0 && index < MATRIX_4_SIZE && "Index out of bounds.");
		return (&m1)[index];
	}

	const float& Matrix4::operator[](const int index) const
	{
		assert(index >= 0 && index < MATRIX_4_SIZE && "Index out of bounds.");
		return (&m1)[index];
	}
}

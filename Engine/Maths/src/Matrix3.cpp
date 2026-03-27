/*****************************************************************************
 * Matrix3.$EXTENSION
 * Created by jcm_d on 27/03/2026.
 *****************************************************************************/

#include "Matrix3.h"

#include <cassert>
#include <cstring>
#include <stdexcept>

#include "CatalystMath.h"
#include "Vector3.h"

using std::runtime_error;

#define MATRIX_3_COLS 3
#define MATRIX_3_ROWS 3
#define MATRIX_3_SIZE MATRIX_3_COLS * MATRIX_3_ROWS

namespace Catalyst::Math
{
	Matrix3 Matrix3::MakeTranslate(const Vector3& trans)
	{
		return MakeTranslate(trans.x, trans.y);
	}

	Matrix3 Matrix3::MakeTranslate(float x, float y)
	{
		return
		{
			1.f, 0.f, x,
			0.f, 1.f, y,
			0.f, 0.f, 1.f
		};
	}

	Matrix3 Matrix3::MakeRotateX(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			1.f, 0.f, 0.f,
			0.f, cos, sin,
			0.f, -sin, cos
		};
	}

	Matrix3 Matrix3::MakeRotateY(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			cos, 0.f, -sin,
			0.f, 1.f, 0.f,
			sin, 0.f, cos
		};
	}

	Matrix3 Matrix3::MakeRotateZ(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			cos, sin, 0.f,
			-sin, cos, 0.f,
			0.f, 0.f, 1.f
		};
	}

	Matrix3 Matrix3::MakeRotate2D(const float rad)
	{
		const float sin = CatalystMath::Sin(rad);
		const float cos = CatalystMath::Cos(rad);

		return
		{
			cos, sin, 0.f,
			-sin, cos, 0.f,
			0.f, 0.f, 1.f
		};
	}

	Matrix3 Matrix3::MakeRotate(const Vector3& euler)
	{
		return MakeRotateX(CatalystMath::Radians(euler.x)) *
		       MakeRotateY(CatalystMath::Radians(euler.y)) *
		       MakeRotateZ(CatalystMath::Radians(euler.z));
	}

	Matrix3 Matrix3::MakeScale(const Vector3& scale)
	{
		return MakeScale(scale.x, scale.y, scale.z);
	}

	Matrix3 Matrix3::MakeScale(float x, float y, float z)
	{
		return
		{
			x, 0.f, 0.f,
			0.f, y, 0.f,
			0.f, 0.f, z
		};
	}

	Matrix3 Matrix3::Make2DTransform(const Vector3& trans, const float rot, const Vector3& scale)
	{
		return MakeTranslate(trans) * MakeRotateZ(rot) * MakeScale(scale);
	}

	Matrix3 Matrix3::Make2DTransform(const float transX, const float transY, const float rot, const float scaleX,
	                           const float scaleY)
	{
		return MakeTranslate(transX, transY) * MakeRotateZ(rot) * MakeScale(scaleX, scaleY, 1.f);
	}

	Matrix3 Matrix3::Identity()
	{
		return Matrix3{ 1.f };
	}

	Matrix3 Matrix3::FromRows(const Vector3& row1, const Vector3& row2, const Vector3& row3)
	{
		return
		{
			row1.x, row2.x, row3.x,
			row1.y, row2.y, row3.y,
			row1.z, row2.z, row3.z
		};
	}

	Matrix3 Matrix3::FromCols(const Vector3& col1, const Vector3& col2, const Vector3& col3)
	{
		return { col1, col2, col3 };
	}

	Matrix3 Matrix3::MakeShear(const Vector3& shear)
	{
		return MakeShear(shear.x, shear.y);
	}

	Matrix3 Matrix3::MakeShear(float x, float y)
	{
		return
		{
			1.f, x, 0.f,
			y, 1.f, 0.f,
			0.f, 0.f, 1.f
		};
	}

	Matrix3::Matrix3()
		: m1{ 1.f }, m2{ 0.f }, m3{ 0.f },
		  m4{ 0.f }, m5{ 1.f }, m6{ 0.f },
		  m7{ 0.f }, m8{ 0.f }, m9{ 1.f } { }

	Matrix3::Matrix3(const float scalar)
		: m1{ scalar }, m2{ 0.f }, m3{ 0.f },
		  m4{ 0.f }, m5{ scalar }, m6{ 0.f },
		  m7{ 0.f }, m8{ 0.f }, m9{ scalar } { }

	Matrix3::Matrix3(const Vector3& col1, const Vector3& col2, const Vector3& col3)
		: m1{ col1.x }, m2{ col1.y }, m3{ col1.z },
		  m4{ col2.x }, m5{ col2.y }, m6{ col2.z },
		  m7{ col3.x }, m8{ col3.y }, m9{ col3.z } { }

	Matrix3::Matrix3(const float m1, const float m4, const float m7, const float m2, const float m5, const float m8,
	           const float m3, const float m6, const float m9)
		: m1{ m1 }, m2{ m2 }, m3{ m3 },
		  m4{ m4 }, m5{ m5 }, m6{ m6 },
		  m7{ m7 }, m8{ m8 }, m9{ m9 } { }

	Matrix3::Matrix3(const Matrix3& rhs) = default;

	Matrix3::Matrix3(const mat3& rhs)
		: m1{ 0.f }, m2{ 0.f }, m3{ 0.f },
		  m4{ 0.f }, m5{ 0.f }, m6{ 0.f },
		  m7{ 0.f }, m8{ 0.f }, m9{ 0.f }
	{
		memcpy(&m1, &rhs, sizeof(float) * MATRIX_3_SIZE);
	}

	Vector3 Matrix3::GetRight() const
	{
		return Column(0);
	}

	Vector3 Matrix3::GetUp() const
	{
		return Column(1);
	}

	Vector3 Matrix3::GetForward() const
	{
		return Column(2);
	}

	Vector3 Matrix3::Translation() const
	{
		return { m7, m8, 1.f };
	}

	Vector3 Matrix3::Scale() const
	{
		return { Column(0).Length(), Column(1).Length(), Column(2).Length() };
	}

	float Matrix3::RotationX() const
	{
		return CatalystMath::Atan2(m2, m1);
	}

	float Matrix3::RotationY() const
	{
		return CatalystMath::Atan2(-m4, m5);
	}

	float Matrix3::RotationZ() const
	{
		return CatalystMath::Atan2(m7, m9);
	}

	float Matrix3::Rotation2D() const
	{
		return CatalystMath::Atan2(m2, m1);
	}

	Vector3 Matrix3::Euler() const
	{
		return
		{
			CatalystMath::Degrees(RotationX()),
			CatalystMath::Degrees(RotationY()),
			CatalystMath::Degrees(RotationZ())
		};
	}

	bool Matrix3::IsApproximatelyEqual(const Matrix3& matrix, const float e) const
	{
		for (int i = 0; i < MATRIX_3_SIZE; ++i)
		{
			if (!CatalystMath::Approximately((*this)[i], matrix[i], e))
			{
				return false;
			}
		}

		return true;
	}

	Matrix3 Matrix3::Transposed() const
	{
		return
		{
			m1, m2, m3,
			m4, m5, m6,
			m7, m8, m9
		};
	}

	Matrix3 Matrix3::Inverse() const
	{
		// inverse = adjugate / determinant
		const Matrix3 adj    = Adjugate();
		const float det   = Determinant();
		const float detO1 = 1.f / det;

		return
		{
			detO1 * adj.m1, detO1 * adj.m4, detO1 * adj.m7,
			detO1 * adj.m2, detO1 * adj.m5, detO1 * adj.m8,
			detO1 * adj.m3, detO1 * adj.m6, detO1 * adj.m9
		};
	}

	Matrix3 Matrix3::Minor() const
	{
		// each element is the determinant of the 2x2 submatrix
		// formed by deleting that element's row and column
		return
		{
			m5 * m9 - m6 * m8, m2 * m9 - m3 * m8, m2 * m6 - m3 * m5,
			m4 * m9 - m6 * m7, m1 * m9 - m3 * m7, m1 * m6 - m3 * m4,
			m4 * m8 - m5 * m7, m1 * m8 - m2 * m7, m1 * m5 - m2 * m4
		};
	}

	Matrix3 Matrix3::Cofactor() const
	{
		// apply the checkerboard sign pattern (+ - +  / - + -  / + - +) to the minor matrix
		const Matrix3 minor = Minor();
		return
		{
			+minor.m1, -minor.m4, +minor.m7,
			-minor.m2, +minor.m5, -minor.m8,
			+minor.m3, -minor.m6, +minor.m9
		};
	}

	Matrix3 Matrix3::Adjugate() const
	{
		// the adjugate is the transpose of the cofactor matrix
		const Matrix3 cofactor = Cofactor();
		return cofactor.Transposed();
	}

	float Matrix3::Determinant() const
	{
		// expand along the first column
		const Matrix3 cofactor = Cofactor();
		return m1 * cofactor.m1 + m2 * cofactor.m2 + m3 * cofactor.m3;
	}

	bool Matrix3::IsOrthogonal(const float e) const
	{
		const Matrix3 qT = Transposed() * *this;
		return qT.IsApproximatelyEqual(Identity(), e);
	}

	bool Matrix3::IsIdentity(const float e) const
	{
		return IsApproximatelyEqual(Identity(), e);
	}

	Vector3 Matrix3::Row(const int index) const
	{
		assert(index >= 0 && index < MATRIX_3_ROWS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				return { m1, m4, m7 };
			}
			case 1:
			{
				return { m2, m5, m8 };
			}
			case 2:
			{
				return { m3, m6, m9 };
			}
			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	Vector3 Matrix3::Column(const int index) const
	{
		assert(index >= 0 && index < MATRIX_3_COLS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				return { m1, m2, m3 };
			}

			case 1:
			{
				return { m4, m5, m6 };
			}

			case 2:
			{
				return { m7, m8, m9 };
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix3::SetRow(const int index, const Vector3& newRow)
	{
		assert(index >= 0 && index < MATRIX_3_ROWS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				m1 = newRow.x;
				m4 = newRow.y;
				m7 = newRow.z;
				break;
			}

			case 1:
			{
				m2 = newRow.x;
				m5 = newRow.y;
				m8 = newRow.z;
				break;
			}

			case 2:
			{
				m3 = newRow.x;
				m6 = newRow.y;
				m9 = newRow.z;
				break;
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix3::SetColumn(const int index, const Vector3& newCol)
	{
		assert(index >= 0 && index < MATRIX_3_COLS && "Index out of bounds.");

		switch (index)
		{
			case 0:
			{
				m1 = newCol.x;
				m2 = newCol.y;
				m3 = newCol.z;
				break;
			}

			case 1:
			{
				m4 = newCol.x;
				m5 = newCol.y;
				m6 = newCol.z;
				break;
			}

			case 2:
			{
				m7 = newCol.x;
				m8 = newCol.y;
				m9 = newCol.z;
				break;
			}

			default:
			{
				throw runtime_error("Index out of bounds.");
			}
		}
	}

	void Matrix3::Orthogonalize()
	{
		// Gram-Schmidt process — make each column perpendicular to all previous columns
		// by subtracting the projection of the column onto each prior basis vector
		const Vector3 u1 = Column(0);
		const Vector3 u2 = Column(1);
		const Vector3 u3 = Column(2);

		// remove the component of u2 that points along u1
		const Vector3 prj = u1 * (Vector3::Dot(u2, u1) / Vector3::Dot(u1, u1));
		const Vector3 e2 = u2 - prj;

		// remove the components of u3 that point along u1 and e2
		const Vector3 prj1 = u1 * (Vector3::Dot(u3, u1) / Vector3::Dot(u1, u1));
		const Vector3 prj2 = e2 * (Vector3::Dot(u3, e2) / Vector3::Dot(e2, e2));
		const Vector3 e3 = u3 - prj1 - prj2;

		SetColumn(0, u1);
		SetColumn(1, e2);
		SetColumn(2, e3);
	}

	void Matrix3::Orthonormalize()
	{
		Orthogonalize();

		for (int i = 0; i < MATRIX_3_COLS; ++i)
		{
			SetColumn(i, Column(i).Normalized());
		}
	}

	float Matrix3::Trace() const
	{
		return m1 + m5 + m9;
	}

	Matrix3::operator mat3() const
	{
		return { Column(0), Column(1), Column(2) };
	}

	float* Matrix3::operator*()
	{
		return &m1;
	}

	Matrix3& Matrix3::operator=(const Matrix3& rhs) = default;

	Vector3 Matrix3::operator*(const Vector3& rhs) const
	{
		return
		{
			m1 * rhs.x + m4 * rhs.y + m7 * rhs.z,
			m2 * rhs.x + m5 * rhs.y + m8 * rhs.z,
			m3 * rhs.x + m6 * rhs.y + m9 * rhs.z
		};
	}

	Matrix3 Matrix3::operator*(const Matrix3& rhs) const
	{
		return
		{
			// Column 0 of result
			m1 * rhs.m1 + m4 * rhs.m2 + m7 * rhs.m3,
			m1 * rhs.m4 + m4 * rhs.m5 + m7 * rhs.m6,
			m1 * rhs.m7 + m4 * rhs.m8 + m7 * rhs.m9,
			// Column 1 of result
			m2 * rhs.m1 + m5 * rhs.m2 + m8 * rhs.m3,
			m2 * rhs.m4 + m5 * rhs.m5 + m8 * rhs.m6,
			m2 * rhs.m7 + m5 * rhs.m8 + m8 * rhs.m9,
			// Column 2 of result
			m3 * rhs.m1 + m6 * rhs.m2 + m9 * rhs.m3,
			m3 * rhs.m4 + m6 * rhs.m5 + m9 * rhs.m6,
			m3 * rhs.m7 + m6 * rhs.m8 + m9 * rhs.m9
		};
	}

	Matrix3& Matrix3::operator*=(const Matrix3& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	bool Matrix3::operator==(const Matrix3& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		return IsApproximatelyEqual(rhs);
	}

	bool Matrix3::operator!=(const Matrix3& rhs) const
	{
		if (this == &rhs)
		{
			return false;
		}

		return !IsApproximatelyEqual(rhs);
	}

	float& Matrix3::operator[](const int index)
	{
		assert(index >= 0 && index < MATRIX_3_SIZE && "Index out of bounds.");
		return (&m1)[index];
	}

	const float& Matrix3::operator[](const int index) const
	{
		assert(index >= 0 && index < MATRIX_3_SIZE && "Index out of bounds.");
		return (&m1)[index];
	}
}

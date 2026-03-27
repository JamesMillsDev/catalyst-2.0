/*****************************************************************************
 * Matrix3
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <glm/mat3x3.hpp>
using glm::mat3;

namespace Catalyst::Math
{
	struct Vector3;

	/**
	 * @brief Column-major 3x3 matrix.
	 *
	 * Memory layout:
	 * | m1  m4  m7 |
	 * | m2  m5  m8 |
	 * | m3  m6  m9 |
	 */
	struct Matrix3
	{
	public:
		/**
		 * @brief Creates a 2D translation matrix.
		 * @param trans Translation vector. x and y components are used.
		 * @return A matrix that translates by the given vector.
		 */
		static Matrix3 MakeTranslate(const Vector3& trans);

		/**
		 * @brief Creates a 2D translation matrix.
		 * @param x Translation along the x-axis.
		 * @param y Translation along the y-axis.
		 * @return A matrix that translates by the given values.
		 */
		static Matrix3 MakeTranslate(float x, float y);

		/**
		 * @brief Creates a rotation matrix around the x-axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the x-axis.
		 */
		static Matrix3 MakeRotateX(float rad);

		/**
		 * @brief Creates a rotation matrix around the y-axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the y-axis.
		 */
		static Matrix3 MakeRotateY(float rad);

		/**
		 * @brief Creates a rotation matrix around the z axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the z axis.
		 */
		static Matrix3 MakeRotateZ(float rad);

		/**
		 * @brief Creates a 2D rotation matrix.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates in 2D.
		 */
		static Matrix3 MakeRotate2D(float rad);

		/**
		 * @brief Creates a rotation matrix from Euler angles.
		 * @param euler Euler angles in degrees as (pitch, yaw, roll).
		 * @return A combined rotation matrix.
		 */
		static Matrix3 MakeRotate(const Vector3& euler);

		/**
		 * @brief Creates a scale matrix.
		 * @param scale Scale factors per axis.
		 * @return A matrix that scales by the given vector.
		 */
		static Matrix3 MakeScale(const Vector3& scale);

		/**
		 * @brief Creates a scale matrix.
		 * @param x Scale factor along the x-axis.
		 * @param y Scale factor along the y-axis.
		 * @param z Scale factor along the z-axis.
		 * @return A matrix that scales by the given values.
		 */
		static Matrix3 MakeScale(float x, float y, float z);

		/**
		 * @brief Creates a 2D transform matrix combining translation, rotation, and scale.
		 * @param trans Translation vector.
		 * @param rot Rotation angle in radians.
		 * @param scale Scale vector.
		 * @return A combined 2D transform matrix.
		 */
		static Matrix3 Make2DTransform(const Vector3& trans, float rot, const Vector3& scale);

		/**
		 * @brief Creates a 2D transform matrix combining translation, rotation, and scale.
		 * @param transX Translation along the x-axis.
		 * @param transY Translation along the y-axis.
		 * @param rot Rotation angle in radians.
		 * @param scaleX Scale factor along the x-axis.
		 * @param scaleY Scale factor along the y-axis.
		 * @return A combined 2D transform matrix.
		 */
		static Matrix3 Make2DTransform(float transX, float transY, float rot, float scaleX, float scaleY);

		/**
		 * @brief Returns the identity matrix.
		 * @return A matrix with 1s on the diagonal and 0s elsewhere.
		 */
		static Matrix3 Identity();

		/**
		 * @brief Constructs a matrix from three row vectors.
		 * @param row1 First row.
		 * @param row2 Second row.
		 * @param row3 Third row.
		 * @return A matrix with the given rows.
		 */
		static Matrix3 FromRows(const Vector3& row1, const Vector3& row2, const Vector3& row3);

		/**
		 * @brief Constructs a matrix from three column vectors.
		 * @param col1 First column.
		 * @param col2 Second column.
		 * @param col3 Third column.
		 * @return A matrix with the given columns.
		 */
		static Matrix3 FromCols(const Vector3& col1, const Vector3& col2, const Vector3& col3);

		/**
		 * @brief Creates a 2D shear matrix from a vector.
		 * @param shear x component shears X by Y, y component shears Y by X.
		 * @return A shear matrix.
		 */
		static Matrix3 MakeShear(const Vector3& shear);

		/**
		 * @brief Creates a 2D shear matrix.
		 * @param x Shear X by Y — shifts X proportionally to Y.
		 * @param y Shear Y by X — shifts Y proportionally to X.
		 * @return A shear matrix.
		 */
		static Matrix3 MakeShear(float x, float y);

	public:
		float m1; /**< Column 1, row 1. */
		float m2; /**< Column 1, row 2. */
		float m3; /**< Column 1, row 3. */
		float m4; /**< Column 2, row 1. */
		float m5; /**< Column 2, row 2. */
		float m6; /**< Column 2, row 3. */
		float m7; /**< Column 3, row 1. */
		float m8; /**< Column 3, row 2. */
		float m9; /**< Column 3, row 3. */

	public:
		/**
		 * @brief Constructs the identity matrix.
		 */
		Matrix3();

		/**
		 * @brief Constructs a matrix with a scalar on the diagonal.
		 * @param scalar Value placed at m1, m5, and m9.
		 */
		explicit Matrix3(float scalar);

		/**
		 * @brief Constructs a matrix from three column vectors.
		 * @param col1 First column.
		 * @param col2 Second column.
		 * @param col3 Third column.
		 */
		Matrix3(const Vector3& col1, const Vector3& col2, const Vector3& col3);

		/**
		 * @brief Constructs a matrix from nine floats in row-major order.
		 * @param m1 Row 1, column 1.
		 * @param m4 Row 1, column 2.
		 * @param m7 Row 1, column 3.
		 * @param m2 Row 2, column 1.
		 * @param m5 Row 2, column 2.
		 * @param m8 Row 2, column 3.
		 * @param m3 Row 3, column 1.
		 * @param m6 Row 3, column 2.
		 * @param m9 Row 3, column 3.
		 */
		Matrix3(float m1, float m4, float m7, float m2, float m5, float m8, float m3, float m6, float m9);

		/**
		 * @brief Copy constructor.
		 * @param rhs Matrix to copy.
		 */
		Matrix3(const Matrix3& rhs);

		/**
		 * @brief Constructs a Mat3 from a GLM mat3.
		 * @param rhs GLM matrix to copy.
		 */
		Matrix3(const mat3& rhs);

	public:
		/**
		 * @brief Returns the right vector (first column).
		 * @return The first column as a Vec3.
		 */
		[[nodiscard]] Vector3 GetRight() const;

		/**
		 * @brief Returns the up vector (second column).
		 * @return The second column as a Vec3.
		 */
		[[nodiscard]] Vector3 GetUp() const;

		/**
		 * @brief Returns the forward vector (third column).
		 * @return The third column as a Vec3.
		 */
		[[nodiscard]] Vector3 GetForward() const;

		/**
		 * @brief Extracts the translation component.
		 * @return The translation stored in the matrix.
		 */
		[[nodiscard]] Vector3 Translation() const;

		/**
		 * @brief Extracts the scale component.
		 * @return The scale along each axis.
		 */
		[[nodiscard]] Vector3 Scale() const;

		/**
		 * @brief Extracts the rotation angle around the x-axis.
		 * @return Rotation in radians.
		 */
		[[nodiscard]] float RotationX() const;

		/**
		 * @brief Extracts the rotation angle around the y-axis.
		 * @return Rotation in radians.
		 */
		[[nodiscard]] float RotationY() const;

		/**
		 * @brief Extracts the rotation angle around the z-axis.
		 * @return Rotation in radians.
		 */
		[[nodiscard]] float RotationZ() const;

		/**
		 * @brief Extracts the 2D rotation angle.
		 * @return Rotation in radians.
		 */
		[[nodiscard]] float Rotation2D() const;

		/**
		 * @brief Extracts the rotation as Euler angles.
		 * @return Euler angles in radians as (pitch, yaw, roll).
		 */
		[[nodiscard]] Vector3 Euler() const;

		/**
		 * @brief Checks if this matrix is approximately equal to another.
		 * @param matrix Matrix to compare against.
		 * @param e Maximum per-element difference allowed.
		 * @return True if all elements are within e of each other.
		 */
		[[nodiscard]] bool IsApproximatelyEqual(const Matrix3& matrix, float e = 1e-4f) const;

		/**
		 * @brief Returns the transpose of this matrix.
		 * @return A matrix with rows and columns swapped.
		 */
		[[nodiscard]] Matrix3 Transposed() const;

		/**
		 * @brief Returns the inverse of this matrix.
		 * @return The matrix inverse, computed via the adjugate divided by the determinant.
		 */
		[[nodiscard]] Matrix3 Inverse() const;

		/**
		 * @brief Returns the minor matrix.
		 * @return A matrix where each element is the determinant of the 2x2 submatrix
		 *         formed by deleting that element's row and column.
		 */
		[[nodiscard]] Matrix3 Minor() const;

		/**
		 * @brief Returns the cofactor matrix.
		 * @return The minor matrix with the checkerboard sign pattern applied.
		 */
		[[nodiscard]] Matrix3 Cofactor() const;

		/**
		 * @brief Returns the adjugate (classical adjoint) of this matrix.
		 * @return The transpose of the cofactor matrix.
		 */
		[[nodiscard]] Matrix3 Adjugate() const;

		/**
		 * @brief Computes the determinant of this matrix.
		 * @return The scalar determinant value.
		 */
		[[nodiscard]] float Determinant() const;

		/**
		 * @brief Checks if this matrix is orthogonal.
		 * @param e Tolerance for the comparison against the identity matrix.
		 * @return True if M * Mᵀ is approximately equal to the identity matrix.
		 */
		[[nodiscard]] bool IsOrthogonal(float e = 1e-4f) const;

		/**
		 * @brief Checks if this matrix is approximately the identity matrix.
		 * @param e Maximum per-element difference allowed.
		 * @return True if all elements are within e of the identity matrix.
		 */
		[[nodiscard]] bool IsIdentity(float e = 1e-4f) const;

		/**
		 * @brief Returns the row at the given index.
		 * @param index Row index in the range [0, 2].
		 * @return The row as a Vec3.
		 */
		[[nodiscard]] Vector3 Row(int index) const;

		/**
		 * @brief Returns the column at the given index.
		 * @param index Column index in the range [0, 2].
		 * @return The column as a Vec3.
		 */
		[[nodiscard]] Vector3 Column(int index) const;

		/**
		 * @brief Sets the row at the given index.
		 * @param index Row index in the range [0, 2].
		 * @param newRow New row values.
		 */
		void SetRow(int index, const Vector3& newRow);

		/**
		 * @brief Sets the column at the given index.
		 * @param index Column index in the range [0, 2].
		 * @param newCol New column values.
		 */
		void SetColumn(int index, const Vector3& newCol);

		/**
		 * @brief Orthogonalizes the columns using the Gram-Schmidt process.
		 * Makes each column perpendicular to the others without normalizing their lengths.
		 */
		void Orthogonalize();

		/**
		 * @brief Orthonormalizes the columns using the Gram-Schmidt process.
		 * Makes each column perpendicular to the others and normalizes each to unit length.
		 */
		void Orthonormalize();

		/**
		 * @brief Computes the trace of the matrix.
		 * @return The sum of the diagonal elements m1 + m5 + m9.
		 */
		[[nodiscard]] float Trace() const;

	public:
		/**
		 * @brief Converts this matrix to a GLM mat3.
		 */
		operator mat3() const;

		/**
		 * @brief Returns a pointer to the first element.
		 * @return Raw float pointer to the matrix data.
		 */
		float* operator*();

		/**
		 * @brief Copy assignment operator.
		 * @param rhs Matrix to copy.
		 * @return Reference to this matrix.
		 */
		Matrix3& operator=(const Matrix3& rhs);

		/**
		 * @brief Transforms a vector by this matrix.
		 * @param rhs Vector to transform.
		 * @return The transformed vector.
		 */
		Vector3 operator*(const Vector3& rhs) const;

		/**
		 * @brief Multiplies two matrices.
		 * @param rhs Right-hand side matrix.
		 * @return The matrix product.
		 */
		Matrix3 operator*(const Matrix3& rhs) const;

		/**
		 * @brief Multiplies this matrix by another in place.
		 * @param rhs Right-hand side matrix.
		 * @return Reference to this matrix after multiplication.
		 */
		Matrix3& operator*=(const Matrix3& rhs);

		/**
		 * @brief Checks equality between two matrices.
		 * @param rhs Matrix to compare against.
		 * @return True if all elements are exactly equal.
		 */
		bool operator==(const Matrix3& rhs) const;

		/**
		 * @brief Checks inequality between two matrices.
		 * @param rhs Matrix to compare against.
		 * @return True if any element differs.
		 */
		bool operator!=(const Matrix3& rhs) const;

		/**
		 * @brief Returns a reference to the element at the given index.
		 * @param index Element index in the range [0, 8], in column-major order.
		 * @return Reference to the element.
		 */
		float& operator[](int index);

		/**
		 * @brief Returns a const reference to the element at the given index.
		 * @param index Element index in the range [0, 8], in column-major order.
		 * @return Const reference to the element.
		 */
		const float& operator[](int index) const;
	};
}

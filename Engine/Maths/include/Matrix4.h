/*****************************************************************************
 * Matrix4
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <glm/mat4x4.hpp>
using glm::mat4;

namespace Catalyst::Math
{
	struct Vector3;
	struct Vector4;
	struct Matrix3;

	/**
	 * @brief Column-major 4x4 matrix.
	 *
	 * Memory layout:
	 * | m1   m5   m9  m13 |
	 * | m2   m6  m10  m14 |
	 * | m3   m7  m11  m15 |
	 * | m4   m8  m12  m16 |
	 */
	struct Matrix4
	{
	public:
		/**
		 * @brief Creates a translation matrix.
		 * @param trans Translation vector.
		 * @return A matrix that translates by the given vector.
		 */
		static Matrix4 MakeTranslate(const Vector3& trans);

		/**
		 * @brief Creates a translation matrix.
		 * @param x Translation along the x-axis.
		 * @param y Translation along the y-axis.
		 * @param z Translation along the z-axis.
		 * @return A matrix that translates by the given values.
		 */
		static Matrix4 MakeTranslate(float x, float y, float z);

		/**
		 * @brief Creates a rotation matrix around the x-axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the x-axis.
		 */
		static Matrix4 MakeRotateX(float rad);

		/**
		 * @brief Creates a rotation matrix around the y-axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the y-axis.
		 */
		static Matrix4 MakeRotateY(float rad);

		/**
		 * @brief Creates a rotation matrix around the z-axis.
		 * @param rad Angle in radians.
		 * @return A matrix that rotates around the z-axis.
		 */
		static Matrix4 MakeRotateZ(float rad);

		/**
		 * @brief Creates a rotation matrix from Euler angles.
		 * @param euler Euler angles in degrees as (pitch, yaw, roll).
		 * @return A combined rotation matrix.
		 */
		static Matrix4 MakeRotate(const Vector3& euler);

		/**
		 * @brief Creates a scale matrix.
		 * @param scale Scale factors per axis.
		 * @return A matrix that scales by the given vector.
		 */
		static Matrix4 MakeScale(const Vector3& scale);

		/**
		 * @brief Creates a scale matrix.
		 * @param x Scale factor along the x-axis.
		 * @param y Scale factor along the y-axis.
		 * @param z Scale factor along the z-axis.
		 * @return A matrix that scales by the given values.
		 */
		static Matrix4 MakeScale(float x, float y, float z);

		/**
		 * @brief Creates a transform matrix combining translation, rotation, and scale.
		 * @param trans Translation vector.
		 * @param euler Rotation in Euler degrees.
		 * @param scale Scale vector.
		 * @return A combined transform matrix.
		 */
		static Matrix4 MakeTransform(const Vector3& trans, const Vector3& euler, const Vector3& scale);

		/**
		 * @brief Creates a perspective projection matrix.
		 * @param fovY Vertical field of view in radians.
		 * @param aspect Aspect ratio (width / height).
		 * @param near Near clipping plane distance.
		 * @param far Far clipping plane distance.
		 * @return A perspective projection matrix.
		 */
		static Matrix4 MakePerspective(float fovY, float aspect, float near, float far);

		/**
		 * @brief Creates an orthographic projection matrix.
		 * @param left Left clipping plane.
		 * @param right Right clipping plane.
		 * @param bottom Bottom clipping plane.
		 * @param top Top clipping plane.
		 * @param near Near clipping plane distance.
		 * @param far Far clipping plane distance.
		 * @return An orthographic projection matrix.
		 */
		static Matrix4 MakeOrthographic(float left, float right, float bottom, float top, float near, float far);

		/**
		 * @brief Creates a look-at view matrix.
		 * @param eye Position of the camera.
		 * @param target Position the camera is looking at.
		 * @param up World up vector.
		 * @return A view matrix looking from eye toward target.
		 */
		static Matrix4 MakeLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

		/**
		 * @brief Returns the identity matrix.
		 * @return A matrix with 1s on the diagonal and 0s elsewhere.
		 */
		static Matrix4 Identity();

		/**
		 * @brief Constructs a matrix from four row vectors.
		 * @param row1 First row.
		 * @param row2 Second row.
		 * @param row3 Third row.
		 * @param row4 Fourth row.
		 * @return A matrix with the given rows.
		 */
		static Matrix4 FromRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);

		/**
		 * @brief Constructs a matrix from four column vectors.
		 * @param col1 First column.
		 * @param col2 Second column.
		 * @param col3 Third column.
		 * @param col4 Fourth column.
		 * @return A matrix with the given columns.
		 */
		static Matrix4 FromCols(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4);

	public:
		float m1;  /**< Column 1, row 1. */
		float m2;  /**< Column 1, row 2. */
		float m3;  /**< Column 1, row 3. */
		float m4;  /**< Column 1, row 4. */
		float m5;  /**< Column 2, row 1. */
		float m6;  /**< Column 2, row 2. */
		float m7;  /**< Column 2, row 3. */
		float m8;  /**< Column 2, row 4. */
		float m9;  /**< Column 3, row 1. */
		float m10; /**< Column 3, row 2. */
		float m11; /**< Column 3, row 3. */
		float m12; /**< Column 3, row 4. */
		float m13; /**< Column 4, row 1. */
		float m14; /**< Column 4, row 2. */
		float m15; /**< Column 4, row 3. */
		float m16; /**< Column 4, row 4. */

	public:
		/**
		 * @brief Constructs the identity matrix.
		 */
		Matrix4();

		/**
		 * @brief Constructs a matrix with a scalar on the diagonal.
		 * @param scalar Value placed at m1, m6, m11, and m16.
		 */
		explicit Matrix4(float scalar);

		/**
		 * @brief Constructs a matrix from four column vectors.
		 * @param col1 First column.
		 * @param col2 Second column.
		 * @param col3 Third column.
		 * @param col4 Fourth column.
		 */
		Matrix4(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4);

		/**
		 * @brief Constructs a Mat4 from a Mat3, placing it in the upper-left and filling the rest with the identity.
		 * @param mat The 3x3 matrix to embed.
		 */
		explicit Matrix4(const Matrix3& mat);

		/**
		 * @brief Constructs a matrix from sixteen floats in column-major order.
		 * @param m1  Column 1, row 1.
		 * @param m2  Column 1, row 2.
		 * @param m3  Column 1, row 3.
		 * @param m4  Column 1, row 4.
		 * @param m5  Column 2, row 1.
		 * @param m6  Column 2, row 2.
		 * @param m7  Column 2, row 3.
		 * @param m8  Column 2, row 4.
		 * @param m9  Column 3, row 1.
		 * @param m10 Column 3, row 2.
		 * @param m11 Column 3, row 3.
		 * @param m12 Column 3, row 4.
		 * @param m13 Column 4, row 1.
		 * @param m14 Column 4, row 2.
		 * @param m15 Column 4, row 3.
		 * @param m16 Column 4, row 4.
		 */
		Matrix4(float m1,  float m2,  float m3,  float m4,
		        float m5,  float m6,  float m7,  float m8,
		        float m9,  float m10, float m11, float m12,
		        float m13, float m14, float m15, float m16);

		/**
		 * @brief Copy constructor.
		 * @param rhs Matrix to copy.
		 */
		Matrix4(const Matrix4& rhs);

		/**
		 * @brief Constructs a Mat4 from a GLM mat4.
		 * @param rhs GLM matrix to copy.
		 */
		Matrix4(const mat4& rhs);

	public:
		/**
		 * @brief Returns the right vector (first column, xyz).
		 * @return The first column as a Vector3.
		 */
		[[nodiscard]] Vector3 GetRight() const;

		/**
		 * @brief Returns the up vector (second column, xyz).
		 * @return The second column as a Vector3.
		 */
		[[nodiscard]] Vector3 GetUp() const;

		/**
		 * @brief Returns the forward vector (third column, xyz).
		 * @return The third column as a Vector3.
		 */
		[[nodiscard]] Vector3 GetForward() const;

		/**
		 * @brief Extracts the translation component.
		 * @return The translation stored in the fourth column.
		 */
		[[nodiscard]] Vector3 Translation() const;

		/**
		 * @brief Extracts the scale component.
		 * @return The scale along each axis, derived from column lengths.
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
		 * @brief Extracts the rotation as Euler angles.
		 * @return Euler angles in degrees as (pitch, yaw, roll).
		 */
		[[nodiscard]] Vector3 Euler() const;

		/**
		 * @brief Extracts the upper-left 3x3 submatrix.
		 * @return The rotation/scale portion of this matrix.
		 */
		[[nodiscard]] Matrix3 ToMat3() const;

		/**
		 * @brief Checks if this matrix is approximately equal to another.
		 * @param matrix Matrix to compare against.
		 * @param e Maximum per-element difference allowed.
		 * @return True if all elements are within e of each other.
		 */
		[[nodiscard]] bool IsApproximatelyEqual(const Matrix4& matrix, float e = 1e-4f) const;

		/**
		 * @brief Returns the transpose of this matrix.
		 * @return A matrix with rows and columns swapped.
		 */
		[[nodiscard]] Matrix4 Transposed() const;

		/**
		 * @brief Returns the inverse of this matrix.
		 * @return The matrix inverse, computed via the adjugate divided by the determinant.
		 */
		[[nodiscard]] Matrix4 Inverse() const;

		/**
		 * @brief Returns the minor matrix.
		 * @return A matrix where each element is the determinant of the 3x3 submatrix
		 *         formed by deleting that element's row and column.
		 */
		[[nodiscard]] Matrix4 Minor() const;

		/**
		 * @brief Returns the cofactor matrix.
		 * @return The minor matrix with the checkerboard sign pattern applied.
		 */
		[[nodiscard]] Matrix4 Cofactor() const;

		/**
		 * @brief Returns the adjugate (classical adjoint) of this matrix.
		 * @return The transpose of the cofactor matrix.
		 */
		[[nodiscard]] Matrix4 Adjugate() const;

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
		 * @param index Row index in the range [0, 3].
		 * @return The row as a Vector4.
		 */
		[[nodiscard]] Vector4 Row(int index) const;

		/**
		 * @brief Returns the column at the given index.
		 * @param index Column index in the range [0, 3].
		 * @return The column as a Vector4.
		 */
		[[nodiscard]] Vector4 Column(int index) const;

		/**
		 * @brief Sets the row at the given index.
		 * @param index Row index in the range [0, 3].
		 * @param newRow New row values.
		 */
		void SetRow(int index, const Vector4& newRow);

		/**
		 * @brief Sets the column at the given index.
		 * @param index Column index in the range [0, 3].
		 * @param newCol New column values.
		 */
		void SetColumn(int index, const Vector4& newCol);

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
		 * @return The sum of the diagonal elements m1 + m6 + m11 + m16.
		 */
		[[nodiscard]] float Trace() const;

	public:
		/**
		 * @brief Converts this matrix to a GLM mat4.
		 */
		operator mat4() const;

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
		Matrix4& operator=(const Matrix4& rhs);

		/**
		 * @brief Transforms a vector by this matrix.
		 * @param rhs Vector to transform.
		 * @return The transformed vector.
		 */
		Vector4 operator*(const Vector4& rhs) const;

		/**
		 * @brief Multiplies two matrices.
		 * @param rhs Right-hand side matrix.
		 * @return The matrix product.
		 */
		Matrix4 operator*(const Matrix4& rhs) const;

		/**
		 * @brief Multiplies this matrix by another in place.
		 * @param rhs Right-hand side matrix.
		 * @return Reference to this matrix after multiplication.
		 */
		Matrix4& operator*=(const Matrix4& rhs);

		/**
		 * @brief Checks equality between two matrices.
		 * @param rhs Matrix to compare against.
		 * @return True if all elements are approximately equal.
		 */
		bool operator==(const Matrix4& rhs) const;

		/**
		 * @brief Checks inequality between two matrices.
		 * @param rhs Matrix to compare against.
		 * @return True if any element differs.
		 */
		bool operator!=(const Matrix4& rhs) const;

		/**
		 * @brief Returns a reference to the element at the given index.
		 * @param index Element index in the range [0, 15], in column-major order.
		 * @return Reference to the element.
		 */
		float& operator[](int index);

		/**
		 * @brief Returns a const reference to the element at the given index.
		 * @param index Element index in the range [0, 15], in column-major order.
		 * @return Const reference to the element.
		 */
		const float& operator[](int index) const;
	};
}
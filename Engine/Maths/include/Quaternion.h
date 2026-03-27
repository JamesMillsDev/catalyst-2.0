/*****************************************************************************
 * Quaternion
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <ostream>
#include <glm/gtc/quaternion.hpp>

using std::ostream;
using glm::quat;

namespace Catalyst::Math
{
	struct Vector3;
	struct Vector4;
	struct Matrix3;
	struct Matrix4;

	/**
	 * @brief A quaternion for representing 3D rotations.
	 *
	 * Stored as (x, y, z, w) where w is the scalar component.
	 */
	struct Quat
	{
	public:
		static const Quat IDENTITY; /**< (0, 0, 0, 1) */

	public:
		/**
		 * @brief Computes the dot product of two quaternions.
		 * @param lhs Left-hand quaternion.
		 * @param rhs Right-hand quaternion.
		 * @return The scalar dot product.
		 */
		static float Dot(const Quat& lhs, const Quat& rhs);

		/**
		 * @brief Spherically interpolates between two quaternions.
		 * @param a Start quaternion.
		 * @param b End quaternion.
		 * @param t Interpolation factor in the range [0, 1].
		 * @return The interpolated quaternion.
		 */
		static Quat Slerp(const Quat& a, const Quat& b, float t);

		/**
		 * @brief Linearly interpolates between two quaternions and normalises the result.
		 * @param a Start quaternion.
		 * @param b End quaternion.
		 * @param t Interpolation factor in the range [0, 1].
		 * @return The interpolated and normalised quaternion.
		 */
		static Quat Lerp(const Quat& a, const Quat& b, float t);

		/**
		 * @brief Returns a normalised copy of the given quaternion.
		 * @param rhs Quaternion to normalise.
		 * @return A unit-length quaternion.
		 */
		static Quat Normalised(const Quat& rhs);

		/**
		 * @brief Computes the angle between two quaternions in radians.
		 * @param lhs First quaternion.
		 * @param rhs Second quaternion.
		 * @return The angle in radians.
		 */
		static float AngleBetween(const Quat& lhs, const Quat& rhs);

		/**
		 * @brief Creates a quaternion from an axis and angle.
		 * @param axis The axis of rotation, assumed to be unit length.
		 * @param rad Angle in radians.
		 * @return A quaternion representing the rotation.
		 */
		static Quat FromAxisAngle(const Vector3& axis, float rad);

		/**
		 * @brief Creates a quaternion from Euler angles.
		 * @param euler Euler angles in degrees as (pitch, yaw, roll).
		 * @return A quaternion representing the rotation.
		 */
		static Quat FromEuler(const Vector3& euler);

		/**
		 * @brief Creates a quaternion from Euler angles.
		 * @param pitch Rotation around the x-axis in degrees.
		 * @param yaw Rotation around the y-axis in degrees.
		 * @param roll Rotation around the z-axis in degrees.
		 * @return A quaternion representing the rotation.
		 */
		static Quat FromEuler(float pitch, float yaw, float roll);

		/**
		 * @brief Creates a quaternion from a rotation matrix.
		 * @param mat A pure rotation matrix.
		 * @return A quaternion representing the same rotation.
		 */
		static Quat FromMatrix3(const Matrix3& mat);

		/**
		 * @brief Creates a quaternion representing the rotation from one direction to another.
		 * @param from Source direction, assumed to be unit length.
		 * @param to Target direction, assumed to be unit length.
		 * @return A quaternion that rotates from to to.
		 */
		static Quat FromToRotation(const Vector3& from, const Vector3& to);

		/**
		 * @brief Creates a quaternion that rotates to look in the given direction.
		 * @param forward Forward direction, assumed to be unit length.
		 * @param up Up vector, assumed to be unit length.
		 * @return A quaternion representing the look rotation.
		 */
		static Quat LookRotation(const Vector3& forward, const Vector3& up);

	public:
		float x; /**< X imaginary component. */
		float y; /**< Y imaginary component. */
		float z; /**< Z imaginary component. */
		float w; /**< W scalar component. */

	public:
		/**
		 * @brief Constructs the identity quaternion (0, 0, 0, 1).
		 */
		Quat();

		/**
		 * @brief Constructs a quaternion from four scalar values.
		 * @param x X imaginary component.
		 * @param y Y imaginary component.
		 * @param z Z imaginary component.
		 * @param w W scalar component.
		 */
		Quat(float x, float y, float z, float w);

		/**
		 * @brief Constructs a quaternion from a Vector4.
		 * @param vec The vector to copy components from.
		 */
		explicit Quat(const Vector4& vec);

		/**
		 * @brief Constructs a Quat from a GLM quat.
		 * @param rhs GLM quaternion to copy.
		 */
		Quat(const quat& rhs);

		/**
		 * @brief Copy constructor.
		 * @param rhs Quaternion to copy.
		 */
		Quat(const Quat& rhs);

	public:
		/**
		 * @brief Computes the dot product with another quaternion.
		 * @param rhs Right-hand quaternion.
		 * @return The scalar dot product.
		 */
		[[nodiscard]] float Dot(const Quat& rhs) const;

		/**
		 * @brief Computes the length of the quaternion.
		 * @return The scalar length.
		 */
		[[nodiscard]] float Length() const;

		/**
		 * @brief Computes the squared length of the quaternion.
		 * @return The squared length, avoiding a square root.
		 */
		[[nodiscard]] float LengthSqr() const;

		/**
		 * @brief Normalises this quaternion in place.
		 */
		void Normalise();

		/**
		 * @brief Returns a normalised copy of this quaternion.
		 * @return A unit-length quaternion.
		 */
		[[nodiscard]] Quat Normalised() const;

		/**
		 * @brief Returns the conjugate of this quaternion.
		 * @return A quaternion with the imaginary components negated.
		 */
		[[nodiscard]] Quat Conjugate() const;

		/**
		 * @brief Returns the inverse of this quaternion.
		 * @return The conjugate divided by the squared length.
		 */
		[[nodiscard]] Quat Inverse() const;

		/**
		 * @brief Checks if this quaternion is approximately equal to another.
		 * @param rhs Quaternion to compare against.
		 * @param e Maximum per-component difference allowed.
		 * @return True if all components are within e of each other.
		 */
		[[nodiscard]] bool IsApproximatelyEqual(const Quat& rhs, float e = 1e-4f) const;

		/**
		 * @brief Computes the angle between this quaternion and another in radians.
		 * @param rhs Other quaternion.
		 * @return The angle in radians.
		 */
		[[nodiscard]] float AngleBetween(const Quat& rhs) const;

		/**
		 * @brief Extracts the axis of rotation.
		 * @return The unit axis of rotation.
		 */
		[[nodiscard]] Vector3 Axis() const;

		/**
		 * @brief Extracts the angle of rotation.
		 * @return The angle in radians.
		 */
		[[nodiscard]] float Angle() const;

		/**
		 * @brief Converts this quaternion to Euler angles.
		 * @return Euler angles in degrees as (pitch, yaw, roll).
		 */
		[[nodiscard]] Vector3 ToEuler() const;

		/**
		 * @brief Converts this quaternion to a 3x3 rotation matrix.
		 * @return A pure rotation matrix.
		 */
		[[nodiscard]] Matrix3 ToMatrix3() const;

		/**
		 * @brief Converts this quaternion to a 4x4 rotation matrix.
		 * @return A rotation matrix with identity translation.
		 */
		[[nodiscard]] Matrix4 ToMat4() const;

		/**
		 * @brief Rotates a vector by this quaternion.
		 * @param vec Vector to rotate.
		 * @return The rotated vector.
		 */
		[[nodiscard]] Vector3 Rotate(const Vector3& vec) const;

		/**
		 * @brief Returns the forward vector of this rotation.
		 * @return The forward direction as a Vector3.
		 */
		[[nodiscard]] Vector3 GetForward() const;

		/**
		 * @brief Returns the up vector of this rotation.
		 * @return The up direction as a Vector3.
		 */
		[[nodiscard]] Vector3 GetUp() const;

		/**
		 * @brief Returns the right vector of this rotation.
		 * @return The right direction as a Vector3.
		 */
		[[nodiscard]] Vector3 GetRight() const;

	public:
		/**
		 * @brief Writes the quaternion to an output stream as (x, y, z, w).
		 */
		friend ostream& operator<<(ostream& stream, const Quat& q);

		/**
		 * @brief Converts this quaternion to a GLM quat.
		 */
		operator quat() const;

		/**
		 * @brief Converts this quaternion to a Vector4.
		 */
		operator Vector4() const;

		/**
		 * @brief Copy assignment operator.
		 * @param rhs Quaternion to copy.
		 * @return Reference to this quaternion.
		 */
		Quat& operator=(const Quat& rhs);

		/**
		 * @brief Returns the inverse rotation.
		 * @return The conjugate of this quaternion.
		 */
		Quat operator-() const;

		/**
		 * @brief Checks equality between two quaternions.
		 * @param rhs Quaternion to compare against.
		 * @return True if all components are approximately equal.
		 */
		bool operator==(const Quat& rhs) const;

		/**
		 * @brief Checks inequality between two quaternions.
		 * @param rhs Quaternion to compare against.
		 * @return True if any component differs.
		 */
		bool operator!=(const Quat& rhs) const;

		/**
		 * @brief Multiplies two quaternions, combining their rotations.
		 * @param rhs Right-hand quaternion.
		 * @return The combined rotation.
		 */
		Quat operator*(const Quat& rhs) const;

		/**
		 * @brief Multiplies this quaternion by another in place.
		 * @param rhs Right-hand quaternion.
		 * @return Reference to this quaternion.
		 */
		Quat& operator*=(const Quat& rhs);

		/**
		 * @brief Rotates a vector by this quaternion.
		 * @param rhs Vector to rotate.
		 * @return The rotated vector.
		 */
		Vector3 operator*(const Vector3& rhs) const;

		/**
		 * @brief Multiplies all components by a scalar.
		 * @param rhs Scalar value.
		 * @return The scaled quaternion.
		 */
		Quat operator*(float rhs) const;

		/**
		 * @brief Multiplies all components by a scalar in place.
		 * @param rhs Scalar value.
		 * @return Reference to this quaternion.
		 */
		Quat& operator*=(float rhs);

		/**
		 * @brief Adds two quaternions component-wise.
		 * @param rhs Right-hand quaternion.
		 * @return The sum quaternion.
		 */
		Quat operator+(const Quat& rhs) const;

		/**
		 * @brief Adds another quaternion to this one in place.
		 * @param rhs Right-hand quaternion.
		 * @return Reference to this quaternion.
		 */
		Quat& operator+=(const Quat& rhs);

		/**
		 * @brief Returns a reference to the component at the given index.
		 * @param index Component index: 0=x, 1=y, 2=z, 3=w.
		 * @return Reference to the component.
		 */
		float& operator[](int index);

		/**
		 * @brief Returns a const reference to the component at the given index.
		 * @param index Component index: 0=x, 1=y, 2=z, 3=w.
		 * @return Const reference to the component.
		 */
		const float& operator[](int index) const;
	};
}

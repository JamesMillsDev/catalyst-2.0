/*****************************************************************************
 * Vector3
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <ostream>
#include <glm/vec3.hpp>

using glm::vec3;
using std::ostream;

namespace Catalyst::Math
{
	struct Vector2;
	struct Vector4;

	/**
	 * @brief A 3D vector with interoperability for Raylib and GLM.
	 */
	struct Vector3
	{
	 public:
        static const Vector3 ZERO;    /**< (0, 0, 0) */
        static const Vector3 ONE;     /**< (1, 1, 1) */
        static const Vector3 HALF;    /**< (0.5, 0.5, 0.5) */

        static const Vector3 UP;      /**< (0, 1, 0) */
        static const Vector3 DOWN;    /**< (0, -1, 0) */
        static const Vector3 LEFT;    /**< (-1, 0, 0) */
        static const Vector3 RIGHT;   /**< (1, 0, 0) */
        static const Vector3 FORWARD; /**< (0, 0, 1) */
        static const Vector3 BACK;    /**< (0, 0, -1) */

    public:
        /**
         * @brief Computes the dot product of two vectors.
         * @param lhs Left-hand vector.
         * @param rhs Right-hand vector.
         * @return The scalar dot product.
         */
        static float Dot(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Computes the cross product of two vectors. w component is ignored.
         * @param lhs Left-hand vector.
         * @param rhs Right-hand vector.
         * @return The cross product with w set to 0.
         */
        static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Linearly interpolates between two vectors.
         * @param a Start vector.
         * @param b End vector.
         * @param t Interpolation factor in the range [0, 1].
         * @return The interpolated vector.
         */
        static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

        /**
         * @brief Computes the angle between two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return The angle in radians.
         */
        static float AngleBetween(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Computes the distance between two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return The scalar distance.
         */
        static float Distance(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Returns the component-wise minimum of two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return A vector with the smallest value in each component.
         */
        static Vector3 Min(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Returns the component-wise maximum of two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return A vector with the largest value in each component.
         */
        static Vector3 Max(const Vector3& lhs, const Vector3& rhs);

        /**
         * @brief Returns the component-wise absolute value of a vector.
         * @param vec Vector to apply to.
         * @return A vector with all non-negative components.
         */
        static Vector3 Abs(const Vector3& vec);

        /**
         * @brief Clamps each component of a vector between min and max.
         * @param val Vector to clamp.
         * @param min Minimum values per component.
         * @param max Maximum values per component.
         * @return The clamped vector.
         */
        static Vector3 Clamp(const Vector3& val, const Vector3& min, const Vector3& max);

        /**
         * @brief Reflects a vector off a surface with the given normal.
         * @param vec Incident vector.
         * @param normal Surface normal, assumed to be unit length.
         * @return The reflected vector.
         */
        static Vector3 Reflect(const Vector3& vec, const Vector3& normal);

        /**
         * @brief Projects a vector onto another vector.
         * @param vec Vector to project.
         * @param onto Vector to project onto, assumed to be unit length.
         * @return The projected vector.
         */
        static Vector3 Project(const Vector3& vec, const Vector3& onto);

    public:
        float x; /**< X component. */
        float y; /**< Y component. */
        float z; /**< Z component. */

    public:
        /**
         * @brief Constructs a zero vector.
         */
        Vector3();

        /**
         * @brief Constructs a vector with all components set to the given scalar.
         * @param scalar Value for all components.
         */
        Vector3(float scalar);

        /**
         * @brief Constructs a vector from a Vec2 and two scalars.
         * @param xy x and y components.
         * @param z Z component.
         */
        Vector3(const Vector2& xy, float z);

        /**
         * @brief Constructs a vector from a Vec4 dropping the w.
         * @param xyzw x, y and z components.
         */
        Vector3(const Vector4& xyzw);

        /**
         * @brief Constructs a vector from four scalar values.
         * @param x X component.
         * @param y Y component.
         * @param z Z component.
         */
        Vector3(float x, float y, float z);

        /**
         * @brief Constructs a Vec4 from a GLM vec4.
         * @param rhs GLM vector to copy.
         */
        Vector3(const vec3& rhs);

        /**
         * @brief Copy constructor.
         * @param rhs Vector to copy.
         */
        Vector3(const Vector3& rhs);

    public:
        /**
         * @brief Computes the dot product with another vector.
         * @param rhs Right-hand vector.
         * @return The scalar dot product.
         */
        [[nodiscard]] float Dot(const Vector3& rhs) const;

        /**
         * @brief Computes the cross product with another vector.
         * @param rhs Right-hand vector.
         * @return The cross product.
         */
        [[nodiscard]] Vector3 Cross(const Vector3& rhs) const;

        /**
         * @brief Computes the length of the vector.
         * @return The scalar length.
         */
        [[nodiscard]] float Length() const;

        /**
         * @brief Computes the squared length of the vector.
         * @return The squared length, avoiding a square root.
         */
        [[nodiscard]] float LengthSqr() const;

        /**
         * @brief Normalises this vector in place.
         */
        void Normalize();

        /**
         * @brief Returns a normalised copy of this vector.
         * @return A unit-length vector in the same direction.
         */
        [[nodiscard]] Vector3 Normalized() const;

        /**
         * @brief Checks if this vector is approximately equal to another.
         * @param rhs Vector to compare against.
         * @param e Maximum per-component difference allowed.
         * @return True if all components are within e of each other.
         */
        [[nodiscard]] bool IsApproximatelyEqual(const Vector3& rhs, float e = 1e-4f) const;

        /**
         * @brief Computes the angle between this vector and another.
         * @param rhs Other vector.
         * @return The angle in radians.
         */
        [[nodiscard]] float AngleBetween(const Vector3& rhs) const;

        /**
         * @brief Computes the distance to another vector.
         * @param rhs Other vector.
         * @return The scalar distance.
         */
        [[nodiscard]] float Distance(const Vector3& rhs) const;

        /**
         * @brief Returns the component-wise minimum of this vector and another.
         * @param rhs Other vector.
         * @return A vector with the smallest value in each component.
         */
        [[nodiscard]] Vector3 Min(const Vector3& rhs) const;

        /**
         * @brief Returns the component-wise maximum of this vector and another.
         * @param rhs Other vector.
         * @return A vector with the largest value in each component.
         */
        [[nodiscard]] Vector3 Max(const Vector3& rhs) const;

        /**
         * @brief Returns the component-wise absolute value of this vector.
         * @return A vector with all non-negative components.
         */
        [[nodiscard]] Vector3 Abs() const;

        /**
         * @brief Clamps each component between min and max.
         * @param min Minimum values per component.
         * @param max Maximum values per component.
         * @return The clamped vector.
         */
        [[nodiscard]] Vector3 Clamp(const Vector3& min, const Vector3& max) const;

        /**
         * @brief Reflects this vector off a surface with the given normal.
         * @param normal Surface normal, assumed to be unit length.
         * @return The reflected vector.
         */
        [[nodiscard]] Vector3 Reflect(const Vector3& normal) const;

        /**
         * @brief Projects this vector onto another vector.
         * @param onto Vector to project onto, assumed to be unit length.
         * @return The projected vector.
         */
        [[nodiscard]] Vector3 Project(const Vector3& onto) const;

    public:
        /**
         * @brief Writes the vector to an output stream as (x, y, z, w).
         */
        friend ostream& operator<<(ostream& stream, const Vector3& vec);

        /**
         * @brief Converts this vector to a GLM vec4.
         */
        operator vec3() const;

        /**
         * @brief Converts this vector to a Vec2, discarding z and w.
         */
        operator Vector2() const;

        /**
         * @brief Converts this vector to a Vec3, discarding w.
         */
        operator Vector4() const;

        /**
         * @brief Copy assignment operator.
         * @param rhs Vector to copy.
         * @return Reference to this vector.
         */
        Vector3& operator=(const Vector3& rhs);

        /**
         * @brief Negates all components.
         * @return A vector with all components negated.
         */
        Vector3 operator-() const;

        /**
         * @brief Checks equality between two vectors.
         * @param rhs Vector to compare against.
         * @return True if all components are approximately equal.
         */
        bool operator==(const Vector3& rhs) const;

        /**
         * @brief Checks inequality between two vectors.
         * @param rhs Vector to compare against.
         * @return True if any component differs.
         */
        bool operator!=(const Vector3& rhs) const;

        /**
         * @brief Less-than comparison for use as a map key. No geometric meaning.
         * @param rhs Vector to compare against.
         * @return True if this vector is lexicographically less than rhs.
         */
        bool operator<(const Vector3& rhs) const;

        /**
         * @brief Adds two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The sum vector.
         */
        Vector3 operator+(const Vector3& rhs) const;

        /**
         * @brief Adds another vector to this one in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector3& operator+=(const Vector3& rhs);

        /**
         * @brief Subtracts two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The difference vector.
         */
        Vector3 operator-(const Vector3& rhs) const;

        /**
         * @brief Subtracts another vector from this one in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector3& operator-=(const Vector3& rhs);

        /**
         * @brief Multiplies two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The product vector.
         */
        Vector3 operator*(const Vector3& rhs) const;

        /**
         * @brief Multiplies this vector by another component-wise in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector3& operator*=(const Vector3& rhs);

        /**
         * @brief Multiplies all components by a scalar.
         * @param rhs Scalar value.
         * @return The scaled vector.
         */
        Vector3 operator*(float rhs) const;

        /**
         * @brief Multiplies all components by a scalar in place.
         * @param rhs Scalar value.
         * @return Reference to this vector.
         */
        Vector3& operator*=(float rhs);

        /**
         * @brief Divides all components by a scalar.
         * @param rhs Scalar value.
         * @return The scaled vector.
         */
        Vector3 operator/(float rhs) const;

        /**
         * @brief Divides all components by a scalar in place.
         * @param rhs Scalar value.
         * @return Reference to this vector.
         */
        Vector3& operator/=(float rhs);

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

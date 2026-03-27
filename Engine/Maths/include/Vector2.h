/*****************************************************************************
 * Vector2
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <ostream>
#include <glm/vec2.hpp>

using glm::vec2;
using std::ostream;

namespace Catalyst::Math
{
	struct Vector3;
    struct Vector4;

    /**
     * @brief A 2D vector with interoperability for Raylib and GLM.
     */
    struct Vector2
    {
    public:
        static const Vector2 ZERO;  /**< (0, 0) */
        static const Vector2 ONE;   /**< (1, 1) */
        static const Vector2 HALF;  /**< (0.5, 0.5) */

        static const Vector2 UP;    /**< (0, 1) */
        static const Vector2 DOWN;  /**< (0, -1) */
        static const Vector2 LEFT;  /**< (-1, 0) */
        static const Vector2 RIGHT; /**< (1, 0) */

    public:
        /**
         * @brief Computes the dot product of two vectors.
         * @param lhs Left-hand vector.
         * @param rhs Right-hand vector.
         * @return The scalar dot product.
         */
        static float Dot(const Vector2& lhs, const Vector2& rhs);

        /**
         * @brief Linearly interpolates between two vectors.
         * @param a Start vector.
         * @param b End vector.
         * @param t Interpolation factor in the range [0, 1].
         * @return The interpolated vector.
         */
        static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

        /**
         * @brief Computes the angle between two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return The angle in radians.
         */
        static float AngleBetween(const Vector2& lhs, const Vector2& rhs);

        /**
         * @brief Computes the distance between two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return The scalar distance.
         */
        static float Distance(const Vector2& lhs, const Vector2& rhs);

        /**
         * @brief Returns the component-wise minimum of two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return A vector with the smallest value in each component.
         */
        static Vector2 Min(const Vector2& lhs, const Vector2& rhs);

        /**
         * @brief Returns the component-wise maximum of two vectors.
         * @param lhs First vector.
         * @param rhs Second vector.
         * @return A vector with the largest value in each component.
         */
        static Vector2 Max(const Vector2& lhs, const Vector2& rhs);

        /**
         * @brief Returns the component-wise absolute value of a vector.
         * @param vec Vector to apply to.
         * @return A vector with all non-negative components.
         */
        static Vector2 Abs(const Vector2& vec);

        /**
         * @brief Clamps each component of a vector between min and max.
         * @param val Vector to clamp.
         * @param min Minimum values per component.
         * @param max Maximum values per component.
         * @return The clamped vector.
         */
        static Vector2 Clamp(const Vector2& val, const Vector2& min, const Vector2& max);

        /**
         * @brief Reflects a vector off a surface with the given normal.
         * @param vec Incident vector.
         * @param normal Surface normal, assumed to be unit length.
         * @return The reflected vector.
         */
        static Vector2 Reflect(const Vector2& vec, const Vector2& normal);

        /**
         * @brief Projects a vector onto another vector.
         * @param vec Vector to project.
         * @param onto Vector to project onto, assumed to be unit length.
         * @return The projected vector.
         */
        static Vector2 Project(const Vector2& vec, const Vector2& onto);

    public:
        float x; /**< X component. */
        float y; /**< Y component. */

    public:
        /**
         * @brief Constructs a zero vector.
         */
        Vector2();

        /**
         * @brief Constructs a vector with all components set to the given scalar.
         * @param scalar Value for all components.
         */
        explicit Vector2(float scalar);

        /**
         * @brief Constructs a Vec2 from a Vec3, discarding z.
         * @param xyz The vector to convert down.
         */
        explicit Vector2(const Vector3& xyz);

        /**
         * @brief Constructs a Vec2 from a Vec4, discarding z and w.
         * @param xyzw The vector to convert down.
         */
        explicit Vector2(const Vector4& xyzw);

        /**
         * @brief Constructs a vector from two scalar values.
         * @param x X component.
         * @param y Y component.
         */
        Vector2(float x, float y);

        /**
         * @brief Constructs a Vec2 from a GLM vec2.
         * @param rhs GLM vector to copy.
         */
        Vector2(const vec2& rhs);

        /**
         * @brief Copy constructor.
         * @param rhs Vector to copy.
         */
        Vector2(const Vector2& rhs);

    public:
        /**
         * @brief Computes the dot product with another vector.
         * @param rhs Right-hand vector.
         * @return The scalar dot product.
         */
        [[nodiscard]] float Dot(const Vector2& rhs) const;

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
        [[nodiscard]] Vector2 Normalized() const;

        /**
         * @brief Checks if this vector is approximately equal to another.
         * @param rhs Vector to compare against.
         * @param e Maximum per-component difference allowed.
         * @return True if all components are within e of each other.
         */
        [[nodiscard]] bool IsApproximatelyEqual(const Vector2& rhs, float e = 1e-4f) const;

        /**
         * @brief Computes the angle between this vector and another.
         * @param rhs Other vector.
         * @return The angle in radians.
         */
        [[nodiscard]] float AngleBetween(const Vector2& rhs) const;

        /**
         * @brief Computes the distance to another vector.
         * @param rhs Other vector.
         * @return The scalar distance.
         */
        [[nodiscard]] float Distance(const Vector2& rhs) const;

        /**
         * @brief Returns the component-wise minimum of this vector and another.
         * @param rhs Other vector.
         * @return A vector with the smallest value in each component.
         */
        [[nodiscard]] Vector2 Min(const Vector2& rhs) const;

        /**
         * @brief Returns the component-wise maximum of this vector and another.
         * @param rhs Other vector.
         * @return A vector with the largest value in each component.
         */
        [[nodiscard]] Vector2 Max(const Vector2& rhs) const;

        /**
         * @brief Returns the component-wise absolute value of this vector.
         * @return A vector with all non-negative components.
         */
        [[nodiscard]] Vector2 Abs() const;

        /**
         * @brief Clamps each component between min and max.
         * @param min Minimum values per component.
         * @param max Maximum values per component.
         * @return The clamped vector.
         */
        [[nodiscard]] Vector2 Clamp(const Vector2& min, const Vector2& max) const;

        /**
         * @brief Reflects this vector off a surface with the given normal.
         * @param normal Surface normal, assumed to be unit length.
         * @return The reflected vector.
         */
        [[nodiscard]] Vector2 Reflect(const Vector2& normal) const;

        /**
         * @brief Projects this vector onto another vector.
         * @param onto Vector to project onto, assumed to be unit length.
         * @return The projected vector.
         */
        [[nodiscard]] Vector2 Project(const Vector2& onto) const;

    public:
        /**
         * @brief Writes the vector to an output stream as (x, y).
         */
        friend ostream& operator<<(ostream& stream, const Vector2& vec);

        /**
         * @brief Converts this vector to a GLM vec2.
         */
        operator vec2() const;

        /**
         * @brief Converts this vector to a Vec3, setting z to 0.
         */
        operator Vector3() const;

        /**
         * @brief Converts this vector to a Vec4, setting z and w to 0.
         */
        operator Vector4() const;

        /**
         * @brief Copy assignment operator.
         * @param rhs Vector to copy.
         * @return Reference to this vector.
         */
        Vector2& operator=(const Vector2& rhs);

        /**
         * @brief Negates all components.
         * @return A vector with all components negated.
         */
        Vector2 operator-() const;

        /**
         * @brief Checks equality between two vectors.
         * @param rhs Vector to compare against.
         * @return True if all components are approximately equal.
         */
        bool operator==(const Vector2& rhs) const;

        /**
         * @brief Checks inequality between two vectors.
         * @param rhs Vector to compare against.
         * @return True if any component differs.
         */
        bool operator!=(const Vector2& rhs) const;

        /**
         * @brief Less-than comparison for use as a map key. No geometric meaning.
         * @param rhs Vector to compare against.
         * @return True if this vector is lexicographically less than rhs.
         */
        bool operator<(const Vector2& rhs) const;

        /**
         * @brief Adds two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The sum vector.
         */
        Vector2 operator+(const Vector2& rhs) const;

        /**
         * @brief Adds another vector to this one in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector2& operator+=(const Vector2& rhs);

        /**
         * @brief Subtracts two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The difference vector.
         */
        Vector2 operator-(const Vector2& rhs) const;

        /**
         * @brief Subtracts another vector from this one in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector2& operator-=(const Vector2& rhs);

        /**
         * @brief Multiplies two vectors component-wise.
         * @param rhs Right-hand vector.
         * @return The product vector.
         */
        Vector2 operator*(const Vector2& rhs) const;

        /**
         * @brief Multiplies this vector by another component-wise in place.
         * @param rhs Right-hand vector.
         * @return Reference to this vector.
         */
        Vector2& operator*=(const Vector2& rhs);

        /**
         * @brief Multiplies all components by a scalar.
         * @param rhs Scalar value.
         * @return The scaled vector.
         */
        Vector2 operator*(float rhs) const;

        /**
         * @brief Multiplies all components by a scalar in place.
         * @param rhs Scalar value.
         * @return Reference to this vector.
         */
        Vector2& operator*=(float rhs);

        /**
         * @brief Divides all components by a scalar.
         * @param rhs Scalar value.
         * @return The scaled vector.
         */
        Vector2 operator/(float rhs) const;

        /**
         * @brief Divides all components by a scalar in place.
         * @param rhs Scalar value.
         * @return Reference to this vector.
         */
        Vector2& operator/=(float rhs);

        /**
         * @brief Returns a reference to the component at the given index.
         * @param index Component index: 0=x, 1=y.
         * @return Reference to the component.
         */
        float& operator[](int index);

        /**
         * @brief Returns a const reference to the component at the given index.
         * @param index Component index: 0=x, 1=y.
         * @return Const reference to the component.
         */
        const float& operator[](int index) const;
    };
}

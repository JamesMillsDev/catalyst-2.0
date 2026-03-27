/*****************************************************************************
 * CatalystMath
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <initializer_list>
#include <numbers>

using std::initializer_list;

namespace Catalyst::Math
{
	struct Vector2;

	/**
	 * @brief A collection of common math functions, mirroring Unity's Mathf API.
	 *
	 * @details All methods are static. The struct is not intended to be instantiated.
	 */
	struct CatalystMath
	{
	public:
		// -----------------------------------------------------------------------
		// Constants
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns the value of pi.
		 * @return π (3.14159...)
		 */
		static float Pi();

		/**
		 * @brief Returns positive infinity.
		 * @return A float representing positive infinity.
		 */
		static float Infinity();

		/**
		 * @brief Returns negative infinity.
		 * @return A float representing negative infinity.
		 */
		static float NegativeInfinity();

		/**
		 * @brief Returns the smallest positive float value greater than zero.
		 * @return Machine epsilon for float precision.
		 */
		static float Epsilon();

		/**
		 * @brief Converts radians to degrees.
		 * @param radians Angle in radians.
		 * @return The angle in degrees.
		 */
		static float Degrees(float radians);

		/**
		 * @brief Converts degrees to radians.
		 * @param degrees Angle in degrees.
		 * @return The angle in radians.
		 */
		static float Radians(float degrees);

	public:
		// -----------------------------------------------------------------------
		// Trigonometry
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns the sine of an angle in radians.
		 * @param f Angle in radians.
		 * @return The sine of f.
		 */
		static float Sin(float f);

		/**
		 * @brief Returns the cosine of an angle in radians.
		 * @param f Angle in radians.
		 * @return The cosine of f.
		 */
		static float Cos(float f);

		/**
		 * @brief Returns the tangent of an angle in radians.
		 * @param f Angle in radians.
		 * @return The tangent of f.
		 */
		static float Tan(float f);

		/**
		 * @brief Returns the arc-sine of f, in radians.
		 * @param f Value in [-1, 1].
		 * @return Angle in radians whose sine is f.
		 */
		static float Asin(float f);

		/**
		 * @brief Returns the arc-cosine of f, in radians.
		 * @param f Value in [-1, 1].
		 * @return Angle in radians whose cosine is f.
		 */
		static float Acos(float f);

		/**
		 * @brief Returns the arc-tangent of f, in radians.
		 * @param f The tangent value.
		 * @return Angle in radians whose tangent is f.
		 */
		static float Atan(float f);

		/**
		 * @brief Returns the angle in radians whose tangent is y/x.
		 * @param y The y coordinate.
		 * @param x The x coordinate.
		 * @return The angle in radians.
		 */
		static float Atan2(float y, float x);

	public:
		// -----------------------------------------------------------------------
		// Powers, roots & logarithms
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns the square root of f.
		 * @param f Non-negative input value.
		 * @return The square root of f.
		 */
		static float Sqrt(float f);

		/**
		 * @brief Returns f raised to power p.
		 * @param f The base.
		 * @param p The exponent.
		 * @return f raised to p.
		 */
		static float Pow(float f, float p);

		/**
		 * @brief Returns e raised to the specified power.
		 * @param power The exponent.
		 * @return e^power.
		 */
		static float Exp(float power);

		/**
		 * @brief Returns the natural (base e) logarithm of f.
		 * @param f Positive input value.
		 * @return The natural logarithm of f.
		 */
		static float Log(float f);

		/**
		 * @brief Returns the logarithm of f in the specified base.
		 * @param f Positive input value.
		 * @param p The logarithm base.
		 * @return log_p(f).
		 */
		static float Log(float f, float p);

		/**
		 * @brief Returns the base-10 logarithm of f.
		 * @param f Positive input value.
		 * @return The base-10 logarithm of f.
		 */
		static float Log10(float f);

	public:
		// -----------------------------------------------------------------------
		// Rounding
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns the smallest integer greater than or equal to f.
		 * @param f The input value.
		 * @return Ceiling of f as a float.
		 */
		static float Ceil(float f);

		/**
		 * @brief Returns the largest integer less than or equal to f.
		 * @param f The input value.
		 * @return Floor of f as a float.
		 */
		static float Floor(float f);

		/**
		 * @brief Returns f rounded to the nearest integer.
		 * @param f The input value.
		 * @return Rounded value as a float.
		 */
		static float Round(float f);

		/**
		 * @brief Returns the smallest integer greater than or equal to f.
		 * @param f The input value.
		 * @return Ceiling of f as an int.
		 */
		static int CeilToInt(float f);

		/**
		 * @brief Returns the largest integer less than or equal to f.
		 * @param f The input value.
		 * @return Floor of f as an int.
		 */
		static int FloorToInt(float f);

		/**
		 * @brief Returns f rounded to the nearest integer.
		 * @param f The input value.
		 * @return Rounded value as an int.
		 */
		static int RoundToInt(float f);

	public:
		// -----------------------------------------------------------------------
		// Absolute value & sign
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns the absolute value of f.
		 * @param f The input float.
		 * @return |f|.
		 */
		static float Abs(float f);

		/**
		 * @brief Returns the absolute value of value.
		 * @param value The input int.
		 * @return |value|.
		 */
		static int Abs(int value);

		/**
		 * @brief Returns 1 if f is positive or zero, -1 if negative.
		 * @param f The input value.
		 * @return The sign of f.
		 */
		static float Sign(float f);

	public:
		// -----------------------------------------------------------------------
		// Min / Max
		// -----------------------------------------------------------------------

		/** @brief Returns the smaller of two floats. */
		static float Min(float a, float b);

		/** @brief Returns the smaller of two ints. */
		static int Min(int a, int b);

		/**
		 * @brief Returns the smallest value in a list of floats.
		 * @param values Initializer list of floats.
		 * @return The minimum value, or 0 if the list is empty.
		 */
		static float Min(std::initializer_list<float> values);

		/**
		 * @brief Returns the smallest value in a list of ints.
		 * @param values Initializer list of ints.
		 * @return The minimum value, or 0 if the list is empty.
		 */
		static int Min(std::initializer_list<int> values);

		/** @brief Returns the larger of two floats. */
		static float Max(float a, float b);

		/** @brief Returns the larger of two ints. */
		static int Max(int a, int b);

		/**
		 * @brief Returns the largest value in a list of floats.
		 * @param values Initializer list of floats.
		 * @return The maximum value, or 0 if the list is empty.
		 */
		static float Max(std::initializer_list<float> values);

		/**
		 * @brief Returns the largest value in a list of ints.
		 * @param values Initializer list of ints.
		 * @return The maximum value, or 0 if the list is empty.
		 */
		static int Max(std::initializer_list<int> values);

	public:
		// -----------------------------------------------------------------------
		// Clamping
		// -----------------------------------------------------------------------

		/**
		 * @brief Clamps a float between min and max.
		 * @param value The value to clamp.
		 * @param min The minimum bound.
		 * @param max The maximum bound.
		 * @return The clamped value.
		 */
		static float Clamp(float value, float min, float max);

		/**
		 * @brief Clamps an int between min and max.
		 * @param value The value to clamp.
		 * @param min The minimum bound.
		 * @param max The maximum bound.
		 * @return The clamped value.
		 */
		static int Clamp(int value, int min, int max);

		/**
		 * @brief Clamps a float between 0 and 1.
		 * @param value The value to clamp.
		 * @return The clamped value in [0, 1].
		 */
		static float Clamp01(float value);

	public:
		// -----------------------------------------------------------------------
		// Interpolation
		// -----------------------------------------------------------------------

		/**
		 * @brief Linearly interpolates between a and b by t, clamped to [0, 1].
		 * @param a Start value.
		 * @param b End value.
		 * @param t Interpolation factor.
		 * @return The interpolated value.
		 */
		static float Lerp(float a, float b, float t);

		/**
		 * @brief Linearly interpolates between a and b by t without clamping.
		 * @param a Start value.
		 * @param b End value.
		 * @param t Interpolation factor (unclamped).
		 * @return The interpolated value.
		 */
		static float LerpUnclamped(float a, float b, float t);

		/**
		 * @brief Interpolates between two angles in degrees, wrapping correctly around 360.
		 * @param a Start angle in degrees.
		 * @param b End angle in degrees.
		 * @param t Interpolation factor, clamped to [0, 1].
		 * @return The interpolated angle.
		 */
		static float LerpAngle(float a, float b, float t);

		/**
		 * @brief Calculates the inverse lerp parameter t such that Lerp(a, b, t) == value.
		 * @param a Start value.
		 * @param b End value.
		 * @param value The value to locate within [a, b].
		 * @return The interpolation factor t, clamped to [0, 1].
		 */
		static float InverseLerp(float a, float b, float value);

		/**
		 * @brief Interpolates between from and to with smoothing at the limits.
		 * @param from The start value.
		 * @param to The end value.
		 * @param t Interpolation factor, clamped to [0, 1].
		 * @return The smoothly interpolated value.
		 */
		static float SmoothStep(float from, float to, float t);

	public:
		// -----------------------------------------------------------------------
		// Movement & damping
		// -----------------------------------------------------------------------

		/**
		 * @brief Moves current towards target by at most maxDelta, without overshooting.
		 * @param current The current value.
		 * @param target The target value.
		 * @param maxDelta Maximum step size.
		 * @return The new value.
		 */
		static float MoveTowards(float current, float target, float maxDelta);

		/**
		 * @brief Moves an angle in degrees towards a target angle, wrapping correctly.
		 * @param current The current angle in degrees.
		 * @param target The target angle in degrees.
		 * @param maxDelta Maximum angular step in degrees.
		 * @return The new angle.
		 */
		static float MoveTowardsAngle(float current, float target, float maxDelta);

		/**
		 * @brief Gradually changes a value towards a target over time using a spring-damper model.
		 * @param current The current value.
		 * @param target The target value.
		 * @param currentVelocity Current velocity, modified in place each call.
		 * @param smoothTime Approximate time to reach the target.
		 * @param maxSpeed Maximum speed cap (default: Math::Infinity).
		 * @param deltaTime Time elapsed since the last call.
		 * @return The new smoothed value.
		 */
		static float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

		/**
		 * @brief Gradually changes an angle in degrees towards a target angle using a spring-damper model.
		 * @param current The current angle in degrees.
		 * @param target The target angle in degrees.
		 * @param currentVelocity Current angular velocity, modified in place each call.
		 * @param smoothTime Approximate time to reach the target.
		 * @param maxSpeed Maximum angular speed cap (default: Math::Infinity).
		 * @param deltaTime Time elapsed since the last call.
		 * @return The new smoothed angle.
		 */
		static float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

	public:
		// -----------------------------------------------------------------------
		// Angles & wrapping
		// -----------------------------------------------------------------------

		/**
		 * @brief Loops t so it is never larger than length and never smaller than 0.
		 * @param t The value to wrap.
		 * @param length The wrap length.
		 * @return The wrapped value in [0, length).
		 */
		static float Repeat(float t, float length);

		/**
		 * @brief Ping-pongs t between 0 and length.
		 * @param t The input value.
		 * @param length The ping-pong range.
		 * @return The bounced value in [0, length].
		 */
		static float PingPong(float t, float length);

		/**
		 * @brief Returns the shortest signed difference between two angles in degrees.
		 * @param current The current angle in degrees.
		 * @param target The target angle in degrees.
		 * @return The delta in (-180, 180].
		 */
		static float DeltaAngle(float current, float target);

	public:
		// -----------------------------------------------------------------------
		// Approximation
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns true if a and b are approximately equal.
		 *
		 * @details Uses a relative epsilon scaled by the magnitude of the inputs,
		 * matching Unity's Mathf.Approximately behaviour.
		 *
		 * @param a First value.
		 * @param b Second value.
		 * @param e
		 * @return True if the values are within a small epsilon of each other.
		 */
		static bool Approximately(float a, float b, float e = 1e-4f);

		/**
		 * @brief Applies a gamma curve to a value within an absolute maximum range.
		 * @param value The input value.
		 * @param absMax The absolute maximum (defines the curve range).
		 * @param gamma The gamma exponent.
		 * @return The gamma-adjusted value.
		 */
		static float Gamma(float value, float absMax, float gamma);

	public:
		// -----------------------------------------------------------------------
		// Bit / integer utilities
		// -----------------------------------------------------------------------

		/**
		 * @brief Returns true if value is a power of two.
		 * @param value The integer to test.
		 * @return True if value is a power of two.
		 */
		static bool IsPowerOfTwo(int value);

		/**
		 * @brief Returns the next power of two greater than or equal to value.
		 * @param value The input integer.
		 * @return The next power of two.
		 */
		static int NextPowerOfTwo(int value);

		/**
		 * @brief Returns the power of two closest to value.
		 * @param value The input integer.
		 * @return The closest power of two.
		 */
		static int ClosestPowerOfTwo(int value);

	public:
		// -----------------------------------------------------------------------
		// Geometry
		// -----------------------------------------------------------------------

		/**
		 * @brief Finds the intersection point of two infinite lines.
		 * @param p1 First point on line 1.
		 * @param p2 Second point on line 1.
		 * @param p3 First point on line 2.
		 * @param p4 Second point on line 2.
		 * @param result Output intersection point.
		 * @return True if the lines intersect (not parallel).
		 */
		static bool LineIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result);

		/**
		 * @brief Finds the intersection point of two finite line segments.
		 * @param p1 Start of segment 1.
		 * @param p2 End of segment 1.
		 * @param p3 Start of segment 2.
		 * @param p4 End of segment 2.
		 * @param result Output intersection point.
		 * @return True if the segments intersect.
		 */
		static bool LineSegmentIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result);

	private:
		CatalystMath() = delete;
		~CatalystMath() = delete;
	};
}

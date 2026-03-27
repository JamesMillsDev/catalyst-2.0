/*****************************************************************************
 * CatalystMath
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "CatalystMath.h"

#include "Vector2.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace Catalyst::Math
{
	// -----------------------------------------------------------------------
	// Trigonometry
	// -----------------------------------------------------------------------

	float CatalystMath::Pi()
	{
		return std::numbers::pi_v<float>;
	}

	float CatalystMath::Infinity()
	{
		return 3.402823466e+38F;
	}

	float CatalystMath::NegativeInfinity()
	{
		return -3.402823466e+38F;
	}

	float CatalystMath::Epsilon()
	{
		return 1.175494351e-38F;
	}

	float CatalystMath::Degrees(const float radians)
	{
		return radians * Pi() * 2.f / 360.f;
	}

	float CatalystMath::Radians(const float degrees)
	{
		return degrees * 1.f / Pi();
	}

	float CatalystMath::Sin(const float f)
	{
		return sinf(f);
	}

	float CatalystMath::Cos(const float f)
	{
		return cosf(f);
	}

	float CatalystMath::Tan(const float f)
	{
		return tanf(f);
	}

	float CatalystMath::Asin(const float f)
	{
		return asinf(f);
	}

	float CatalystMath::Acos(const float f)
	{
		return acosf(f);
	}

	float CatalystMath::Atan(const float f)
	{
		return atanf(f);
	}

	float CatalystMath::Atan2(const float y, const float x)
	{
		return atan2f(y, x);
	}

	// -----------------------------------------------------------------------
	// Powers, roots & logarithms
	// -----------------------------------------------------------------------

	float CatalystMath::Sqrt(const float f)
	{
		return sqrtf(f);
	}

	float CatalystMath::Pow(const float f, const float p)
	{
		return powf(f, p);
	}

	float CatalystMath::Exp(const float power)
	{
		return expf(power);
	}

	float CatalystMath::Log(const float f)
	{
		return logf(f);
	}

	float CatalystMath::Log(const float f, const float p)
	{
		return logf(f) / logf(p);
	}

	float CatalystMath::Log10(const float f)
	{
		return log10f(f);
	}

	// -----------------------------------------------------------------------
	// Rounding
	// -----------------------------------------------------------------------

	float CatalystMath::Ceil(const float f)
	{
		return ceilf(f);
	}

	float CatalystMath::Floor(const float f)
	{
		return floorf(f);
	}

	float CatalystMath::Round(const float f)
	{
		return roundf(f);
	}

	int CatalystMath::CeilToInt(const float f)
	{
		return static_cast<int>(ceilf(f));
	}

	int CatalystMath::FloorToInt(const float f)
	{
		return static_cast<int>(floorf(f));
	}

	int CatalystMath::RoundToInt(const float f)
	{
		return static_cast<int>(roundf(f));
	}

	// -----------------------------------------------------------------------
	// Absolute value & sign
	// -----------------------------------------------------------------------

	float CatalystMath::Abs(const float f)
	{
		return fabsf(f);
	}

	int CatalystMath::Abs(const int value)
	{
		return abs(value);
	}

	float CatalystMath::Sign(const float f)
	{
		return f >= 0.f ? 1.f : -1.f;
	}

	// -----------------------------------------------------------------------
	// Min / Max
	// -----------------------------------------------------------------------

	float CatalystMath::Min(const float a, const float b)
	{
		return a < b ? a : b;
	}

	int CatalystMath::Min(const int a, const int b)
	{
		return a < b ? a : b;
	}

	float CatalystMath::Min(const initializer_list<float> values)
	{
		if (values.size() == 0)
		{
			return 0.f;
		}

		float m = *values.begin();
		for (const float v : values)
		{
			m = std::min(v, m);
		}
		return m;
	}

	int CatalystMath::Min(const initializer_list<int> values)
	{
		if (values.size() == 0)
		{
			return 0;
		}

		int m = *values.begin();
		for (const int v : values)
		{
			m = std::min(v, m);
		}
		return m;
	}

	float CatalystMath::Max(const float a, const float b)
	{
		return a > b ? a : b;
	}

	int CatalystMath::Max(const int a, const int b)
	{
		return a > b ? a : b;
	}

	float CatalystMath::Max(const initializer_list<float> values)
	{
		if (values.size() == 0)
		{
			return 0.f;
		}

		float m = *values.begin();
		for (const float v : values)
		{
			m = std::max(v, m);
		}
		return m;
	}

	int CatalystMath::Max(const std::initializer_list<int> values)
	{
		if (values.size() == 0)
		{
			return 0;
		}

		int m = *values.begin();
		for (const int v : values)
		{
			m = std::max(v, m);
		}
		return m;
	}

	// -----------------------------------------------------------------------
	// Clamping
	// -----------------------------------------------------------------------

	float CatalystMath::Clamp(float value, const float min, const float max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}

	int CatalystMath::Clamp(int value, const int min, const int max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
		return value;
	}

	float CatalystMath::Clamp01(const float value)
	{
		if (value < 0.f)
		{
			return 0.f;
		}
		if (value > 1.f)
		{
			return 1.f;
		}
		return value;
	}

	// -----------------------------------------------------------------------
	// Interpolation
	// -----------------------------------------------------------------------

	float CatalystMath::Lerp(const float a, const float b, const float t)
	{
		return a + (b - a) * Clamp01(t);
	}

	float CatalystMath::LerpUnclamped(const float a, const float b, const float t)
	{
		return a + (b - a) * t;
	}

	float CatalystMath::LerpAngle(const float a, const float b, const float t)
	{
		float delta = Repeat(b - a, 360.f);
		if (delta > 180.f)
		{
			delta -= 360.f;
		}
		return a + delta * Clamp01(t);
	}

	float CatalystMath::InverseLerp(const float a, const float b, const float value)
	{
		if (!Approximately(a, b))
		{
			return Clamp01((value - a) / (b - a));
		}
		return 0.f;
	}

	float CatalystMath::SmoothStep(const float from, const float to, float t)
	{
		t = Clamp01(t);
		t = -2.f * t * t * t + 3.f * t * t;
		return to * t + from * (1.f - t);
	}

	// -----------------------------------------------------------------------
	// Movement & damping
	// -----------------------------------------------------------------------

	float CatalystMath::MoveTowards(const float current, const float target, const float maxDelta)
	{
		if (Abs(target - current) <= maxDelta)
		{
			return target;
		}
		return current + Sign(target - current) * maxDelta;
	}

	float CatalystMath::MoveTowardsAngle(const float current, float target, const float maxDelta)
	{
		const float deltaAngle = DeltaAngle(current, target);
		if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
		{
			return target;
		}
		target = current + deltaAngle;
		return MoveTowards(current, target, maxDelta);
	}

	float CatalystMath::SmoothDamp(const float current, float target, float& currentVelocity, float smoothTime, const float maxSpeed, const float deltaTime)
	{
		// Based on Game Programming Gems 4, Chapter 1.10
		smoothTime = Max(0.0001f, smoothTime);

		const float omega = 2.f / smoothTime;
		const float x = omega * deltaTime;
		const float exp = 1.f / (1.f + x + 0.48f * x * x + 0.235f * x * x * x);

		float change = current - target;
		const float originalTo = target;

		const float maxChange = maxSpeed * smoothTime;
		change = Clamp(change, -maxChange, maxChange);
		target = current - change;

		const float temp = (currentVelocity + omega * change) * deltaTime;
		currentVelocity = (currentVelocity - omega * temp) * exp;

		float output = target + (change + temp) * exp;

		// Prevent overshooting
		if (originalTo - current > 0.f == output > originalTo)
		{
			output = originalTo;
			currentVelocity = (output - originalTo) / deltaTime;
		}

		return output;
	}

	float CatalystMath::SmoothDampAngle(const float current, float target, float& currentVelocity, const float smoothTime, const float maxSpeed, const float deltaTime)
	{
		target = current + DeltaAngle(current, target);
		return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
	}

	// -----------------------------------------------------------------------
	// Angles & wrapping
	// -----------------------------------------------------------------------

	float CatalystMath::Repeat(const float t, const float length)
	{
		return Clamp(t - Floor(t / length) * length, 0.f, length);
	}

	float CatalystMath::PingPong(const float t, const float length)
	{
		const float r = Repeat(t, length * 2.f);
		return length - Abs(r - length);
	}

	float CatalystMath::DeltaAngle(const float current, const float target)
	{
		float delta = Repeat(target - current, 360.f);
		if (delta > 180.f)
		{
			delta -= 360.f;
		}
		return delta;
	}

	// -----------------------------------------------------------------------
	// Approximation
	// -----------------------------------------------------------------------

	bool CatalystMath::Approximately(const float a, const float b, const float e)
	{
		return Abs(b - a) < Max(0.000001f * Max(Abs(a), Abs(b)), Epsilon() * e * 8.f);
	}

	float CatalystMath::Gamma(const float value, const float absMax, const float gamma)
	{
		const bool negative = value < 0.f;
		const float absVal = Abs(value);

		if (absVal > absMax)
		{
			return negative ? -absVal : absVal;
		}

		const float result = Pow(absVal / absMax, gamma) * absMax;
		return negative ? -result : result;
	}

	// -----------------------------------------------------------------------
	// Bit / integer utilities
	// -----------------------------------------------------------------------

	bool CatalystMath::IsPowerOfTwo(const int value)
	{
		return (value & (value - 1)) == 0;
	}

	int CatalystMath::NextPowerOfTwo(int value)
	{
		value -= 1;
		value |= value >> 16;
		value |= value >> 8;
		value |= value >> 4;
		value |= value >> 2;
		value |= value >> 1;
		return value + 1;
	}

	int CatalystMath::ClosestPowerOfTwo(const int value)
	{
		const int nextPower = NextPowerOfTwo(value);
		const int prevPower = nextPower >> 1;
		return (value - prevPower < nextPower - value) ? prevPower : nextPower;
	}

	// -----------------------------------------------------------------------
	// Geometry
	// -----------------------------------------------------------------------

	bool CatalystMath::LineIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result)
	{
		const float bx = p2.x - p1.x;
		const float by = p2.y - p1.y;
		const float dx = p4.x - p3.x;
		const float dy = p4.y - p3.y;

		const float bDotDPerp = bx * dy - by * dx;
		if (Approximately(bDotDPerp, 0.f))
		{
			return false;
		}

		const float cx = p3.x - p1.x;
		const float cy = p3.y - p1.y;
		const float t = (cx * dy - cy * dx) / bDotDPerp;

		result.x = p1.x + t * bx;
		result.y = p1.y + t * by;
		return true;
	}

	bool CatalystMath::LineSegmentIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result)
	{
		const float bx = p2.x - p1.x;
		const float by = p2.y - p1.y;
		const float dx = p4.x - p3.x;
		const float dy = p4.y - p3.y;

		const float bDotDPerp = bx * dy - by * dx;
		if (Approximately(bDotDPerp, 0.f))
		{
			return false;
		}

		const float cx = p3.x - p1.x;
		const float cy = p3.y - p1.y;
		const float t = (cx * dy - cy * dx) / bDotDPerp;

		if (t < 0.f || t > 1.f)
		{
			return false;
		}

		const float u = (cx * by - cy * bx) / bDotDPerp;
		if (u < 0.f || u > 1.f)
		{
			return false;
		}

		result.x = p1.x + t * bx;
		result.y = p1.y + t * by;
		return true;
	}
}

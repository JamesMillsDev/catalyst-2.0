/*****************************************************************************
 * Color
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "Color.h"

#include <algorithm>
#include <cmath>
#include <format>

#include "CatalystMath.h"

namespace Catalyst::Math
{
	const Color Color::red        = 0xE62937FF;
	const Color Color::maroon     = 0xBE2137FF;
	const Color Color::orange     = 0xFFA100FF;
	const Color Color::gold       = 0xFFCB00FF;
	const Color Color::yellow     = 0xFDF900FF;
	const Color Color::green      = 0x00E430FF;
	const Color Color::lime       = 0x009E2FFF;
	const Color Color::darkGreen  = 0x00752CFF;
	const Color Color::skyBlue    = 0x66BFFFFF;
	const Color Color::blue       = 0x0079F1FF;
	const Color Color::darkBlue   = 0x0052ACFF;
	const Color Color::purple     = 0xC87AFFFF;
	const Color Color::violet     = 0x873CBEFF;
	const Color Color::darkPurple = 0x701F7EFF;
	const Color Color::pink       = 0xFF6DC2FF;
	const Color Color::magenta    = 0xFF00FFFF;
	const Color Color::beige      = 0xD3B083FF;
	const Color Color::brown      = 0x7F6A4FFF;
	const Color Color::darkBrown  = 0x4C3F2FFF;
	const Color Color::white      = 0xFFFFFFFF;
	const Color Color::lightGray  = 0xC8C8C8FF;
	const Color Color::gray       = 0x828282FF;
	const Color Color::darkGray   = 0x505050FF;
	const Color Color::black      = 0x000000FF;
	const Color Color::blank      = 0x00000000;

	Color Color::FromHex(const char* hex)
	{
		return { };
	}

	Color Color::Lerp(const Color& lhs, const Color& rhs, float t)
	{
		return { };
	}

	Color::Color()
		: rgba{ 0x000000ff } { }

	Color::Color(const uint32_t rgba)
		: rgba{ rgba } { }

	Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
		: rgba{
			static_cast<uint32_t>(r) << 24 | static_cast<uint32_t>(g) << 16 |
			static_cast<uint32_t>(b) << 8 | static_cast<uint32_t>(a) << 0
		} { }

	Color::Color(uint16_t hue, float sat, float val, const uint8_t a)
		: rgba{ 0 }
	{
		// Clamp the values to the correct ranges
		hue %= 360;
		sat = std::clamp(sat, 0.0f, 1.0f);
		val = std::clamp(val, 0.0f, 1.0f);

		// Get the states
		const float c = val * sat;
		const float h = static_cast<float>(hue) / 60.f;
		const float x = c * (1 - fabsf(fmodf(h, 2) - 1));
		const float m = val - c;

		float rPrime = 0.f;
		float gPrime = 0.f;
		float bPrime = 0.f;

		// Calculate the prime versions of rgb based on the angle of the hue
		if (0 <= h && h <= 1.f)
		{
			rPrime = c;
			gPrime = x;
		}
		else if (1.f <= h && h <= 2.f)
		{
			rPrime = x;
			gPrime = c;
		}
		else if (2.f <= h && h <= 3.f)
		{
			gPrime = c;
			bPrime = x;
		}
		else if (3.f <= h && h <= 4.f)
		{
			gPrime = x;
			bPrime = c;
		}
		else if (4.f <= h && h <= 5.f)
		{
			rPrime = x;
			bPrime = c;
		}
		else if (5.f <= h && h <= 6.f)
		{
			rPrime = c;
			bPrime = x;
		}

		// Assign the relevant channels
		SetRed(static_cast<uint8_t>((rPrime + m) * 255.f + .5f)); // NOLINT(*-incorrect-roundings)
		SetGreen(static_cast<uint8_t>((gPrime + m) * 255.f + .5f)); // NOLINT(*-incorrect-roundings)
		SetBlue(static_cast<uint8_t>((bPrime + m) * 255.f + .5f)); // NOLINT(*-incorrect-roundings)
		SetAlpha(a);
	}

	Color::Color(const vec4& rhs)
		: rgba{
			static_cast<uint32_t>(rhs.r * 255) << 24 | static_cast<uint32_t>(rhs.g * 255) << 16 |
			static_cast<uint32_t>(rhs.b) << 8 | static_cast<uint32_t>(rhs.a) << 0
		} { }

	Color::Color(const Color& rhs) = default;

	uint8_t Color::GetRed() const
	{
		return static_cast<uint8_t>(rgba >> 24);
	}

	uint8_t Color::GetGreen() const
	{
		return static_cast<uint8_t>(rgba >> 16);
	}

	uint8_t Color::GetBlue() const
	{
		return static_cast<uint8_t>(rgba >> 8);
	}

	uint8_t Color::GetAlpha() const
	{
		return static_cast<uint8_t>(rgba >> 0);
	}

	float Color::GetRedF() const
	{
		return static_cast<float>(GetRed()) / 255.f;
	}

	float Color::GetGreenF() const
	{
		return static_cast<float>(GetGreen()) / 255.f;
	}

	float Color::GetBlueF() const
	{
		return static_cast<float>(GetBlue()) / 255.f;
	}

	float Color::GetAlphaF() const
	{
		return static_cast<float>(GetAlpha()) / 255.f;
	}

	void Color::SetRed(const uint8_t r)
	{
		rgba = (rgba & 0x00ffffff) | static_cast<uint32_t>(r) << 24;
	}

	void Color::SetGreen(const uint8_t g)
	{
		rgba = (rgba & 0xff00ffff) | static_cast<uint32_t>(g) << 16;
	}

	void Color::SetBlue(const uint8_t b)
	{
		rgba = (rgba & 0xffff00ff) | static_cast<uint32_t>(b) << 8;
	}

	void Color::SetAlpha(const uint8_t a)
	{
		rgba = (rgba & 0xffffff00) | static_cast<uint32_t>(a) << 0;
	}

	uint16_t Color::GetHue() const
	{
		uint16_t hue = 0;
		HSV(&hue, nullptr, nullptr);

		return hue;
	}

	float Color::GetSaturation() const
	{
		float sat = 0;
		HSV(nullptr, &sat, nullptr);

		return sat;
	}

	float Color::GetValue() const
	{
		float val = 0;
		HSV(nullptr, nullptr, &val);

		return val;
	}

	void Color::HSV(uint16_t* hue, float* sat, float* val) const
	{
		// Get each channel as a normalised float
		const float r = GetRedF();
		const float g = GetGreenF();
		const float b = GetBlueF();

		// Find the minimum and maximum channels
		const float cMin = std::min(r, std::min(g, b));
		const float cMax = std::max(r, std::max(g, b));
		const float c    = cMax - cMin; // Delta: the range of the channels

		// Value is simply the largest channel
		if (val != nullptr)
		{
			*val = cMax;
		}

		// Saturation is undefined when the color is black, so guard against divide by zero
		if (sat != nullptr)
		{
			*sat = CatalystMath::Approximately(cMax, 0.f) ? 0.f : c / cMax;
		}

		if (hue != nullptr)
		{
			// Achromatic case (grey): hue is undefined, default to 0
			if (CatalystMath::Approximately(c, 0.f))
			{
				*hue = 0;
			}
			else
			{
				float h = 0;

				// Determine which channel is dominant to select the correct sextant
				if (CatalystMath::Approximately(cMax, r))
				{
					h = 60.f * fmodf((g - b) / c, 6); // Sextant 0 or 5, mod 6 handles wraparound
				}
				else if (CatalystMath::Approximately(cMax, g))
				{
					h = 60.f * ((b - r) / c + 2.f); // Sextant 1 or 2
				}
				else if (CatalystMath::Approximately(cMax, b))
				{
					h = 60.f * ((r - g) / c + 4.f); // Sextant 3 or 4
				}

				// Wrap negative hue values into [0, 360)
				if (CatalystMath::Sign(h) < 0.f)
				{
					h += 360.f;
				}

				*hue = static_cast<uint16_t>(h);
			}
		}
	}

	Color Color::WithRed(const uint8_t r) const
	{
		Color redVersion = *this;
		redVersion.SetRed(r);
		return redVersion;
	}

	Color Color::WithGreen(const uint8_t g) const
	{
		Color greenVersion = *this;
		greenVersion.SetGreen(g);
		return greenVersion;
	}

	Color Color::WithBlue(const uint8_t b) const
	{
		Color blueVersion = *this;
		blueVersion.SetBlue(b);
		return blueVersion;
	}

	Color Color::WithAlpha(const uint8_t a) const
	{
		Color alphaVersion = *this;
		alphaVersion.SetAlpha(a);
		return alphaVersion;
	}

	Color Color::Inverted() const
	{
		uint8_t r = 255 - GetRed();
		uint8_t g = 255 - GetGreen();
		uint8_t b = 255 - GetBlue();

		return { r, g, b, GetAlpha() };
	}

	Color Color::Greyscale() const
	{
		const uint8_t l = static_cast<uint8_t>(Luminance() * 255.f);

		return { l, l, l, GetAlpha() };
	}

	float Color::Luminance() const
	{
		const float r = static_cast<float>(GetRed()) / 255.f;
		const float g = static_cast<float>(GetGreen()) / 255.f;
		const float b = static_cast<float>(GetBlue()) / 255.f;

		return .2126f * r + .7152f * g + .0722f * b;
	}

	void Color::ToLinear()
	{
		const float r = GetRedF();
		const float g = GetGreenF();
		const float b = GetBlueF();

		SetRed(static_cast<uint8_t>(255.f * powf(r, 2.2f)));
		SetGreen(static_cast<uint8_t>(255.f * powf(g, 2.2f)));
		SetBlue(static_cast<uint8_t>(255.f * powf(b, 2.2f)));
	}

	void Color::ToGamma()
	{
		const float r = GetRedF();
		const float g = GetGreenF();
		const float b = GetBlueF();

		SetRed(static_cast<uint8_t>(255.f * powf(r, 1.f / 2.2f)));
		SetGreen(static_cast<uint8_t>(255.f * powf(g, 1.f / 2.2f)));
		SetBlue(static_cast<uint8_t>(255.f * powf(b, 1.f / 2.2f)));
	}

	Color::operator ::vec4() const
	{
		return
		{
			static_cast<float>(GetRed()) / 255.f,
			static_cast<float>(GetGreen()) / 255.f,
			static_cast<float>(GetBlue()) / 255.f,
			static_cast<float>(GetAlpha()) / 255.f
		};
	}

	Color& Color::operator=(const vec4& rhs)
	{
		SetRed(static_cast<uint8_t>(rhs.r * 255.f));
		SetGreen(static_cast<uint8_t>(rhs.g * 255.f));
		SetBlue(static_cast<uint8_t>(rhs.b * 255.f));
		SetAlpha(static_cast<uint8_t>(rhs.a * 255.f));

		return *this;
	}

	Color& Color::operator=(const Color& rhs) = default;

	bool Color::operator==(const Color& rhs) const
	{
		return rgba == rhs.rgba;
	}

	bool Color::operator!=(const Color& rhs) const
	{
		return rgba != rhs.rgba;
	}

	ostream& operator<<(ostream& stream, const Color& rhs)
	{
		stream << std::format("(r:{:<02}, g:{:<02}, b:{:<02}, a:{:<02})",
		                      rhs.GetRed(),
		                      rhs.GetGreen(),
		                      rhs.GetBlue(),
		                      rhs.GetAlpha());

		return stream;
	}
}

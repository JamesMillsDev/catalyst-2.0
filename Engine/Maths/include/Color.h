/*****************************************************************************
 * Color
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include <ostream>
#include <glm/vec4.hpp>

using glm::vec4;
using std::ostream;

namespace Catalyst::Math
{
	/** @brief A 32-bit RGBA color value. */
	class Color
	{
	public:
		static const Color red;         /** RGBA(230,  41,  55, 255) | #E62937FF */
		static const Color maroon;      /** RGBA(190,  33,  55, 255) | #BE2137FF */
		static const Color orange;      /** RGBA(255, 161,   0, 255) | #FFA100FF */
		static const Color gold;        /** RGBA(255, 203,   0, 255) | #FFCB00FF */
		static const Color yellow;      /** RGBA(253, 249,   0, 255) | #FDF900FF */
		static const Color green;       /** RGBA(  0, 228,  48, 255) | #00E430FF */
		static const Color lime;        /** RGBA(  0, 158,  47, 255) | #009E2FFF */
		static const Color darkGreen;   /** RGBA(  0, 117,  44, 255) | #00752CFF */
		static const Color skyBlue;     /** RGBA(102, 191, 255, 255) | #66BFFFFF */
		static const Color blue;        /** RGBA(  0, 121, 241, 255) | #0079F1FF */
		static const Color darkBlue;    /** RGBA(  0,  82, 172, 255) | #0052ACFF */
		static const Color purple;      /** RGBA(200, 122, 255, 255) | #C87AFFFF */
		static const Color violet;      /** RGBA(135,  60, 190, 255) | #873CBEFF */
		static const Color darkPurple;  /** RGBA(112,  31, 126, 255) | #701F7EFF */
		static const Color pink;        /** RGBA(255, 109, 194, 255) | #FF6DC2FF */
		static const Color magenta;     /** RGBA(255,   0, 255, 255) | #FF00FFFF */
		static const Color beige;       /** RGBA(211, 176, 131, 255) | #D3B083FF */
		static const Color brown;       /** RGBA(127, 106,  79, 255) | #7F6A4FFF */
		static const Color darkBrown;   /** RGBA( 76,  63,  47, 255) | #4C3F2FFF */
		static const Color white;       /** RGBA(255, 255, 255, 255) | #FFFFFFFF */
		static const Color lightGray;   /** RGBA(200, 200, 200, 255) | #C8C8C8FF */
		static const Color gray;        /** RGBA(130, 130, 130, 255) | #828282FF */
		static const Color darkGray;    /** RGBA( 80,  80,  80, 255) | #505050FF */
		static const Color black;       /** RGBA(  0,   0,   0, 255) | #000000FF */
		static const Color blank;       /** RGBA(  0,   0,   0,   0) | #00000000 */

	public:
		/**
		 * @brief Constructs a Color from a hex string.
		 * @param hex A null-terminated string in the form @c "#RRGGBBAA", @c "RRGGBBAA",
		 *            @c "#RRGGBB", or @c "RRGGBB". Case-insensitive.
		 * @return The parsed Color. Alpha defaults to 255 when omitted.
		 */
		static Color FromHex(const char* hex);

		/**
		 * @brief Linearly interpolates between two colors.
		 * @param lhs The start color (returned when @p t is 0).
		 * @param rhs The end color (returned when @p t is 1).
		 * @param t   The interpolation factor, clamped to [0, 1].
		 * @return The interpolated Color.
		 */
		static Color Lerp(const Color& lhs, const Color& rhs, float t);

	public:
		/** @brief The packed RGBA value. Byte order: R at bits 31–24, G at 23–16, B at 15–8, A at 7–0. */
		uint32_t rgba;

	public:
		/** @brief Constructs a fully transparent black color (0x00000000). */
		Color();

		/**
		 * @brief Constructs a Color from a packed 32-bit RGBA value.
		 * @param rgba Packed value with R at bits 31–24, G at 23–16, B at 15–8, A at 7–0.
		 */
		Color(uint32_t rgba);

		/**
		 * @brief Constructs a Color from individual 8-bit RGBA components.
		 * @param r Red channel   [0, 255].
		 * @param g Green channel [0, 255].
		 * @param b Blue channel  [0, 255].
		 * @param a Alpha channel [0, 255].
		 */
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		/**
		 * @brief Constructs a Color from HSV values plus an alpha channel.
		 * @param hue Hue in degrees            [0, 360).
		 * @param sat Saturation as a fraction  [0.0, 1.0].
		 * @param val Value (brightness)        [0.0, 1.0].
		 * @param a   Alpha channel             [0, 255].
		 */
		Color(uint16_t hue, float sat, float val, uint8_t a);

		/**
		 * @brief Constructs a Color from a GLM @c vec4.
		 * @param rhs A vector with components in the range [0.0, 1.0], ordered (r, g, b, a).
		 */
		explicit Color(const vec4& rhs);

		/**
		 * @brief Copy constructor.
		 * @param rhs The Color to copy.
		 */
		Color(const Color& rhs);

	public:
		/**
		 * @brief Returns the red channel.
		 * @return Red component in the range [0, 255].
		 */
		[[nodiscard]] uint8_t GetRed() const;

		/**
		 * @brief Returns the green channel.
		 * @return Green component in the range [0, 255].
		 */
		[[nodiscard]] uint8_t GetGreen() const;

		/**
		 * @brief Returns the blue channel.
		 * @return Blue component in the range [0, 255].
		 */
		[[nodiscard]] uint8_t GetBlue() const;

		/**
		 * @brief Returns the alpha channel.
		 * @return Alpha component in the range [0, 255].
		 */
		[[nodiscard]] uint8_t GetAlpha() const;

		/**
		 * @brief Returns the red channel normalised to [0.0, 1.0].
		 * @return Red component as a float in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetRedF() const;

		/**
		 * @brief Returns the green channel normalised to [0.0, 1.0].
		 * @return Green component as a float in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetGreenF() const;

		/**
		 * @brief Returns the blue channel normalised to [0.0, 1.0].
		 * @return Blue component as a float in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetBlueF() const;

		/**
		 * @brief Returns the alpha channel normalised to [0.0, 1.0].
		 * @return Alpha component as a float in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetAlphaF() const;

		/**
		 * @brief Sets the red channel.
		 * @param r Red component in the range [0, 255].
		 */
		void SetRed(uint8_t r);

		/**
		 * @brief Sets the green channel.
		 * @param g Green component in the range [0, 255].
		 */
		void SetGreen(uint8_t g);

		/**
		 * @brief Sets the blue channel.
		 * @param b Blue component in the range [0, 255].
		 */
		void SetBlue(uint8_t b);

		/**
		 * @brief Sets the alpha channel.
		 * @param a Alpha component in the range [0, 255].
		 */
		void SetAlpha(uint8_t a);

		/**
		 * @brief Returns the hue of this color in degrees.
		 * @return Hue in the range [0, 360).
		 */
		[[nodiscard]] uint16_t GetHue() const;

		/**
		 * @brief Returns the HSV saturation of this color.
		 * @return Saturation in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetSaturation() const;

		/**
		 * @brief Returns the HSV value (brightness) of this color.
		 * @return Value in the range [0.0, 1.0].
		 */
		[[nodiscard]] float GetValue() const;

		/**
		 * @brief Converts the colour to HSV components.
		 * @param hue Output hue in the range [0, 360].
		 * @param sat Output saturation in the range [0, 1].
		 * @param val Output value in the range [0, 1].
		 */
		void HSV(uint16_t* hue, float* sat, float* val) const;

		/**
		 * @brief Returns a copy of this color with the red channel replaced.
		 * @param r The new red component [0, 255].
		 */
		[[nodiscard]] Color WithRed(uint8_t r) const;

		/**
		 * @brief Returns a copy of this color with the green channel replaced.
		 * @param g The new green component [0, 255].
		 */
		[[nodiscard]] Color WithGreen(uint8_t g) const;

		/**
		 * @brief Returns a copy of this color with the blue channel replaced.
		 * @param b The new blue component [0, 255].
		 */
		[[nodiscard]] Color WithBlue(uint8_t b) const;

		/**
		 * @brief Returns a copy of this color with the alpha channel replaced.
		 * @param a The new alpha component [0, 255].
		 */
		[[nodiscard]] Color WithAlpha(uint8_t a) const;

		/**
		 * @brief Returns the bitwise inverse of this color's RGB channels.
		 * @note  The alpha channel is preserved.
		 */
		[[nodiscard]] Color Inverted() const;

		/**
		 * @brief Returns a greyscale version of this color.
		 * @details Converts using perceived luminance weights (ITU-R BT.709).
		 *          The alpha channel is preserved.
		 */
		[[nodiscard]] Color Greyscale() const;

		/**
		 * @brief Returns the perceived luminance of this color.
		 * @details Calculated using ITU-R BT.709 weights: 0.2126R + 0.7152G + 0.0722B.
		 * @return Luminance in the range [0.0, 1.0].
		 */
		[[nodiscard]] float Luminance() const;

		/**
		 * @brief Converts this color's RGB channels from sRGB (gamma-encoded) to linear light.
		 * @note  Should be called before any physically-based lighting calculations.
		 *        The alpha channel is not affected.
		 */
		void ToLinear();

		/**
		 * @brief Converts this color's RGB channels from linear light to sRGB (gamma-encoded).
		 * @note  Should be called before storing or displaying a color that was in linear space.
		 *        The alpha channel is not affected.
		 */
		void ToGamma();

	public:
		/** @brief Converts this Color to a GLM @c vec4 with components in [0.0, 1.0]. */
		operator vec4() const;

		/**
		 * @brief Assigns a GLM @c vec4 to this Color.
		 * @param rhs A vector with components in the range [0.0, 1.0], ordered (r, g, b, a).
		 */
		Color& operator=(const vec4& rhs);

		/** @brief Copy-assignment operator. */
		Color& operator=(const Color& rhs);

		/** @brief Returns @c true if both colors have identical RGBA values. */
		bool operator==(const Color& rhs) const;

		/** @brief Returns @c true if the colors differ in any channel. */
		bool operator!=(const Color& rhs) const;

		/** @brief Writes the color to a stream as @c "Color(r, g, b, a)". */
		friend ostream& operator<<(ostream& stream, const Color& rhs);
	};
}

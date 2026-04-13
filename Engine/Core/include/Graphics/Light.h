/*****************************************************************************
 * Light
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/
#pragma once

#include "catalyst_export.h"

#include <Matrix4.h>
#include <Vector3.h>

using Catalyst::Math::Matrix4;
using Catalyst::Math::Vector3;

namespace Catalyst::Graphics
{
	/**
	 * Represents a light source in the scene, supporting both positional
	 * and directional light types with configurable color and intensity.
	 */
	class CATALYST_EXPORT Light
	{
	public:
		/**
		 * Default constructor. Initialises the light with white color,
		 * full intensity, and no direction.
		 */
		Light();

		/**
		 * Constructs a positional light with the given color and intensity.
		 * @param color    The RGB color of the light.
		 * @param intensity The brightness scalar applied to the color.
		 */
		Light(const Vector3& color, float intensity);

		/**
		 * Constructs a directional light with the given color, intensity, and direction.
		 * @param color     The RGB color of the light.
		 * @param intensity The brightness scalar applied to the color.
		 * @param direction The world-space direction the light is casting towards.
		 */
		Light(const Vector3& color, float intensity, const Vector3& direction);

	public:
		/**
		 * Calculates the full color value of this light.
		 * @return m_color * m_intensity
		 */
		[[nodiscard]] Vector3 TrueColor() const;

		/**
		 * Returns the current intensity of the light.
		 * @return The brightness scalar.
		 */
		[[nodiscard]] float Intensity() const;

		/**
		 * Sets the intensity of the light.
		 * @param intensity The new brightness scalar to apply.
		 */
		void SetIntensity(float intensity);

		/**
		 * Returns the base RGB color of the light, without intensity applied.
		 * @return The light's color vector.
		 */
		[[nodiscard]] Vector3 Color() const;

		/**
		 * Sets the base RGB color of the light.
		 * @param color The new color vector to assign.
		 */
		void SetColor(const Vector3& color);

		/**
		 * Returns the world-space position of the light.
		 * @return The translation component of the light's transform.
		 */
		[[nodiscard]] Vector3 Location() const;

		/**
		 * Sets the world-space position of the light.
		 * @param location The new position to assign to the light's transform.
		 */
		void SetLocation(const Vector3& location);

		/**
		 * Returns the direction the light is casting towards.
		 * Only meaningful when the light is set as directional.
		 * @return The normalised direction vector.
		 */
		[[nodiscard]] Vector3 Direction() const;

		/**
		 * Sets the direction the light casts towards.
		 * @param direction The new direction vector. Expected to be normalised.
		 */
		void SetDirection(const Vector3& direction);

		/**
		 * Gets the current state of the isDirectional value.
		 * @return True if the light is directional, false if it is positional.
		 */
		[[nodiscard]] bool IsDirectional() const;

		/**
		 * Sets the directional boolean value.
		 * @param isDirectional The new value of the directional boolean.
		 */
		void SetIsDirectional(bool isDirectional);

	private:
		Matrix4 m_transform;  /**< The world-space transform of the light, encoding position and orientation. */
		Vector3 m_color;      /**< The base RGB color of the light, before intensity is applied. */
		float m_intensity;    /**< The brightness scalar multiplied against m_color to produce the true color. */
		bool m_isDirectional; /**< True if the light is treated as directional (infinite distance), false if positional. */

	};
}
/*****************************************************************************
 * SceneLighting
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/
#pragma once

#include "catalyst_export.h"

#include <Vector3.h>

#include <string>
#include <vector>

using Catalyst::Math::Vector3;

using std::string;
using std::vector;

namespace Catalyst::Graphics
{
	class IShader;
	class Light;

	/**
	 * Manages all light sources in a scene and is responsible for uploading
	 * lighting data to a shader for rendering.
	 */
	class CATALYST_EXPORT SceneLighting
	{
	public:
		/**
		 * Default constructor. Initialises ambient color to black and
		 * prepares an empty light list.
		 */
		SceneLighting();

		/**
		 * Destructor. Does not take ownership of light pointers;
		 * lights must be freed by the caller.
		 */
		~SceneLighting();

	public:
		/**
		 * Returns the current ambient light color of the scene.
		 * @return The ambient color vector.
		 */
		[[nodiscard]] Vector3 AmbientColor() const;

		/**
		 * Sets the ambient light color of the scene.
		 * @param color The new ambient color to assign.
		 */
		void SetAmbientColor(const Vector3& color);

		/**
		 * Adds a light to the scene. Ownership is not transferred;
		 * the caller is responsible for the lifetime of the pointer.
		 * @param light Pointer to the light to add.
		 */
		void AddLight(Light* light);

		/**
		 * Uploads all lighting data to the provided shader, including
		 * ambient color and all registered light sources.
		 * @param shader The shader to upload lighting uniforms to.
		 */
		void Render(IShader* shader) const;

	private:
		/**
		 * Attempts to set a boolean uniform on the shader, keyed by id and key.
		 * @param shader The target shader.
		 * @param id     The light's identifier string used to namespace the uniform.
		 * @param key    The uniform field name within the light's namespace.
		 * @param value  The boolean value to set.
		 */
		static void TrySetBoolean(IShader* shader, const string& id, const string& key, bool value);

		/**
		 * Attempts to set a Vector3 uniform on the shader, keyed by id and key.
		 * @param shader The target shader.
		 * @param id     The light's identifier string used to namespace the uniform.
		 * @param key    The uniform field name within the light's namespace.
		 * @param value  The Vector3 value to set.
		 */
		static void TrySetVector(IShader* shader, const string& id, const string& key, const Vector3& value);

	private:
		Vector3 m_ambient;       /**< The ambient light color applied globally across the scene. */
		vector<Light*> m_lights; /**< The collection of lights registered to this scene. Pointers are non-owning. */

	};
}
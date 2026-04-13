/*****************************************************************************
 * Light
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/

#include "Graphics/SceneLighting.h"

#include <format>
#include <iostream>

#include "Graphics/IShader.h"
#include "Graphics/Light.h"

#define MAX_LIGHTS 8

namespace Catalyst::Graphics
{
	SceneLighting::SceneLighting()
		: m_ambient{ 1.f }
	{

	}

	SceneLighting::~SceneLighting()
	{
		for (const Light* light : m_lights)
		{
			delete light;
		}

		m_lights.clear();
	}

	Vector3 SceneLighting::AmbientColor() const
	{
		return m_ambient;
	}

	void SceneLighting::SetAmbientColor(const Vector3& color)
	{
		m_ambient = color;
	}

	void SceneLighting::AddLight(Light* light)
	{
		m_lights.emplace_back(light);
	}

	void SceneLighting::Render(IShader* shader) const
	{
		TrySetVector(shader, "", "ambientLight", m_ambient);

		for (size_t i = 0; i < MAX_LIGHTS; ++i)
		{
			// Construct the ID for this index
			string id = std::format("lights[{}].", i);

			// If this index has a light
			if (i < m_lights.size())
			{
				const Light* light = m_lights[i];

				// Attempt to set the directional and set booleans
				TrySetBoolean(shader, id, "isSet", true);
				TrySetBoolean(shader, id, "isDirectional", light->IsDirectional());

				// Attempt to set the direction, location and color values
				TrySetVector(shader, id, "direction", light->Direction());
				TrySetVector(shader, id, "location", light->Location());
				TrySetVector(shader, id, "color", light->TrueColor());
			}
			else
			{
				// No light for this index, so set the value to false
				TrySetBoolean(shader, id, "isSet", false);
			}
		}
	}

	void SceneLighting::TrySetBoolean(IShader* shader, const string& id, const string& key, const bool value)
	{
		try
		{
			// Attempt to set the boolean value
			shader->Set(id + key, value ? 1 : 0);
		}
		catch (std::exception& e)
		{
			// It failed, so print out the information about the failure
			std::cout << e.what() << ": " << id << key << "\n";
		}
	}

	void SceneLighting::TrySetVector(IShader* shader, const string& id, const string& key, const Vector3& value)
	{
		try
		{
			// Attempt to set the boolean value
			shader->Set(id + key, value);
		}
		catch (std::exception& e)
		{
			// It failed, so print out the information about the failure
			std::cout << e.what() << ": " << id << key << "\n";
		}
	}
}

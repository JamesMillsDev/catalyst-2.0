/*****************************************************************************
 * SceneLighting
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/
#include "Graphics/Material.h"

#include <iostream>
#include <ranges>

#include "Graphics/IShader.h"
#include "Graphics/ITexture.h"

namespace Catalyst::Graphics
{
	Material::Material(IShader* shader)
		: m_shader{ shader }
	{

	}

	Material::~Material()
	{
		for (const auto& texture : m_textures | std::views::values)
		{
			delete texture;
		}

		m_textures.clear();

		m_booleans.clear();
		m_integers.clear();
		m_floats.clear();

		m_rgbs.clear();
		m_rgbas.clear();
	}

	void Material::Set(const string& name, const bool value)
	{
		m_booleans[name] = value;
	}

	void Material::Set(const string& name, const int value)
	{
		m_integers[name] = value;
	}

	void Material::Set(const string& name, const float value)
	{
		m_floats[name] = value;
	}

	void Material::Set(const string& name, ITexture* value)
	{
		size_t index = 0;

		for (const string& id : m_textures | std::views::keys)
		{
			if (name == id)
			{
				break;
			}

			index++;
		}

		if (index < m_textures.size())
		{
			if (m_textures[index].second != value)
			{
				m_textures[index].second = value;
			}
		}
		else
		{
			m_textures.emplace_back(name, value);
		}
	}

	void Material::Set(const string& name, const Vector3& value)
	{
		m_rgbs[name] = value;
	}

	void Material::Set(const string& name, const Vector4& value)
	{
		m_rgbas[name] = value;
	}

	void Material::Render()
	{
		// Utility lambda to save having to rewrite this everytime.
		auto setUniforms = [this]<typename T>(unordered_map<string, T> map)
		{
			for (auto& [key, value] : map)
			{
				try
				{
					m_shader->Set("material." + key, value);
				}
				catch (std::exception& e)
				{
					std::cout << e.what() << ": material." << key << "\n";
				}
			}
		};

		int index = 0;
		for (auto& [key, value] : m_textures)
		{
			try
			{
				m_shader->Set("material." + key, value, index++);
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << ": material." << key << "\n";
			}
		}

		setUniforms(m_booleans);
		setUniforms(m_integers);
		setUniforms(m_floats);
		setUniforms(m_rgbs);
		setUniforms(m_rgbas);
	}
}

/*****************************************************************************
 * SceneLighting
 * Created by James Mills on 13/04/2026.
 *****************************************************************************/
#pragma once

#include "catalyst_export.h"

#include <Vector3.h>
#include <Vector4.h>

#include <string>
#include <unordered_map>
#include <vector>

using Catalyst::Math::Vector3;
using Catalyst::Math::Vector4;

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

namespace Catalyst::Graphics
{
	class IShader;
	class ITexture;

	class CATALYST_EXPORT Material
	{
	public:
		explicit Material(IShader* shader);
		~Material();

	public:
		void Set(const string& name, bool value);

		void Set(const string& name, int value);

		void Set(const string& name, float value);

		void Set(const string& name, ITexture* value);

		void Set(const string& name, const Vector3& value);

		void Set(const string& name, const Vector4& value);

		void Render();

	private:
		IShader* m_shader;

		vector<pair<string, ITexture*>> m_textures;

		unordered_map<string, bool> m_booleans;
		unordered_map<string, int> m_integers;
		unordered_map<string, float> m_floats;

		unordered_map<string, Vector3> m_rgbs;
		unordered_map<string, Vector4> m_rgbas;

	};
}
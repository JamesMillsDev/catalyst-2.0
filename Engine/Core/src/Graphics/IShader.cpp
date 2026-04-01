#include "Graphics/IShader.h"

#include <filesystem>
#include <utility>

namespace fs = std::filesystem;

namespace Catalyst::Graphics
{
	IShader::IShader(string path)
		: m_path{ std::move(path) } { }

	IShader::~IShader() = default;

	const string& IShader::Path() const
	{
		return m_path;
	}

	string IShader::Name() const
	{
		const fs::path path{ m_path };
		return path.filename().string();
	}
}

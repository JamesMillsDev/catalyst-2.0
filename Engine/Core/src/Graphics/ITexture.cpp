/*****************************************************************************
 * ITexture
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#include "Graphics/ITexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Catalyst::Graphics
{
	ITexture::ITexture() :
		m_fileName{ "none" }, m_width{ 0 }, m_height{ 0 }, m_format{ None }, m_pixels{ nullptr } { }

	ITexture::ITexture(const string& fileName) :
		m_fileName{ fileName }, m_width{ 0 }, m_height{ 0 }, m_format{ None }, m_pixels{ nullptr }
	{
	}

	ITexture::ITexture(const uint32 width, const uint32 height, const ETextureFormat format, uint8* pixels) :
		m_fileName{ "none" }, m_width{ width }, m_height{ height }, m_format{ format }, m_pixels{ pixels }
	{
	}

	ITexture::~ITexture() = default;

	const string& ITexture::GetFileName() const
	{
		return m_fileName;
	}

	uint32 ITexture::Width() const
	{
		return m_width;
	}

	uint32 ITexture::Height() const
	{
		return m_height;
	}

	ETextureFormat ITexture::Format() const
	{
		return m_format;
	}

	const uint8* ITexture::Pixels() const
	{
		return m_pixels;
	}

	void ITexture::LoadPixels(const string& fileName, int* w, int* h, int* comp)
	{
		m_pixels = stbi_load(fileName.c_str(), w, h, comp, STBI_default);
	}

	void ITexture::UnloadPixels()
	{
		if (m_pixels != nullptr)
		{
			stbi_image_free(m_pixels);
			m_pixels = nullptr;
		}
	}
}

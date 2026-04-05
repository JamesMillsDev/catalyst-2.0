/*****************************************************************************
 * OpenGlTexture
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#include "Graphics/OpenGlTexture.h"

#include <glad/gl.h>

namespace Catalyst::Graphics::OpenGL
{
	OpenGlTexture::OpenGlTexture() = default;

	OpenGlTexture::OpenGlTexture(const string& fileName) :
		ITexture{ fileName }
	{
		OpenGlTexture::Load(fileName);
	}

	OpenGlTexture::OpenGlTexture(const uint32 width, const uint32 height, const ETextureFormat format, uint8* pixels) :
		ITexture{ width, height, format, pixels }
	{
		OpenGlTexture::Create(width, height, format, pixels);
	}

	OpenGlTexture::~OpenGlTexture()
	{
		if (m_handle != 0)
		{
			glDeleteTextures(1, &m_handle);
		}

		UnloadPixels();
	}

	bool OpenGlTexture::Load(const string& fileName)
	{
		if (m_handle != 0)
		{
			glDeleteTextures(1, &m_handle);

			m_handle = 0;
			m_width = 0;
			m_height = 0;
			m_format = None;
			m_fileName = "none";
		}

		int w = 0, h = 0, comp = 0;
		LoadPixels(fileName, &w, &h, &comp);

		if (m_pixels != nullptr)
		{
			glGenTextures(1, &m_handle);
			glBindTexture(GL_TEXTURE_2D, m_handle);

			switch (comp)
			{
				case 1:
					{
						m_format = R;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, m_pixels);

						break;
					}

				case 2:
					{
						m_format = RG;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, w, h, 0, GL_RG, GL_UNSIGNED_BYTE, m_pixels);
						break;
					}

				case 3:
					{
						m_format = RGB;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pixels);
						break;
					}

				case 4:
					{
						m_format = RGBA;
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels);
						break;
					}
				default:
					{
						break;
					}
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			m_width = static_cast<uint32>(w);
			m_height = static_cast<uint32>(h);
			m_fileName = fileName;

			return true;
		}

		return false;
	}

	void OpenGlTexture::Create(const uint32 width, const uint32 height, const ETextureFormat format, uint8* pixels)
	{
		if (m_handle != 0)
		{
			glDeleteTextures(1, &m_handle);
			m_handle = 0;
			m_fileName = "none";
		}

		m_width = width;
		m_height = height;
		m_format = format;

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		switch (m_format)
		{
			case R:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels);
					break;
				}
			case RG:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_width, m_height, 0, GL_RG, GL_UNSIGNED_BYTE, pixels);
					break;
				}
			case RGB:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
					break;
				}
			case RGBA:
			default:
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
					break;
				}
		};

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGlTexture::Bind(const uint32 slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	uint32 OpenGlTexture::Handle() const
	{
		return m_handle;
	}
}

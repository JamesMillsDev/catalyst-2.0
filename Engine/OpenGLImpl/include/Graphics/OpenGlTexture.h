/*****************************************************************************
 * OpenGlTexture
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_opengl_export.h"

#include "Graphics/ITexture.h"

namespace Catalyst::Graphics::OpenGL
{
	class CATALYSTOPENGL_EXPORT OpenGlTexture : public ITexture
	{
	public:
		OpenGlTexture();
		explicit OpenGlTexture(const string& fileName);
		OpenGlTexture(uint32 width, uint32 height, ETextureFormat format, uint8* pixels = nullptr);

		~OpenGlTexture() override;

	public:
		bool Load(const string& fileName) override;
		void Create(unsigned width, unsigned height, ETextureFormat format, uint8* pixels) override;
		void Bind(uint32 slot) const override;

		uint32 Handle() const;

	private:
		uint32 m_handle;

	};
}

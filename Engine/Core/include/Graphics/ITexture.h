/*****************************************************************************
 * ITexture
 * Created by James Mills on 5/04/2026.
 *****************************************************************************/

#pragma once

#include <string>

#include "catalyst_export.h"

#include "Utility/Typedefs.h"

using std::string;

namespace Catalyst::Graphics
{
	enum ETextureFormat : uint8
	{
		None,
		R,
		RG,
		RGB,
		RGBA
	};

	class CATALYST_EXPORT ITexture
	{
	public:
		ITexture();
		explicit ITexture(const string& fileName);
		ITexture(uint32 width, uint32 height, ETextureFormat format, uint8* pixels = nullptr);

		virtual ~ITexture();

	public:
		virtual bool Load(const string& fileName) = 0;
		virtual void Create(unsigned int width, unsigned int height, ETextureFormat format, uint8* pixels = nullptr) = 0;

		const string& GetFileName() const;

		virtual void Bind(uint32 slot = 0) const = 0;

		uint32 Width() const;
		uint32 Height() const;

		ETextureFormat Format() const;
		const uint8* Pixels() const;

	protected:
		string m_fileName;

		uint32 m_width;
		uint32 m_height;

		ETextureFormat m_format;
		uint8* m_pixels;

	protected:
		void LoadPixels(const string& fileName, int* w, int* h, int* comp);
		void UnloadPixels();

	};
}

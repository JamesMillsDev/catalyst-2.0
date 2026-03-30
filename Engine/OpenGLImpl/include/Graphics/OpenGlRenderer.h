/*****************************************************************************
 * OpenGlRenderer
 * Created by James Mills on 31/03/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_opengl_export.h"
#include "Graphics/IRenderer.h"

namespace Catalyst::Graphics::OpenGL
{
	class CATALYSTOPENGL_EXPORT OpenGlRenderer : public IRenderer
	{
	public:
		virtual void RenderMesh(IMesh* mesh) override;

	};
}

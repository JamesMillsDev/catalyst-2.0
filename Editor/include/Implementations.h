/*****************************************************************************
 * Implementations
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#ifdef USE_OPEN_GL
#include <OpenGLWindow.h>
#include <Graphics/OpenGlRenderer.h>

using WindowImpl = Catalyst::OpenGL::OpenGLWindow;
using RendererImpl = Catalyst::Graphics::OpenGL::OpenGlRenderer;
#else
#include "IWindow.h"
#include "Graphics/IRenderer.h"
namespace Catalyst
{
	class InvalidWindow : public IWindow
	{
	public:
		InvalidWindow(const char* title, float width, float height)
			: IWindow{ title, width, height } { }

		virtual bool Open() override{ return false; }

		virtual void Close() override{}

		virtual bool BeginFrame() const override {return false;}

		virtual void EndFrame() override {}
	};

	namespace Graphics
	{
		class InvalidRenderer : public IRenderer
		{
		public:
			virtual void RenderMesh(IMesh* mesh) override{}

		};
	}
}

using WindowImpl = Catalyst::InvalidWindow;
using RendererImpl = Catalyst::Graphics::InvalidRenderer;
#endif
/*****************************************************************************
 * Implementations
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#ifdef USE_OPEN_GL
#include <OpenGLWindow.h>

#include <Graphics/OpenGlMesh.h>
#include <Graphics/OpenGlRenderer.h>

using WindowImpl   = Catalyst::OpenGL::OpenGLWindow;
using RendererImpl = Catalyst::Graphics::OpenGL::OpenGlRenderer;
using MeshImpl     = Catalyst::Graphics::OpenGL::OpenGlMesh;
#else
#include "IWindow.h"
#include "Graphics/IMesh.h"
#include "Graphics/IRenderer.h"
namespace Catalyst
{
	class InvalidWindow : public IWindow
	{
	public:
		InvalidWindow(const char* title, float width, float height)
			: IWindow{ title, width, height } { }

		virtual bool Open() override
		{
			return false;
		}

		virtual void Close() override { }

		virtual bool BeginFrame() const override
		{
			return false;
		}

		virtual void EndFrame() override { }
	};

	namespace Graphics
	{
		class InvalidRenderer : public IRenderer
		{
		public:
			virtual void RenderMesh(IMesh* mesh) override { }
		};

		class InvalidMesh : public IMesh
		{
		public:
			InvalidMesh() = default;

			InvalidMesh(const InvalidMesh& other) = default;

		public:
			virtual void Initialise(uint32 vertexCount, const Vertex* vertices, uint32 indexCount,
			                        const uint32* indices) override { }
		};
	}
}

using WindowImpl   = Catalyst::InvalidWindow;
using RendererImpl = Catalyst::Graphics::InvalidRenderer;
using MeshImpl     = Catalyst::Graphics::InvalidMesh;
#endif

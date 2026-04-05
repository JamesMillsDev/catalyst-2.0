/*****************************************************************************
 * Implementations
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#ifdef USE_OPEN_GL
#include <OpenGLWindow.h>

#include <Graphics/OpenGlMesh.h>
#include <Graphics/OpenGlRenderer.h>
#include <Graphics/OpenGlShader.h>
#include <Graphics/OpenGlTexture.h>

using WindowImpl = Catalyst::OpenGL::OpenGLWindow;
using RendererImpl = Catalyst::Graphics::OpenGL::OpenGlRenderer;
using MeshImpl = Catalyst::Graphics::OpenGL::OpenGlMesh;
using ShaderImpl = Catalyst::Graphics::OpenGL::OpenGlShader;
using TextureImpl = Catalyst::Graphics::OpenGL::OpenGlTexture;
#else
#include "IWindow.h"
#include "Graphics/IMesh.h"
#include "Graphics/IRenderer.h"
#include "Graphics/IShader.h"
#include "Graphics/ITexture.h"

namespace Catalyst
{
	class InvalidWindow : public IWindow
	{
	public:
		InvalidWindow(const char* title, float width, float height) :
			IWindow{ title, width, height } { }

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

		class InvalidShader : public IShader
		{
		public:
			explicit InvalidShader(const string& path) :
				IShader{ path } { }

			virtual bool Load() override
			{
				return false;
			}

			virtual void Bind(ICommandBuffer* cmd) override { }

			virtual void Unbind(ICommandBuffer* cmd) override { }

			virtual void Set(const string& id, float value) override { }

			virtual void Set(const string& id, int value) override { }

			virtual void Set(const string& id, const Vector2& value) override { }

			virtual void Set(const string& id, const Vector3& value) override { }

			virtual void Set(const string& id, const Vector4& value) override { }

			virtual void Set(const string& id, const Matrix3& value) override { }

			virtual void Set(const string& id, const Matrix4& value) override { }

			virtual void Set(const string& id, float* value, int count) override { }

			virtual void Set(const string& id, int* value, int count) override { }

			virtual void Set(const string& id, Vector2* value, int count) override { }

			virtual void Set(const string& id, Vector3* value, int count) override { }

			virtual void Set(const string& id, Vector4* value, int count) override { }

			virtual void Set(const string& id, Matrix3* value, int count) override { }

			virtual void Set(const string& id, Matrix4* value, int count) override { }

		protected:
			virtual vector<string> Extensions() override
			{
				return { };
			}
		};

		class InvalidTexture : public ITexture
		{
		public:
			InvalidTexture() = default;

			explicit InvalidTexture(const string& fileName) :
				ITexture{ fileName } { }

			InvalidTexture(const uint32 width, const uint32 height, const ETextureFormat format) :
				ITexture{ width, height, format } { }

		public:
			bool Load(const string& fileName) override
			{
				return false;
			}

			void Create(unsigned width, unsigned height, ETextureFormat format, uint8* pixels) override { }
			void Bind(uint32 slot) const override { }
		};
	}
}

using WindowImpl = Catalyst::InvalidWindow;
using RendererImpl = Catalyst::Graphics::InvalidRenderer;
using MeshImpl = Catalyst::Graphics::InvalidMesh;
using ShaderImpl = Catalyst::Graphics::InvalidShader;
#endif

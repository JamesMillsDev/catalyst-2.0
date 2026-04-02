#include "Graphics/IRenderer.h"

#include "Graphics/Camera.h"
#include "Graphics/IShader.h"

namespace Catalyst::Graphics
{
	IRenderer::IRenderer()
		: m_camera{ nullptr } { }

	void IRenderer::SetCamera(Camera* camera)
	{
		m_camera = camera;
	}

	void IRenderer::SetProjectionViewMatrix(IShader* shader) const
	{
		shader->Set("projection", m_camera->Projection());
		shader->Set("view", m_camera->View());
	}
}

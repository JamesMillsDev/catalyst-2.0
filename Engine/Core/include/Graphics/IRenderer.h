/*****************************************************************************
* IRenderer
* Created by James Mills on 30/03/2026.
*****************************************************************************/
#pragma once

#include "catalyst_export.h"

namespace Catalyst::Graphics
{
	class Camera;
	class IMesh;
	class IShader;

	class CATALYST_EXPORT IRenderer
	{
	public:
		IRenderer();
		virtual ~IRenderer() = default;

	public:
		void SetCamera(Camera* camera);
		void SetProjectionViewMatrix(IShader* shader) const;

		virtual void RenderMesh(IMesh* mesh) = 0;

	private:
		Camera* m_camera;

	};
}

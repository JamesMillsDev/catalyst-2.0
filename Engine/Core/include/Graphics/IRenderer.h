/*****************************************************************************
* IRenderer
* Created by James Mills on 30/03/2026.
*****************************************************************************/
#pragma once

namespace Catalyst::Graphics
{
	class IMesh;

	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

	public:
		virtual void RenderMesh(IMesh* mesh) = 0;

	};
}

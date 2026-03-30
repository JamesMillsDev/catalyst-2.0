/*****************************************************************************
 * OpenGlMesh
 * Created by James Mills on 31/03/2026.
 *****************************************************************************/

#pragma once

#include "Graphics/IMesh.h"

#include "catalyst_opengl_export.h"

namespace Catalyst::Graphics::OpenGL
{
	class CATALYSTOPENGL_EXPORT OpenGlMesh : public IMesh
	{
		friend class OpenGlRenderer;

	public:
		explicit OpenGlMesh(const string& name);

		OpenGlMesh(const OpenGlMesh& other);

	protected:
		virtual void Initialise(uint32 vertexCount, const Vertex* vertices, uint32 indexCount,
		                        const uint32* indices) override;

	private:
		uint32 m_triCount;
		uint32 m_vao; // the Vertex Array Object
		uint32 m_vbo; // the Vertex Buffer Object
		uint32 m_ibo; // the Index Buffer Object

	};
}

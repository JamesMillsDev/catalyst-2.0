/*****************************************************************************
 * OpenGlRenderer
 * Created by James Mills on 31/03/2026.
 *****************************************************************************/

#include "Graphics/OpenGlRenderer.h"

#include <glad/gl.h>

#include "Graphics/OpenGlMesh.h"

namespace Catalyst::Graphics::OpenGL
{
	void OpenGlRenderer::RenderMesh(IMesh* mesh)
	{
		if (const OpenGlMesh* oglMesh = dynamic_cast<OpenGlMesh*>(mesh))
		{
			glBindVertexArray(oglMesh->m_vao);

			// Check if we are using indices or just vertex points
			if (oglMesh->m_ibo != 0)
			{
				glDrawElements(GL_TRIANGLES, 3 * static_cast<int>(oglMesh->m_triCount), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, 3 * static_cast<int>(oglMesh->m_triCount));
			}
		}
	}
}

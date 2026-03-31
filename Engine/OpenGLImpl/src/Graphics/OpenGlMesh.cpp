/*****************************************************************************
 * OpenGlMesh
 * Created by James Mills on 31/03/2026.
 *****************************************************************************/

#include "Graphics/OpenGlMesh.h"

#include <glad/gl.h>

#include <cassert>

namespace Catalyst::Graphics::OpenGL
{
	OpenGlMesh::OpenGlMesh()
		: m_triCount{ 0 }, m_vao{ 0 }, m_vbo{ 0 }, m_ibo{ 0 } { }

	OpenGlMesh::OpenGlMesh(const OpenGlMesh& other) = default;

	void OpenGlMesh::Initialise(const uint32 vertexCount, const Vertex* vertices, const uint32 indexCount,
	                            const uint32* indices)
	{
		assert(m_vao == 0);

		// Generate buffers
		glGenBuffers(1, &m_vbo);
		glGenVertexArrays(1, &m_vao);

		// Bind the vertex array, this will be our mesh buffer
		glBindVertexArray(m_vao);

		// Bind and fill the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * static_cast<long long>(sizeof(Vertex)), vertices, GL_STATIC_DRAW);

		int id = 0;

		// Enable the first element as the location
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id++, 4, GL_FLOAT, GL_FALSE, static_cast<long long>(sizeof(Vertex)),
		                      reinterpret_cast<void*>(offsetof(Vertex, location)));

		// Enable the second element as the normal
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id++, 4, GL_FLOAT, GL_TRUE, static_cast<long long>(sizeof(Vertex)),
		                      reinterpret_cast<void*>(offsetof(Vertex, normal)));

		// Enable the third-tenth elements as the uvs
		for (uint32 i = 0; i < MAX_TEXTURE_COORDS; i++)
		{
			glEnableVertexAttribArray(id);
			glVertexAttribPointer(id++, 2, GL_FLOAT, GL_FALSE, static_cast<long long>(sizeof(Vertex)),
			                      reinterpret_cast<void*>(offsetof(Vertex, uvs) + sizeof(float) * 2 * i));
		}

		if (vertices->hasTangents)
		{
			// Enable the eleventh element as the tangent
			glEnableVertexAttribArray(id);
			glVertexAttribPointer(id++, 4, GL_FLOAT, GL_TRUE, static_cast<long long>(sizeof(Vertex)),
			                      reinterpret_cast<void*>(offsetof(Vertex, tangent)));

			// Enable the twelfth element as the bit tangent
			glEnableVertexAttribArray(id);
			glVertexAttribPointer(id, 4, GL_FLOAT, GL_TRUE, static_cast<long long>(sizeof(Vertex)),
			                      reinterpret_cast<void*>(offsetof(Vertex, biTangent)));
		}

		// Bind the indices if there are any defined
		if (indexCount != 0)
		{
			glGenBuffers(1, &m_ibo);

			// Bind and fill the index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * static_cast<long long>(sizeof(uint32)), indices,
			             GL_STATIC_DRAW);

			m_triCount = indexCount / 3;
		}
		else
		{
			m_triCount = vertexCount / 3;
		}

		// Unbind the buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

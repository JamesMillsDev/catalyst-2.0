#include "Graphics/IMesh.h"

#include <utility>

#include "Graphics/IRenderer.h"

namespace Catalyst::Graphics
{
	IMesh::IMesh() = default;

	IMesh::IMesh(const IMesh& other) = default;

	IMesh::~IMesh() = default;

	void IMesh::Render(IRenderer* renderer)
	{
		renderer->RenderMesh(this);
	}
}

#include "Graphics/IMesh.h"

#include <utility>

namespace Catalyst::Graphics
{
	IMesh::IMesh(string name)
		: name{ std::move(name) } { }

	IMesh::IMesh(const IMesh& other) = default;

	IMesh::~IMesh() = default;

	void IMesh::Render(IRenderer* renderer)
	{

	}
}

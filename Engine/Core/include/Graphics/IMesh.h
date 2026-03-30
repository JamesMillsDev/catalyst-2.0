/*****************************************************************************
* IMesh
* Created by James Mills on 30/03/2026.
*****************************************************************************/
#pragma once

#include <string>

#include <assimp/mesh.h>

#include "catalyst_export.h"
#include "Vector2.h"
#include "Vector4.h"

#include "Utility/TemplateConstraints.h"
#include "Utility/Typedefs.h"

using std::string;

using Catalyst::Math::Vector2;
using Catalyst::Math::Vector4;

namespace Catalyst::Graphics
{
	class IRenderer;

	#define MAX_TEXTURE_COORDS 8

	struct Vertex
	{
		Vector4 location;
		Vector4 normal;

		Vector4 tangent;
		Vector4 biTangent;

		Vector2 uvs[MAX_TEXTURE_COORDS];

		bool hasTangents;
	};

	class CATALYST_EXPORT IMesh
	{
	public:
		template<Derived<IMesh> MESH>
		static MESH* MakeQuad();

		template<Derived<IMesh> MESH>
		static MESH* MakeCube();

		template<Derived<IMesh> MESH>
		static MESH* MakeSphere(uint8 segments = 16, uint8 rings = 16);

		template<Derived<IMesh> MESH>
		static MESH* MakeCylinder(uint8 segments = 16);

		template<Derived<IMesh> MESH>
		static MESH* MakePlane(int32 w = 1, int32 h = 1, int32 subdivisions = 1);

		template<Derived<IMesh> MESH>
		static MESH* MakeFromAssimp(const aiMesh* mesh, bool flipV = false);

	public:
		string name;

	public:
		explicit IMesh(string  name);

		IMesh(const IMesh& other);

		virtual ~IMesh();

	public:
		virtual void Render(IRenderer* renderer);

	protected:
		virtual void Initialise(uint32 vertexCount, const Vertex* vertices, uint32 indexCount = 0,
		                        const uint32* indices = nullptr) = 0;
	};
}

#include "IMesh.inl"
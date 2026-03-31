/*****************************************************************************
* IMesh Implementation
* Created by James Mills on 30/03/2026.
*****************************************************************************/
#ifndef IMESH_IMPLEMENTATION
#define IMESH_IMPLEMENTATION

#include "Utility/Typedefs.h"

#include <vector>

using std::vector;

namespace Catalyst::Graphics
{
	template<Derived<IMesh> MESH>
	MESH* IMesh::MakeQuad()
	{
		MESH* mesh = new MESH;
		mesh->name = "Quad";

		// Define the 6 vertices for our two triangles to make a quad,
		// in a counter-clockwise direction.
		Vertex vertices[6];
		vertices[0].location = { -.5f, 0, .5f, 1.f };
		vertices[1].location = { .5f, 0, .5f, 1.f };
		vertices[2].location = { -.5f, 0, -.5f, 1.f };

		vertices[3].location = { -0.5f, 0, -0.5f, 1.f };
		vertices[4].location = { 0.5f, 0, 0.5f, 1.f };
		vertices[5].location = { 0.5f, 0, -0.5f, 1.f };

		vertices[0].normal = { 0, 1, 0, 0 };
		vertices[1].normal = { 0, 1, 0, 0 };
		vertices[2].normal = { 0, 1, 0, 0 };
		vertices[3].normal = { 0, 1, 0, 0 };
		vertices[4].normal = { 0, 1, 0, 0 };
		vertices[5].normal = { 0, 1, 0, 0 };

		vertices[0].uvs[0] = { 0, 1 }; // Bottom Left
		vertices[1].uvs[0] = { 1, 1 }; // Bottom Right
		vertices[2].uvs[0] = { 0, 0 }; // Top Left
		vertices[3].uvs[0] = { 0, 0 }; // Top Left
		vertices[4].uvs[0] = { 1, 1 }; // Bottom Right
		vertices[5].uvs[0] = { 1, 0 }; // Top Right

		mesh->Initialise(6, vertices);

		return mesh;
	}

	template<Derived<IMesh> MESH>
	MESH* IMesh::MakeCube()
	{
		return nullptr;
	}

	template<Derived<IMesh> MESH>
	MESH* IMesh::MakeSphere(uint8 segments, uint8 rings)
	{
		return nullptr;
	}

	template<Derived<IMesh> MESH>
	MESH* IMesh::MakeCylinder(uint8 segments)
	{
		return nullptr;
	}

	template<Derived<IMesh> MESH>
	MESH* IMesh::MakePlane(int32 w, int32 h, int32 subdivisions)
	{
		return nullptr;
	}

	template<Derived<IMesh> MESH>
	MESH* IMesh::MakeFromAssimp(const aiMesh* mesh, const bool flipV)
	{
		MESH* newMesh = new MESH;
		newMesh->name = mesh->mName.C_Str();

		vector<Vertex> vertices;
		vector<uint32> indices;

		for (uint32 v = 0; v < mesh->mNumVertices; ++v)
		{
			Vertex vert;

			aiVector3D vertex = mesh->mVertices[v];
			vert.location = { vertex.x, vertex.y, vertex.z, 1.f };

			if (mesh->HasNormals())
			{
				aiVector3D normal = mesh->mNormals[v];
				vert.normal = { normal.x, normal.y, normal.z, 0.f };
			}

			if (mesh->HasTangentsAndBitangents())
			{
				aiVector3D tangent = mesh->mTangents[v];
				aiVector3D biTangent = mesh->mBitangents[v];

				vert.tangent = { tangent.x, tangent.y, tangent.z, 0.f };
				vert.biTangent = { biTangent.x, biTangent.y, biTangent.z, 0.f };
				vert.hasTangents = true;
			}

			for (uint32 i = 0; i < mesh->GetNumUVChannels(); ++i)
			{
				if (mesh->HasTextureCoords(i))
				{
					aiVector3D uv = mesh->mTextureCoords[i][v];
					vert.uvs[i] = { uv.x, flipV ? -uv.y : uv.y };
				}
			}
		}

		for (uint32 i = 0; i < mesh->mNumFaces; ++i)
		{
			indices.emplace_back(mesh->mFaces[i].mIndices[1]);
			indices.emplace_back(mesh->mFaces[i].mIndices[2]);
			indices.emplace_back(mesh->mFaces[i].mIndices[0]);

			// generate a second triangle for quads
			if (mesh->mFaces[i].mNumIndices == 4)
			{
				indices.emplace_back(mesh->mFaces[i].mIndices[2]);
				indices.emplace_back(mesh->mFaces[i].mIndices[3]);
				indices.emplace_back(mesh->mFaces[i].mIndices[0]);
			}
		}

		newMesh->Initialise(static_cast<uint32>(vertices.size()), vertices.data(), static_cast<uint32>(indices.size()),
		                    indices.data());
		return newMesh;
	}
}
#endif

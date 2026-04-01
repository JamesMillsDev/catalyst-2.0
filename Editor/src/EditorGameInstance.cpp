#include "EditorGameInstance.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Implementations.h"
#include "Vector3.h"
#include "Graphics/Camera.h"

using Catalyst::Math::Vector3;

namespace Catalyst::Editor
{
	EditorGameInstance::EditorGameInstance()
		: m_camera{ new Camera }, m_testMesh{ nullptr }
	{ }

	EditorGameInstance::~EditorGameInstance()
	{
		delete m_camera;
		m_camera = nullptr;
	}

	void EditorGameInstance::Initialise()
	{
		m_camera->View() = Matrix4::MakeTransform(
			{ 0.f, 1.f, -10.f }, { -30.f, 0.f, 0.f }, { 1.f }
		);

		const aiScene* loaded = aiImportFile("TestProject\\Content\\Models\\SM_Soulspear.fbx", aiProcess_CalcTangentSpace);
		m_testMesh = IMesh::MakeFromAssimp<MeshImpl>(loaded->mMeshes[0]);
	}

	void EditorGameInstance::Tick() { }

	void EditorGameInstance::Render()
	{
		m_testMesh->Render(const_cast<IRenderer*>(m_renderer));
	}

	void EditorGameInstance::Shutdown() { }
}

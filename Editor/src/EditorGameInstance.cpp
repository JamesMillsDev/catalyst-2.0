#include "EditorGameInstance.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/scene.h>           // Output data structure

#include "Implementations.h"
#include "Vector3.h"
#include "Graphics/Camera.h"

using Catalyst::Math::Vector3;

namespace Catalyst::Editor
{
	EditorGameInstance::EditorGameInstance()
		: m_camera{ new Camera }, m_testMesh{ nullptr }, m_testShader{ nullptr } { }

	EditorGameInstance::~EditorGameInstance()
	{
		delete m_camera;
		m_camera = nullptr;
	}

	void EditorGameInstance::Initialise()
	{
		m_camera->View() = Matrix4::MakeTransform({ 0.f, 0.f, -10.f }, { 0.f, 0.f, 0.f }, { 1.f });
		m_renderer->SetCamera(m_camera);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(R"(TestProject\Content\Models\SM_Soulspear.fbx)", aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		m_testMesh = IMesh::MakeFromAssimp<MeshImpl>(scene->mMeshes[0]);

		m_testShader = new ShaderImpl{ R"(TestProject\Content\Shaders\test)" };
		m_testShader->Load();
	}

	void EditorGameInstance::Tick() { }

	void EditorGameInstance::Render()
	{
		m_testShader->Bind(nullptr);
		m_renderer->SetProjectionViewMatrix(m_testShader);
		m_testShader->Set("model", Matrix4::Identity());

		m_testMesh->Render(m_renderer);
		m_testShader->Unbind(nullptr);
	}

	void EditorGameInstance::Shutdown()
	{
		delete m_testMesh;
		m_testMesh = nullptr;

		delete m_testShader;
		m_testShader = nullptr;
	}
}

#include "EditorGameInstance.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/scene.h>           // Output data structure

#include "CatalystMath.h"
#include "GameTime.h"
#include "Implementations.h"
#include "Vector3.h"

#include "Graphics/Camera.h"

using Catalyst::Math::CatalystMath;
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
		float time = GameTime::AppTime();

		m_testShader->Bind(nullptr);
		m_renderer->SetProjectionViewMatrix(m_testShader);
		m_testShader->Set("model", Matrix4::Identity());
		m_testShader->Set("light.color", Vector3{ 1.f, 1.f, 0.f });
		m_testShader->Set("light.direction", Vector3{ CatalystMath::Cos(time * 2.f), CatalystMath::Sin(time * 2.f), 0.f });
		m_testShader->Set("ambientLight", Vector3{ .25f, .25f, .25f });

		m_testShader->Set("material.ambientColor", Vector3{ 0.f });
		m_testShader->Set("material.diffuseColor", Vector3{ .8f });
		m_testShader->Set("material.specularColor", Vector3{ .5f });
		m_testShader->Set("material.specularPower", 20.f);

		m_testShader->Set("cameraLocation", m_camera->View().Translation());

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

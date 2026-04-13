#include "EditorGameInstance.h"

#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/scene.h>           // Output data structure

#include "CatalystMath.h"
#include "FlyCam.h"
#include "GameTime.h"
#include "Implementations.h"
#include "Vector3.h"

#include "Graphics/Light.h"
#include "Graphics/Material.h"
#include "Graphics/SceneLighting.h"

using Catalyst::Math::CatalystMath;
using Catalyst::Math::Vector3;

namespace Catalyst::Editor
{
	EditorGameInstance::EditorGameInstance() :
		m_camera{ new FlyCam }, m_testMesh{ nullptr }, m_testShader{ nullptr }, m_sceneLighting{ nullptr },
		m_material{ nullptr } { }

	EditorGameInstance::~EditorGameInstance()
	{
		delete m_camera;
		m_camera = nullptr;
	}

	void EditorGameInstance::Initialise()
	{
		m_renderer->SetCamera(m_camera);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(R"(TestProject\Content\Models\SM_Soulspear.fbx)",
		                                         aiProcess_CalcTangentSpace |
		                                         aiProcess_Triangulate |
		                                         aiProcess_JoinIdenticalVertices |
		                                         aiProcess_SortByPType);

		m_testMesh = IMesh::MakeFromAssimp<MeshImpl>(scene->mMeshes[0], true);

		m_testShader = new ShaderImpl{ R"(TestProject\Content\Shaders\pbr)" };
		m_testShader->Load();

		TextureImpl* baseColorTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_Soulspear_B.tga)" };
		TextureImpl* normalTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_Soulspear_N.tga)" };
		TextureImpl* ormTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_Soulspear_ORM.tga)" };

		m_sceneLighting = new SceneLighting;

		Light* light = new Light{ { 1.f, 0.f, 0.f }, 500.f };
		light->SetLocation({ 5.f, 3.f, 0.f });

		Light* light2 = new Light{ { 0.f, 0.f, 1.f }, 500.f };
		light2->SetLocation({ -5.f, 3.f, 0.f });

		m_sceneLighting->AddLight(light);
		m_sceneLighting->AddLight(light2);
		m_sceneLighting->SetAmbientColor({ .5f });

		m_material = new Material{ m_testShader };
		m_material->Set("baseColorTex", baseColorTexture);
		m_material->Set("normalTex", normalTexture);
		m_material->Set("ormTex", ormTexture);

		m_material->Set("baseColor", Vector3{ .8f });
		//m_material->Set("specularColor", Vector3{ .5f });
		//m_material->Set("specularPower", 20.f);
	}

	void EditorGameInstance::Tick()
	{
		m_camera->Tick();
	}

	void EditorGameInstance::Render()
	{
		m_testShader->Bind(nullptr);

		try
		{
			m_renderer->SetProjectionViewMatrix(m_testShader);
			m_testShader->Set("model", Matrix4::Identity());

			m_sceneLighting->Render(m_testShader);
			m_material->Render();

			m_testShader->Set("cameraLocation", m_camera->View().Translation());
		}
		catch ([[maybe_unused]] std::exception& e)
		{
			std::cout << e.what() << "\n";
		}

		m_testMesh->Render(m_renderer);
		m_testShader->Unbind(nullptr);
	}

	void EditorGameInstance::Shutdown()
	{
		delete m_sceneLighting;
		m_sceneLighting = nullptr;

		delete m_material;
		m_material = nullptr;

		delete m_testMesh;
		m_testMesh = nullptr;

		delete m_testShader;
		m_testShader = nullptr;
	}
}

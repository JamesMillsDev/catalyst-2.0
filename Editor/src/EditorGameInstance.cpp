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

using Catalyst::Math::CatalystMath;
using Catalyst::Math::Vector3;

namespace Catalyst::Editor
{
	EditorGameInstance::EditorGameInstance() :
		m_camera{ new FlyCam }, m_testMesh{ nullptr }, m_testShader{ nullptr }, m_baseColorTexture{ nullptr },
		m_normalTexture{ nullptr }, m_ormTexture{ nullptr } { }

	EditorGameInstance::~EditorGameInstance()
	{
		delete m_camera;
		m_camera = nullptr;
	}

	void EditorGameInstance::Initialise()
	{
		m_renderer->SetCamera(m_camera);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(R"(TestProject\Content\Models\SM_ToiletBrush.fbx)",
		                                         aiProcess_CalcTangentSpace |
		                                         aiProcess_Triangulate |
		                                         aiProcess_JoinIdenticalVertices |
		                                         aiProcess_SortByPType);

		m_testMesh = IMesh::MakeFromAssimp<MeshImpl>(scene->mMeshes[0], true);

		m_testShader = new ShaderImpl{ R"(TestProject\Content\Shaders\pbr)" };
		m_testShader->Load();

		m_baseColorTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_ToiletBrush_B.tga)" };
		m_normalTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_ToiletBrush_N.tga)" };
		m_ormTexture = new TextureImpl{ R"(TestProject\Content\Textures\T_ToiletBrush_ORM.tga)" };
	}

	void EditorGameInstance::Tick()
	{
		m_camera->Tick();
	}

	void EditorGameInstance::Render()
	{
		float time = GameTime::AppTime();

		m_testShader->Bind(nullptr);

		try
		{
			for (int i = 1; i < 4; ++i)
			{
				m_testShader->Set(std::format("lights[{}].isSet", i), 0);
			}

			m_renderer->SetProjectionViewMatrix(m_testShader);
			m_testShader->Set("model", Matrix4::Identity());
			m_testShader->Set("lights[0].isSet", 1);
			m_testShader->Set("lights[0].isDirectional", 1);
			m_testShader->Set("lights[0].color", Vector3{ 1.f, 1.f, 1.f });
			m_testShader->Set("lights[0].direction", Vector3{ CatalystMath::Cos(time * 2.f), CatalystMath::Sin(time * 2.f), 0.f });
			//m_testShader->Set("ambientLight", Vector3{ .25f, .25f, .25f });

			//m_testShader->Set("material.ambientColor", Vector3{ 0.f });
			m_testShader->Set("material.baseColor", Vector3{ .8f });
			//m_testShader->Set("material.specularColor", Vector3{ .5f });
			//m_testShader->Set("material.specularPower", 20.f);

			m_testShader->Set("cameraLocation", m_camera->View().Translation());

			m_testShader->Set("material.baseColorTex", m_baseColorTexture, 0);
			m_testShader->Set("material.normalTex", m_normalTexture, 1);
			m_testShader->Set("material.ormTex", m_ormTexture, 2);
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
		delete m_baseColorTexture;
		m_baseColorTexture = nullptr;

		delete m_normalTexture;
		m_normalTexture = nullptr;

		delete m_ormTexture;
		m_ormTexture = nullptr;

		delete m_testMesh;
		m_testMesh = nullptr;

		delete m_testShader;
		m_testShader = nullptr;
	}
}

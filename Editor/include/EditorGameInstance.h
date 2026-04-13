#pragma once

#include "IGameInstance.h"

#include "Graphics/ITexture.h"

namespace Catalyst
{
	namespace Graphics
	{
		class Camera;
		class IMesh;
		class IShader;
		class ITexture;
		class Material;
		class SceneLighting;
	}

	using namespace Graphics;

	namespace Editor
	{
		class EditorGameInstance : public IGameInstance
		{
		public:
			EditorGameInstance();
			~EditorGameInstance() override;

		protected:
			virtual void Initialise() override;

			virtual void Tick() override;

			virtual void Render() override;

			virtual void Shutdown() override;

		private:
			Camera* m_camera;
			IMesh* m_testMesh;
			IShader* m_testShader;

			SceneLighting* m_sceneLighting;
			Material* m_material;

		};
	}
}

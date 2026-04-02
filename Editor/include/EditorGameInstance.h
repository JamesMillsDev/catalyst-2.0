#pragma once

#include "IGameInstance.h"

namespace Catalyst
{
	namespace Graphics
	{
		class Camera;
		class IMesh;
		class IShader;
	}

	using Graphics::Camera;
	using Graphics::IMesh;
	using Graphics::IShader;

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

		};
	}
}

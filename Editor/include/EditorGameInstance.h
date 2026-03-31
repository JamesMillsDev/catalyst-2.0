#pragma once

#include "IGameInstance.h"

namespace Catalyst
{
	namespace Graphics
	{
		class Camera;
		class IMesh;
	}

	using Graphics::Camera;
	using Graphics::IMesh;

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

		};
	}
}

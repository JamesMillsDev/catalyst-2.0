#pragma once

#include "catalyst_export.h"

namespace Catalyst
{
	class IWindow;

	namespace Graphics
	{
		class IRenderer;
	}

	using Graphics::IRenderer;

	class CATALYST_EXPORT IGameInstance
	{
		friend class Application;

	protected:
		IWindow const* m_window;
		IRenderer const* m_renderer;

	protected:
		IGameInstance();
		virtual ~IGameInstance();

	protected:
		virtual void Initialise() = 0;

		virtual void Tick() = 0;
		virtual void Render() = 0;

		virtual void Shutdown() = 0;

	};
}
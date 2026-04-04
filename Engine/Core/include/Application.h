/*****************************************************************************
 * Application
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_export.h"
#include "IGameInstance.h"
#include "IWindow.h"

#include "Graphics/IRenderer.h"

#include "Utility/ExitCodes.h"
#include "Utility/TemplateConstraints.h"

namespace Catalyst
{
	using Graphics::IRenderer;

	class CATALYST_EXPORT Application
	{
	public:
		template<Derived<IGameInstance> GAME, Derived<IWindow> WINDOW, Derived<IRenderer> RENDERER>
		static int Run(const char* title, float w, float h);

		static Application const* Instance();

	public:
		IWindow const* GetWindow() const;

	private:
		static Application* m_instance;

	private:
		IWindow* m_window;
		IRenderer* m_renderer;
		IGameInstance* m_gameInstance;

	private:
		Application();
		~Application();

	private:
		int Process();

	};

	template<Derived<IGameInstance> GAME, Derived<IWindow> WINDOW, Derived<IRenderer> RENDERER>
	int Application::Run(const char* title, float w, float h)
	{
		if (m_instance != nullptr)
		{
			return APP_INSTANCE_NOT_NULL;
		}

		m_instance = new Application;
		m_instance->m_window = new WINDOW{ title, w, h };
		m_instance->m_renderer = new RENDERER;

		m_instance->m_gameInstance = new GAME;
		m_instance->m_gameInstance->m_window = m_instance->m_window;
		m_instance->m_gameInstance->m_renderer = m_instance->m_renderer;

		const int retCode = m_instance->Process();
		delete m_instance;

		return retCode;
	}
}

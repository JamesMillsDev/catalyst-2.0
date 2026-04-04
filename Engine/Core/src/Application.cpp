/*****************************************************************************
 * Application
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#include "Application.h"

#include "GameTime.h"

namespace Catalyst
{
	Application const* Application::Instance()
	{
		return m_instance;
	}

	IWindow const* Application::GetWindow() const
	{
		return m_window;
	}

	Application* Application::m_instance = nullptr;

	Application::Application()
		: m_window{ nullptr }, m_renderer{ nullptr }, m_gameInstance{ nullptr }
	{
		m_instance = this;
	}

	Application::~Application()
	{
		delete m_gameInstance;
		m_gameInstance = nullptr;

		delete m_renderer;
		m_renderer = nullptr;

		delete m_window;
		m_window = nullptr;
	}

	int Application::Process()
	{
		if (!m_window->Open())
		{
			return WINDOW_FAILED_TO_OPEN;
		}

		GameTime::Init();

		m_gameInstance->Initialise();

		while (m_window->IsOpen())
		{
			GameTime::Tick();

			if (!m_window->BeginFrame())
			{
				continue;
			}

			m_gameInstance->Tick();
			m_gameInstance->Render();

			m_window->EndFrame();
		}

		m_gameInstance->Shutdown();

		m_window->Close();

		return SUCCESS;
	}
}

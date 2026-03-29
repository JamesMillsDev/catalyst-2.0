/*****************************************************************************
 * Application
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_export.h"
#include "IWindow.h"

#include "Utility/ExitCodes.h"
#include "Utility/TemplateConstraints.h"

namespace Catalyst
{
	class CATALYST_EXPORT Application
	{
	public:
		template<Derived<IWindow> WINDOW>
		static int Run(const char* title, float w, float h);

		static Application const* Instance();

	private:
		static Application* m_instance;

	private:
		IWindow* m_window;

	private:
		Application();
		~Application();

	private:
		int Process();

	};

	template<Derived<IWindow> WINDOW>
	int Application::Run(const char* title, float w, float h)
	{
		if (m_instance != nullptr)
		{
			return APP_INSTANCE_NOT_NULL;
		}

		m_instance = new Application;
		m_instance->m_window = new WINDOW{ title, w, h };

		const int retCode = m_instance->Process();
		delete m_instance;

		return retCode;
	}
}

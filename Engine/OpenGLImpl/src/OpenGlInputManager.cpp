#include "OpenGlInputManager.h"

#include "Application.h"
#include "OpenGlWindow.h"

#include "GLFW/glfw3.h"

namespace Catalyst::OpenGL
{
	OpenGlInputManager::OpenGlInputManager()
		: m_window{ nullptr } { }

	void OpenGlInputManager::Initialize()
	{
		m_window = dynamic_cast<OpenGlWindow*>(const_cast<IWindow*>(Application::Instance()->GetWindow()));

		m_lastKeys = new int[GLFW_KEY_LAST + 1];
		m_currentKeys = new int[GLFW_KEY_LAST + 1];

		m_mouseX = 0;
		m_mouseY = 0;
		m_mouseScroll = 0;

		for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
		{
			m_lastKeys[i] = m_currentKeys[i] = glfwGetKey(m_window->ToGlfw(), i);
		}

		for (int i = 0; i < 8; ++i)
		{
			m_lastButtons[i] = m_currentButtons[i] = glfwGetMouseButton(m_window->ToGlfw(), i);
		}

		auto mouseMoveCallback = [](GLFWwindow* window, const double x, const double y)
		{
			m_instance->OnMouseMove(static_cast<float>(x), static_cast<float>(y));
		};

		auto mouseScrollCallback = [](GLFWwindow* window, const double x, const double y)
		{
			m_instance->SetMouseScroll(m_instance->GetMouseScroll() + static_cast<float>(y));
		};

		auto mouseEnterCallback = [](GLFWwindow* window, int entered)
		{
			m_instance->SetMouseEntered(true);
		};

		glfwSetScrollCallback(m_window->ToGlfw(), mouseScrollCallback);
		glfwSetCursorPosCallback(m_window->ToGlfw(), mouseMoveCallback);
		glfwSetCursorEnterCallback(m_window->ToGlfw(), mouseEnterCallback);
	}

	void OpenGlInputManager::Poll()
	{
		m_pressedCharacters.clear();
		m_pressedKeys.clear();

		for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
		{
			m_lastKeys[i] = m_currentKeys[i];

			if ((m_currentKeys[i] = glfwGetKey(m_window->ToGlfw(), i)) == GLFW_PRESS)
			{
				m_pressedKeys.emplace_back(i);
			}
		}

		for (int i = 0; i <= MouseButton8; ++i)
		{
			m_lastButtons[i] = m_currentButtons[i];
			m_currentButtons[i] = glfwGetMouseButton(m_window->ToGlfw(), i);
		}

		m_oldMouseX = m_mouseX;
		m_oldMouseY = m_mouseY;
	}

	int OpenGlInputManager::PressValue() const
	{
		return GLFW_PRESS;
	}

	int OpenGlInputManager::ReleaseValue() const
	{
		return GLFW_RELEASE;
	}
}

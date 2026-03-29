/*****************************************************************************
 * OpenGLWindow
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#include "OpenGlWindow.h"

#include "glad/gl.h"

#include "GLFW/glfw3.h"

namespace Catalyst::OpenGL
{
	OpenGLWindow::OpenGLWindow(const char* title, const float width, const float height)
		: IWindow{ title, width, height }, m_window{ nullptr } { }

	bool OpenGLWindow::Open()
	{
		if (!glfwInit())
		{
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height), m_title, nullptr, nullptr);
		if (m_window == nullptr)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGL(glfwGetProcAddress))
		{
			glfwTerminate();
			glfwDestroyWindow(m_window);
			m_window = nullptr;

			return false;
		}

		glViewport(0, 0, static_cast<int>(m_width), static_cast<int>(m_height));

		return true;
	}

	void OpenGLWindow::Close()
	{
		glfwTerminate();

		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}

	bool OpenGLWindow::BeginFrame() const
	{
		glfwPollEvents();

		return glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) == GLFW_FALSE;
	}

	void OpenGLWindow::EndFrame()
	{
		glfwSwapBuffers(m_window);

		if (glfwWindowShouldClose(m_window))
		{
			m_shouldClose = true;
		}
	}
}

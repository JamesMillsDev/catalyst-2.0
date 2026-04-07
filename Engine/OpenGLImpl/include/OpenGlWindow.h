/*****************************************************************************
 * OpenGLWindow
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_opengl_export.h"
#include "IWindow.h"

struct GLFWwindow;

namespace Catalyst::OpenGL
{
	class CATALYSTOPENGL_EXPORT OpenGLWindow : public IWindow
	{
	public:
		OpenGLWindow(const char* title, float width, float height);

	public:
		virtual bool Open() override;

		virtual void Close() override;

		virtual bool BeginFrame() const override;

		virtual void EndFrame() override;
		
		GLFWwindow* ToGlfw() const;

	private:
		GLFWwindow* m_window;

	};
}

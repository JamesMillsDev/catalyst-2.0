/*****************************************************************************
 * Implementations
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#ifdef USE_OPEN_GL
#include <OpenGLWindow.h>

using WindowImpl = Catalyst::OpenGL::OpenGLWindow;
#else
#include "IWindow.h"
namespace Catalyst
{
	class WindowImpl : public IWindow
	{
	public:
		WindowImpl(const char* title, float width, float height)
			: IWindow{ title, width, height } { }

		virtual bool Open() override{ return false; }

		virtual void Close() override{}

		virtual bool BeginFrame() const override {return false;}

		virtual void EndFrame() override {}
	};
}
#endif
#pragma once

#include "catalyst_opengl_export.h"
#include "IInputManager.h"

namespace Catalyst::OpenGL
{
	class OpenGlWindow;

	class CATALYSTOPENGL_EXPORT OpenGlInputManager : public IInputManager
	{
	public:
		OpenGlInputManager();

	protected:
		virtual void Initialize() override;

		virtual void Poll() override;

		[[nodiscard]] virtual int PressValue() const override;

		[[nodiscard]] virtual int ReleaseValue() const override;

	private:
		OpenGlWindow* m_window;
	};
}

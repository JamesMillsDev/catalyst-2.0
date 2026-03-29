/*****************************************************************************
 * IWindow
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#pragma once

#include "catalyst_export.h"

namespace Catalyst
{
	class CATALYST_EXPORT IWindow
	{
	public:
		IWindow(const char* title, float width, float height);

		virtual ~IWindow();

	public:
		virtual bool Open() = 0;

		virtual void Close() = 0;

		void Quit();

		virtual bool BeginFrame() const = 0;

		virtual void EndFrame() = 0;

		bool IsOpen() const;

	protected:
		char* m_title;
		float m_width;
		float m_height;

		bool m_shouldClose;
	};
} // Catalyst

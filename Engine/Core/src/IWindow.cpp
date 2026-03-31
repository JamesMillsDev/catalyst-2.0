/*****************************************************************************
 * IWindow
 * Created by James Mills on 27/03/2026.
 *****************************************************************************/

#include "IWindow.h"

#include <cstring>

namespace Catalyst
{
	IWindow::IWindow(const char* title, const float width, const float height)
		: m_title{ nullptr }, m_width{ width }, m_height{ height }, m_shouldClose{ false }
	{
		m_title = new char[strlen(title) + 1];
		strcpy_s(m_title, strlen(title) + 1, title);
	}

	IWindow::~IWindow()
	{
		delete[] m_title;
		m_title = nullptr;
	}

	void IWindow::Quit()
	{
		m_shouldClose = true;
	}

	bool IWindow::IsOpen() const
	{
		return !m_shouldClose;
	}

	float IWindow::Width() const
	{
		return m_width;
	}

	float IWindow::Height() const
	{
		return m_height;
	}
}

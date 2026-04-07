/*****************************************************************************
 * IInputManager
 * Created by James Mills on 7/04/2026.
 *****************************************************************************/

#include "IInputManager.h"

namespace Catalyst
{
	bool IInputManager::IsKeyDown(const EKeyCode inputKey) const
	{
		return m_currentKeys[inputKey] == PressValue();
	}

	bool IInputManager::IsKeyUp(const EKeyCode inputKey) const
	{
		return m_currentKeys[inputKey] == ReleaseValue();
	}

	bool IInputManager::WasKeyPressed(const EKeyCode inputKey) const
	{
		return m_currentKeys[inputKey] == PressValue() &&
		       m_lastKeys[inputKey] == ReleaseValue();
	}

	bool IInputManager::WasKeyReleased(const EKeyCode inputKey) const
	{
		return m_currentKeys[inputKey] == ReleaseValue() &&
		       m_lastKeys[inputKey] == PressValue();
	}

	bool IInputManager::IsMouseButtonDown(const EMouseButton mouseButton) const
	{
		return m_currentButtons[mouseButton] == PressValue();
	}

	bool IInputManager::IsMouseButtonUp(const EMouseButton mouseButton) const
	{
		return m_currentButtons[mouseButton] == ReleaseValue();
	}

	bool IInputManager::WasMouseButtonPressed(const EMouseButton mouseButton) const
	{
		return m_currentButtons[mouseButton] == PressValue() &&
		       m_lastButtons[mouseButton] == ReleaseValue();
	}

	bool IInputManager::WasMouseButtonReleased(const EMouseButton mouseButton) const
	{
		return m_currentButtons[mouseButton] == ReleaseValue() &&
		       m_lastButtons[mouseButton] == PressValue();
	}

	Vector2 IInputManager::GetMouseLocation() const
	{
		return { m_mouseX, m_mouseY };
	}

	Vector2 IInputManager::GetMouseDelta() const
	{
		return { m_mouseX - m_oldMouseX, m_mouseY - m_oldMouseY };
	}

	float IInputManager::GetMouseScroll() const
	{
		return m_mouseScroll;
	}

	IInputManager::IInputManager()
		: m_mouseX{ 0 }, m_mouseY{ 0 }, m_oldMouseX{ 0 }, m_oldMouseY{ 0 }, m_mouseScroll{ 0 },
		  m_firstMouseMove{ false }, m_lastKeys{ nullptr }, m_currentKeys{ nullptr }, m_lastButtons{ },
		  m_currentButtons{ } { }

	IInputManager::~IInputManager()
	{
		delete[] m_lastKeys;
		m_lastKeys = nullptr;

		delete[] m_currentKeys;
		m_currentKeys = nullptr;
	}

	IInputManager* IInputManager::m_instance = nullptr;

	void IInputManager::Destroy()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
}
